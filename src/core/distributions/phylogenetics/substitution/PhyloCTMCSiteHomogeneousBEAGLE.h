//---------------------------------------------------------------------------------------[ Header ]
//--{1

#ifndef PhyloCTMCSiteHomogeneousBEAGLE_H
#define PhyloCTMCSiteHomogeneousBEAGLE_H

#include "AbstractPhyloCTMCSiteHomogeneous.h"
#include "TopologyNode.h"

#include "RbVector.h"

//-- TODO: are these needed?
#include "DnaState.h"
#include "RateMatrix.h"
#include "TransitionProbabilityMatrix.h"
#include "TypedDistribution.h"


//#if defined ( RB_BEAGLE_DEBUG )
//    #include <iomanip>
//
//    //-- Enable / Disable using eigen3 library by (un)commenting the following:
//    #define RB_USE_EIGEN3
//
//    #if defined ( RB_USE_EIGEN3 )
//        #include <Eigen/Core>
//        #include <Eigen/Dense>
//        #include <Eigen/Eigenvalues>
//    #endif /* RB_USE_EIGEN3 */
//
//#endif /* RB_BEAGLE_DEBUG */



namespace RevBayesCore
{

    template<class charType>
    class PhyloCTMCSiteHomogeneousBEAGLE : public AbstractPhyloCTMCSiteHomogeneous<charType>
    {

        public:

            //----====  Constructors  ====----

            //-- Default constructor
            PhyloCTMCSiteHomogeneousBEAGLE ( const TypedDagNode<Tree>* t
                                           , size_t nChars
                                           , bool c
                                           , size_t nSites
                                           , bool amb
                                           , bool internal
                                           , bool gapmatch
                                           );

            //-- Clone constructor
            PhyloCTMCSiteHomogeneousBEAGLE* clone ( void ) const;


            //-- Destructor
            virtual ~PhyloCTMCSiteHomogeneousBEAGLE ( void );


        protected:

            //----====  Protected Methods  ====----

            //-- Set MCMC mode.
            //virtual void   setMcmcMode                   ( bool tf );

            //-- Return the computed likelihood.
            virtual double sumRootLikelihood             ( void );

            //-- Calculate the lnLikelihood of a tree given the model.
            //virtual double computeLnProbability          ( void );

            //-- BEAGLE compute lnLikelihood of a rooted tree.
            virtual void   computeRootLikelihood         ( size_t root
                                                         , size_t l
                                                         , size_t r
                                                         );

            //-- BEAGLE compute lnLikelihood of an unrooted tree.
            virtual void   computeRootLikelihood         ( size_t root
                                                         , size_t l
                                                         , size_t r
                                                         , size_t m
                                                         );

            //-- Collect a BEAGLE operation for an internal node into the computation queue.
            virtual void   computeInternalNodeLikelihood ( const TopologyNode &n
                                                         , size_t nIdx
                                                         , size_t l
                                                         , size_t r
                                                         );

            //-- Collect a BEAGLE operation for a leaf node into the computation queue.
            virtual void   computeTipLikelihood          ( const TopologyNode &node
                                                         , size_t nIdx
                                                         );

        private:

            //----====  Private Variables  ====----

            //-- Keep track if a BEAGLE instance exists.
            //bool isBeagleInitialized = false;

            //-- Accumulate BEAGLE lnLikelihood across all models.
            double ln_beagle_probability;


            //----====  Private Methods  ====----

            //-- Helper function to pretty print BEAGLE error codes.
            //std::string parseBeagleReturnCode           ( int code );

            //-- Initialize a BEAGLE instance.
            //void        initializeBeagleInstance  ( void );

            //-- Set the tree tip states for the BEAGLE instance.
            //void        initializeBeagleTips      ( void );

            //-- Set BEAGLE buffers for the substitution models.
            //void        updateSubstitutionModels  ( void );

            //-- Calculate the tree branch length between adjacent tree nodes..
            double      calculateBranchLength     ( const TopologyNode &node
                                                  , size_t node_index
                                                  );

            //-- Set BEAGLE buffers for site-model mappings.
            //void        setSitePatterns           ( void );

            //-- Set BEAGLE buffers for the the stationary distribution of a model.
            //void        setStationaryDistribution ( void );

            //-- Set BEAGLE buffers for the ASRV distribution for a model.
            //void        setSiteRateDistribution   ( void );


    };

} //-- End namespace

//--}

//-----------------------------------------------------------------------[ Imports / Constructors ]
//--{1

#include "ConstantNode.h"
#include "DiscreteCharacterState.h"
#include "RandomNumberFactory.h"

#include <cmath>
#include <cstring>


//-- Try to keep a clean(ish) file structure... Refer to the namespace of this class as 'This'.
//   Remember to '#undef This' at the end of header file and NEVER have '#include'
//   statements after this line.
#define This RevBayesCore::PhyloCTMCSiteHomogeneousBEAGLE<charType>



template<class charType>
This::PhyloCTMCSiteHomogeneousBEAGLE ( const TypedDagNode<Tree>* t
                                     , size_t nChars
                                     , bool c
                                     , size_t nSites
                                     , bool amb
                                     , bool internal
                                     , bool gapmatch
                                     )
    : AbstractPhyloCTMCSiteHomogeneous<charType> ( t
                                                 , nChars
                                                 , 1
                                                 , c
                                                 , nSites
                                                 , amb
                                                 , internal
                                                 , gapmatch
                                                 )
{
    //#if defined ( RB_BEAGLE_DEBUG )
    //    std::stringstream ss;
    //    ss << "Constructing BEAGLE!!!!" << std::endl;
    //    RBOUT(ss.str());
    //#endif /* RB_BEAGLE_DEBUG_TIP_STATES */

    //this->initializeBeagleInstance();
}



template<class charType>
This::~PhyloCTMCSiteHomogeneousBEAGLE ( void )
{
    // We don't delete the parameters, because they might be used somewhere else too.
    // The model needs to do that!

    //if ( RbSettings::userSettings().getUseBeagle() == true
    //     && this->in_mcmc_mode == true
    //     && this->beagle_instance >= 0 )
    //{
    //    #if defined ( RB_BEAGLE_DEBUG )
    //        RBOUT ( "Finalizing BEAGLE" );
    //    #endif /* RB_BEAGLE_DEBUG */

    //    beagleFinalizeInstance(this->beagle_instance);
    //    this->beagle_instance = -1;
    //}
}



template<class charType>
This* This::clone ( void ) const
{
    return new PhyloCTMCSiteHomogeneousBEAGLE<charType>(*this);
}

//--}


//-----------------------------------------------------------------------[ Private Helper Methods ]
//--{1

template<class charType>
double This::calculateBranchLength ( const TopologyNode &node, size_t node_index )
{
    double branch_len;
    double rate ;

    if ( this->branch_heterogeneous_clock_rates == true )
    {
        rate = this->heterogeneous_clock_rates->getValue()[node_index];
    }
    else if ( this->homogeneous_clock_rate != NULL)
    {
        rate = this->homogeneous_clock_rate->getValue();
    }
    else
    {
        rate = 1.0;
    }

    //-- TODO: check if this should be invariable site...
    //rate /= this->homogeneous_clock_rate->getValue();

    branch_len = rate * node.getBranchLength();
    if ( branch_len < 0 )
    {
      throw RbException("Error : Negative branch length!");
    }

    // #if defined ( RB_BEAGLE_DEBUG )
    //     std::stringstream ss;
    //     ss << "Branch length: " << std::to_string(branch_len) << "\n";
    //     RBOUT(ss.str());
    // #endif /* RB_BEAGLE_DEBUG */

    return branch_len;
}

//--}

//------------------------------------------------------------------------------[ BEAGLE Updaters ]
//--{1

//template<class charType>
//void This::setSitePatterns ( void )
//{
//    this->b_inPatternWeights = std::vector<double>(this->pattern_block_size);
//    for ( size_t b_pattern = 0; b_pattern < this->pattern_block_size; ++b_pattern )
//    {
//        this->b_inPatternWeights[b_pattern] = (double) this->pattern_counts[b_pattern];
//    }
//
//    #if defined ( RB_BEAGLE_DEBUG )
//        std::stringstream ss; ss << "Setting Site Patterns...\n";
//        ss << "\tPatterns : \n\t\t";
//        for ( auto x : this->b_inPatternWeights )
//        {
//          ss << std::to_string(x) << " ";
//        }
//        ss << "\n";
//        RBOUT(ss.str());
//    #endif /* RB_BEAGLE_DEBUG */
//
//    int b_code_pattern_weight =
//        beagleSetPatternWeights( this->beagle_instance
//                               , &this->b_inPatternWeights[0]
//                               );
//    if ( b_code_pattern_weight != 0 )
//    {
//        ss << "Error : " << this->parseBeagleReturnCode(b_code_pattern_weight) << "\n";
//        throw RbException("Could not set pattern weights for model"
//                         + this->parseBeagleReturnCode(b_code_pattern_weight));
//    }
//}


//template<class charType>
//void This::setSiteRateDistribution ( void )
//{
//    #if defined ( RB_BEAGLE_DEBUG )
//        std::stringstream ss;
//    #endif /* RB_BEAGLE_DEBUG */
//
//    // site rate categories not yet supported
//    int b_categoryWeightsIndex = 0;
//
//    int b_code_weights;
//    int b_code_rates;
//
//    //-- Only homogeneous models for now...
//    if (this->rate_variation_across_sites)
//    {
//        this->b_inCategoryWeights = this->site_rates_probs->getValue();
//        this->b_inCategoryRates   = this->site_rates->getValue();
//    }
//    else
//    {
//        this->b_inCategoryWeights = { 1.0 };
//        this->b_inCategoryRates   = { 1.0 };
//    }
//
//    #if defined ( RB_BEAGLE_DEBUG )
//        ss << "Setting Site Rates...\n";
//        ss << "\tCategory weights : \n\t\t";
//        for ( auto x : this->b_inCategoryWeights )
//        {
//          ss << std::to_string(x) << " ";
//        }
//        ss << "\n";
//        ss << "\tCategory rates : \n\t\t";
//        for ( auto x : this->b_inCategoryRates )
//        {
//          ss << std::to_string(x) << " ";
//        }
//    #endif /* RB_BEAGLE_DEBUG */
//
//    b_code_weights =
//        beagleSetCategoryWeights( this->beagle_instance
//                                , b_categoryWeightsIndex
//                                , &this->b_inCategoryWeights[0]
//                                );
//    if ( b_code_weights != 0 )
//    {
//	    throw RbException( "Could not set category weights for model : "
//	  		             + this->parseBeagleReturnCode(b_code_weights));
//    }
//
//	b_code_rates =
//	    beagleSetCategoryRatesWithIndex( this->beagle_instance
//                                       , 0 //(int) model
//                                       , &this->b_inCategoryRates[0]
//                                       );
//    if ( b_code_rates != 0 )
//    {
//	    throw RbException( "Could not set category rates for model : "
//	  		             + this->parseBeagleReturnCode(b_code_rates));
//    }
//
//    #if defined ( RB_BEAGLE_DEBUG )
//        RBOUT(ss.str());
//    #endif /* RB_BEAGLE_DEBUG */
//}


//template<class charType>
//void This::updateSubstitutionModels ( void )
//{
//    #if defined ( RB_BEAGLE_DEBUG )
//        std::stringstream ss;
//        ss << "Updating Models...\n";
//    #endif /* RB_BEAGLE_DEBUG */
//
//    //-- Substitution model indexing.
//    size_t                           b_model_idx;
//
//    //-- Discrete rate matrices for models.
//    const AbstractRateMatrix*        arm_ptr;
//    RbVector<MatrixReal>             rate_matrices;
//
//    //-- Stationary frequencies for models.
//    std::vector<std::vector<double>> model_pi_vectors;
//    size_t                           b_stateFrequenciesIndex;
//    std::vector<double>              b_inStateFrequencies;
//
//    //-- ASRV for models.
//    int                              b_categoryWeightsIndex;
//    std::vector<double>              b_inCategoryWeights;
//    std::vector<double>              b_inCategoryRates;
//
//    //-- Eigensystem for models.
//    std::vector<double>              b_flat_eigenvalues;
//    std::vector<double>              b_flat_eigenvectors;
//    std::vector<double>              b_flat_inv_eigenvectors;
//
//    //-- BEAGLE return codes for error checking.
//    int                              b_code_category_weights;
//    int                              b_code_category_rates;
//    int                              b_code_eigen_decomp;
//    int                              b_code_update_transitions;
//
//    //-- Eigensystem temporary structures.
//    #if defined ( RB_USE_EIGEN3 )
//        //-- New  Eigen library way... but requires 2 copies...
//        Eigen::EigenSolver<Eigen::MatrixXd>  eigen_system;
//        Eigen::MatrixXd                      rate_matrix(this->num_chars, this->num_chars);
//        Eigen::VectorXd                      eigenvalues;
//        Eigen::MatrixXd                      eigenvectors;
//        Eigen::MatrixXd                      inv_eigenvectors;
//    #else
//        //-- Old internal eigen system way... but may have bad eigenvectors...
//        EigenSystem*                         eigen_system;
//    #endif /* RB_BEAGLE_DEBUG */
//
//
//    //-- Get the 'root frequencies' (stationary distributions) for all models.
//    this->getRootFrequencies(model_pi_vectors);
//
//    //-- Set site rates for model.
//    if ( this->rate_variation_across_sites )
//    {
//        b_inCategoryWeights = this->site_rates_probs->getValue();
//        b_inCategoryRates   = this->site_rates->getValue();
//    }
//    else
//    {
//        b_inCategoryWeights = { 1.0 };
//        b_inCategoryRates   = { 1.0 };
//    }
//
//    #if defined ( RB_BEAGLE_DEBUG )
//        ss << "\tCategory weights : \n\t\t";
//        for ( auto x : b_inCategoryWeights )
//        {
//          ss << std::to_string(x) << " ";
//        }
//        ss << std::endl;
//        ss << "\tCategory rates : \n\t\t";
//        for ( auto x : b_inCategoryRates )
//        {
//          ss << std::to_string(x) << " ";
//        }
//        ss << std::endl << std::endl;
//    #endif /* RB_BEAGLE_DEBUG */
//
//    b_categoryWeightsIndex  = 0;  //-- ASRV index
//    b_code_category_weights =
//        beagleSetCategoryWeights( this->beagle_instance
//                                , b_categoryWeightsIndex
//                                , &b_inCategoryWeights[0]
//                                );
//    if ( b_code_category_weights != 0 )
//    {
//	    throw RbException( "Could not set category weights for models : "
//	  		             + this->parseBeagleReturnCode(b_code_category_weights));
//    }
//
//	b_code_category_rates =
//        beagleSetCategoryRates( this->beagle_instance
//                              , &b_inCategoryRates[0]
//                              );
//    //beagleSetCategoryRatesWithIndex( this->beagle_instance
//    //                               , b_categoryWeightsIndex
//    //                               , &b_inCategoryRates[0]
//    //                               );
//    if ( b_code_category_rates != 0 )
//    {
//	    throw RbException( "Could not set category rates for models : "
//	  		             + this->parseBeagleReturnCode(b_code_category_rates));
//    }
//
//
//    //-- Get the rate matrices of all models.
//    if ( this->homogeneous_rate_matrix )
//    {
//        //const AbstractRateMatrix* arm_ptr =
//        //    dynamic_cast<const AbstractRateMatrix*>(&this->homogeneous_rate_matrix->getValue());
//        arm_ptr = dynamic_cast<const AbstractRateMatrix*>(&this->homogeneous_rate_matrix->getValue());
//        rate_matrices.push_back(arm_ptr->getRateMatrix());
//    }
//    else
//    {
//        for ( size_t i = 0; i < this->heterogeneous_rate_matrices->getValue().size(); ++i )
//        {
//            //const AbstractRateMatrix* arm_ptr =
//            //    dynamic_cast<const AbstractRateMatrix*>(&this->heterogeneous_rate_matrices->getValue()[i]);
//            arm_ptr = dynamic_cast<const AbstractRateMatrix*>(&this->heterogeneous_rate_matrices->getValue()[i]);
//            rate_matrices.push_back(arm_ptr->getRateMatrix());
//        }
//    }
//
//
//    for ( size_t i = 0; i < this->num_site_mixtures; ++i )
//    {
//        //-- TODO : Maybe add checks to only update if eigensystem changes (use touched bitmap)
//
//        //-- Get correct model indices.
//        //model_idx = i + this->active_eigen_system[i] * this->num_site_mixtures;
//        b_model_idx             = this->active_eigen_system[i];  //-- Eigensystem index
//        b_stateFrequenciesIndex = i;                             //-- Pi vector index
//
//        #if defined ( RB_BEAGLE_DEBUG )
//            ss << "\tModel " <<  std::to_string(i) << " located at beagle model index "
//               << b_model_idx << std::endl;
//        #endif /* RB_BEAGLE_DEBUG */
//
//        //-- Set base frequencies for model.
//        b_inStateFrequencies    = model_pi_vectors[i];
//
//        #if defined ( RB_BEAGLE_DEBUG )
//            ss << "\tStationary Distribution : \n\t\t";
//            //for ( auto x : b_f )
//            for ( auto x : b_inStateFrequencies )
//            {
//              ss << std::to_string(x) << " ";
//            }
//            ss << std::endl;
//        #endif /* RB_BEAGLE_DEBUG */
//
//        beagleSetStateFrequencies( this->beagle_instance
//                                 , b_stateFrequenciesIndex
//                                 , &b_inStateFrequencies[0]
//                                 );
//
//
//        //-- Set eigensystem for model.
//        #if defined ( RB_USE_EIGEN3 )
//            //-- Copy into Eigen structure
//            for (size_t j = 0; j < this->num_chars; ++j )
//            {
//                for (size_t k = 0; k < this->num_chars; ++k )
//                {
//                    rate_matrix(j,k) = (rate_matrices[i])[j][k]; //-- Are there active/inactive rate_matrices?
//                }
//            }
//            //-- Build eigensystem
//            eigen_system.compute(rate_matrix, true); //-- compute eigen values and vectors
//
//            eigenvalues      = eigen_system.eigenvalues().real();
//            eigenvectors     = eigen_system.eigenvectors().real();
//            inv_eigenvectors = eigen_system.eigenvectors().inverse().real();
//
//            std::vector<double> flat_eigenvalues(eigenvalues.data(), eigenvalues.data() + eigenvalues.rows() * eigenvalues.cols());
//            std::vector<double> flat_eigenvectors(eigenvectors.data(), eigenvectors.data() + eigenvectors.rows() * eigenvectors.cols());
//            std::vector<double> flat_inv_eigenvectors(inv_eigenvectors.data(), inv_eigenvectors.data() + inv_eigenvectors.rows() * inv_eigenvectors.cols());
//
//            //-- Should at some point figure out a ways just to use eigen matrix data pointer instead of copy.
//            b_flat_eigenvalues      = flat_eigenvalues;
//            b_flat_eigenvectors     = flat_eigenvectors;
//            b_flat_inv_eigenvectors = flat_inv_eigenvectors;
//        #else
//            eigen_system            = &rate_matrices[i].getEigenSystem();
//            b_flat_eigenvalues      = eigen_system->getRealEigenvalues();
//            b_flat_eigenvectors     = eigen_system->getEigenvectors().flattenMatrix();
//            b_flat_inv_eigenvectors = eigen_system->getInverseEigenvectors().flattenMatrix();
//        #endif /* RB_USE_EIGEN3 */
//
//
//        #if defined ( RB_BEAGLE_DEBUG )
//            ss << "\tEigenvalues : \n\t\t";
//            for ( size_t j = 0; j < this->num_chars; ++j )
//            {
//                ss << std::fixed << std::setw(8) << std::setprecision(4)
//                   << b_flat_eigenvalues[j] << " ";
//            }
//            ss << "\n";
//            ss << "\tEigenvectors : ";
//            for ( size_t j = 0; j < this->num_chars * this->num_chars; ++j )
//            {
//                if ( (j % this->num_chars) == 0) { ss << "\n\t\t"; };
//                ss << std::fixed << std::setw(8) << std::setprecision(4)
//                   << b_flat_eigenvectors[j] << " ";
//            }
//            ss << "\n";
//            ss << "\tInverse Eigenvectors : ";
//            for ( size_t j = 0; j < this->num_chars * this->num_chars; ++j )
//            {
//                if ( (j % this->num_chars) == 0) { ss << "\n\t\t"; };
//                ss << std::fixed << std::setw(8) << std::setprecision(4)
//                   << b_flat_inv_eigenvectors[j] << " ";
//            }
//        #endif /* RB_BEAGLE_DEBUG */
//
//	    b_code_eigen_decomp =
//            beagleSetEigenDecomposition( this->beagle_instance
//                                       , b_model_idx
//                                       , &b_flat_eigenvectors[0]
//                                       , &b_flat_inv_eigenvectors[0]
//                                       , &b_flat_eigenvalues[0]
//                                       );
//        if ( b_code_eigen_decomp != 0 )
//        {
//	        throw RbException( "Could not set eigen decomposition for model '"
//                             + std::to_string(i) + "'. "
//                             + this->parseBeagleReturnCode(b_code_eigen_decomp));
//        }
//
//        //-- Update all transition matrices for model.
//        b_code_update_transitions =
//            beagleUpdateTransitionMatrices( this->beagle_instance
//                                          , b_model_idx
//                                          , &this->b_node_indices[0]
//                                          , NULL
//                                          , NULL
//                                          , &this->b_branch_lengths[0]
//                                          , this->b_branch_lengths.size()
//                                          );
//        if ( b_code_update_transitions != 0 )
//        {
//            throw RbException( "Could not update transition matrix for model '"
//                             + std::to_string(i) + "'. "
//                             + this->parseBeagleReturnCode(b_code_update_transitions));
//        }
//
//    }
//
//    //-- TODO : Do Eigen3 structs need freeing?
//
//    #if defined ( RB_BEAGLE_DEBUG )
//        RBOUT(ss.str());
//    #endif /* RB_BEAGLE_DEBUG */
//}

//--}

//----------------------------------------------------------------------[ Likelihood Calculations ]
//--{1

template<class charType>
double This::sumRootLikelihood (void )
{
    //computeLnProbability();

    #if defined ( RB_BEAGLE_DEBUG )
        std::stringstream ss;
        ss << std::endl << "SumRootlikelihood = "
           << std::to_string(this->ln_beagle_probability)
           << std::endl << std::endl;
        RBOUT(ss.str());
    #endif /* RB_BEAGLE_DEBUG */

    return this->ln_beagle_probability;
}



template<class charType>
void This::computeRootLikelihood ( size_t root, size_t left, size_t right )
{
    //-- TODO : Calculate the lnLikelihood for rooted trees. Should be able to copy the code for the
    //          unroooted case, but must change the child indexes/partials buffers.
}



template<class charType>
void This::computeRootLikelihood ( size_t root, size_t left, size_t right, size_t middle )
{
    #if defined ( RB_BEAGLE_DEBUG )
        std::stringstream ss;
        ss << "using beagle instance " << std::to_string(this->beagle_instance) << std::endl;
    #endif /* RB_BEAGLE_DEBUG */

    //-- Reset the stored probability.
    this->ln_beagle_probability = 0.0;

    size_t b_model_idx;
    size_t num_taxa  = (this->num_nodes + 2) / 2;

    size_t root_idx  = root + this->num_nodes * this->activeLikelihood[root];
    //this->b_node_indices.push_back(root_idx); //-- TESTING!

    size_t mid_idx   = middle + this->num_nodes * this->activeLikelihood[middle];
    size_t left_idx  = left   + this->num_nodes * this->activeLikelihood[left];
    size_t right_idx = right  + this->num_nodes * this->activeLikelihood[right];

    //-- Tips are actually just stored once, so we dont need offests.
    size_t mid_partials   = (middle < num_taxa) ? middle : mid_idx;
    size_t left_partials  = (left   < num_taxa) ? left   : left_idx;
    size_t right_partials = (right  < num_taxa) ? right  : right_idx;

    //-- Push the last operation onto the queue
    BeagleOperation b_operation =
        { .destinationPartials    = (int) root_idx
        , .destinationScaleWrite  = BEAGLE_OP_NONE
        , .destinationScaleRead   = BEAGLE_OP_NONE
        , .child1Partials         = (int) left_partials
        , .child1TransitionMatrix = (int) left_idx
        , .child2Partials         = (int) right_partials
        , .child2TransitionMatrix = (int) right_idx
        };
    this->b_ops.push_back(b_operation);  //-- TESTING

    //-- BEAGLE model parameters.
    int     b_parentBufferIndices     = (int) root_idx;
    int     b_childBufferIndices      = (int) mid_partials;
    int     b_probabilityIndices      = (int) mid_idx;
    int*    b_firstDerivativeIndices  = NULL;
    int*    b_secondDerivativeIndices = NULL;
    int     b_categoryWeightsIndices  = 0; //(int) model;  //0;
    int     b_stateFrequenciesIndices = 0; //(int) model;  //0;
    int     b_cumulativeScaleIndices  = BEAGLE_OP_NONE;
    int     b_count                   = 1;
    double  b_outSumLogLikelihood; //     = NULL; //0;
    double* b_outSumFirstDerivative   = NULL;
    double* b_outSumSecondDerivative  = NULL;

    //-- Return codes for BEAGLE operations.
    int b_code_update_transitions;
    int b_code_update_partials;
    int b_code_calc_edges;

    this->updateBeagleEigensystem();
    this->updateBeagleSiteRates();

    for ( size_t i = 0; i < this->num_site_mixtures; ++i )
    {
        b_model_idx = this->active_eigen_system[i];

        //-- Update all transition matrices for model i.
        b_code_update_transitions =
            beagleUpdateTransitionMatrices( this->beagle_instance
                                          , b_model_idx
                                          , &this->b_node_indices[0]
                                          , NULL
                                          , NULL
                                          , &this->b_branch_lengths[0]
                                          , this->b_branch_lengths.size()
                                          );
        if ( b_code_update_transitions != 0 )
        {
            throw RbException( "Could not update transition matrix for model '"
                             + std::to_string(i) + "'. "
                             + this->parseBeagleReturnCode(b_code_update_transitions));
        }
    }

    //-- Calculate and update all partial likelihood buffers
    b_code_update_partials = beagleUpdatePartials( this->beagle_instance
                                                 , &this->b_ops[0]
                                                 , this->b_ops.size()
                                                 , BEAGLE_OP_NONE
                                                 );
	if ( b_code_update_partials != 0 )
	{
        throw RbException( "Could not update partials for models '"
	  		             + this->parseBeagleReturnCode(b_code_update_partials));
	}

    //#if defined ( RB_BEAGLE_DEBUG )
    //    ss << "updated partials\n";
    //#endif /* RB_BEAGLE_DEBUG */

    //-- Reset the beagle operations queues
    this->b_ops.clear();
    this->b_branch_lengths.clear();
    this->b_node_indices.clear();

    //-- Calclulate the lnLikelihood of the model
    b_code_calc_edges =
        beagleCalculateEdgeLogLikelihoods( this->beagle_instance
                                         , &b_parentBufferIndices
                                         , &b_childBufferIndices
                                         , &b_probabilityIndices
                                         , b_firstDerivativeIndices
                                         , b_secondDerivativeIndices

                                         , &b_categoryWeightsIndices
                                         , &b_stateFrequenciesIndices

				                         , &b_cumulativeScaleIndices
                                         , b_count
                                         , &b_outSumLogLikelihood
                                         , b_outSumFirstDerivative
                                         , b_outSumSecondDerivative
                                         );
    if ( b_code_calc_edges != 0 )
    {
	    throw RbException("Could not calculate edge log likelihood for models '"
                          + this->parseBeagleReturnCode(b_code_calc_edges));
    }

    this->ln_beagle_probability = b_outSumLogLikelihood;

    //-- Reset the beagle operations queues
    //this->b_ops.clear();
    //this->b_branch_lengths.clear();
    //this->b_node_indices.clear();

    #if defined ( RB_BEAGLE_DEBUG )
        RBOUT(ss.str());
    #endif /* RB_BEAGLE_DEBUG */

}



template<class charType>
void This::computeInternalNodeLikelihood ( const TopologyNode &node
                                         , size_t node_index
                                         , size_t left
                                         , size_t right
                                         )
{
    double branch_length = calculateBranchLength(node, node_index);

    size_t node_idx  = node_index + this->num_nodes * this->activeLikelihood[node_index];
    size_t left_idx  = left       + this->num_nodes * this->activeLikelihood[left];
    size_t right_idx = right      + this->num_nodes * this->activeLikelihood[right];

    //-- Tips are actually just stored once, so we dont need offests.
    size_t left_partials  = (node.getChild(0).isTip()) ? left  : left_idx;
    size_t right_partials = (node.getChild(1).isTip()) ? right : right_idx;

    BeagleOperation b_operation =
        { .destinationPartials    = (int) node_idx
        , .destinationScaleWrite  = BEAGLE_OP_NONE
        , .destinationScaleRead   = BEAGLE_OP_NONE
        , .child1Partials         = (int) left_partials
        , .child1TransitionMatrix = (int) left_idx
        , .child2Partials         = (int) right_partials
        , .child2TransitionMatrix = (int) right_idx
        };

    this->b_ops.push_back(b_operation);
    this->b_node_indices.push_back(node_idx);
    this->b_branch_lengths.push_back(branch_length);
}



template<class charType>
void This::computeTipLikelihood ( const TopologyNode &node, size_t node_index )
{
    double branch_length = calculateBranchLength(node, node_index);
    this->b_branch_lengths.push_back(branch_length);

    size_t node_idx = node_index + this->num_nodes * this->activeLikelihood[node_index];
    this->b_node_indices.push_back(node_idx);
}

//--}


//--------------------------------------------------------------------------------------[ Cleanup ]
//--{1

//-- Undefine the local namespace shortcut
#undef This

#endif

//--}
