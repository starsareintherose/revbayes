//---------------------------------------------------------------------------------------[ Header ]
//--{1

#ifndef PhyloCTMCSiteHomogeneousBEAGLE_H
#define PhyloCTMCSiteHomogeneousBEAGLE_H

#include "AbstractPhyloCTMCSiteHomogeneous.h"
#include "TopologyNode.h"

#include "RbVector.h"

//#include "DnaState.h"
//#include "RateMatrix.h"
//#include "TransitionProbabilityMatrix.h"
//#include "TypedDistribution.h"


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
            PhyloCTMCSiteHomogeneousBEAGLE* clone ( void ) const;                                                                                      //!< Create an independent clone


            //-- Destructor
            virtual ~PhyloCTMCSiteHomogeneousBEAGLE ( void );                                                                   //!< Virtual destructor


        protected:

            //----====  Protected Methods  ====----

            //-- BEAGLE compute lnLikelihood of a rooted tree.
            virtual void                computeRootLikelihood         ( size_t root
                                                                      , size_t l
                                                                      , size_t r
                                                                      );


            //-- BEAGLE compute lnLikelihood of an unrooted tree.
            virtual void                computeRootLikelihood         ( size_t root
                                                                      , size_t l
                                                                      , size_t r
                                                                      , size_t m
                                                                      );

            //-- Collect a BEAGLE operation for an internal node into the computation queue.
            virtual void                computeInternalNodeLikelihood ( const TopologyNode &n
                                                                      , size_t nIdx
                                                                      , size_t l
                                                                      , size_t r
                                                                      );

            //-- Collect a BEAGLE operation for a leaf node into the computation queue.
            virtual void                computeTipLikelihood          ( const TopologyNode &node
                                                                      , size_t nIdx
                                                                      );

            //-- Simple getter that returns the lnLikelihood for the tree.
            virtual double              sumRootLikelihood             ( void );

            //-- This is a no-op method that overrides the parent class transition matrix
            //update on tree traversals.
            //virtual void                updateTransitionProbabilities ( size_t node_idx );


            //virtual std::vector<double> getRootFrequencies            ( size_t mixture = 0 ) const;
            //virtual void                getRootFrequencies            ( std::vector<std::vector<double>>& ) const;


        private:

            //----====  Private Variables  ====----

            //-- Accumulate BEAGLE lnLikelihood across all models.
            double ln_beagle_probability;


            //----====  Private Methods  ====----

            //-- Set BEAGLE buffers for site-model mappings.
            void   setSitePatterns           ( void );

            //-- Set BEAGLE buffers for the the stationary distribution of a model.
            void   setStationaryDistribution ( void );

            //-- Set BEAGLE buffers for the ASRV distribution for a model.
            void   setSiteRateDistribution   ( void );

            //-- Set BEAGLE buffers for the substitution models.
            void   setSubstitutionModels     ( void );

            //-- Calculate the tree branch length between adjacent tree nodes..
            double calculateBranchLength     ( const TopologyNode &node
                                             , size_t node_index
                                             );

            //-- Generic BEAGLE lnLikelihood calculation for a tree.
            void   computeLikelihood         ( int               root_idx
                                             , std::vector<int>  child_idxs
                                             , std::vector<int>  prob_idxs
                                             );

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

}



template<class charType>
This::~PhyloCTMCSiteHomogeneousBEAGLE ( void )
{
    // We don't delete the parameters, because they might be used somewhere else too.
    // The model needs to do that!
}



template<class charType>
This* This::clone ( void ) const
{
    return new PhyloCTMCSiteHomogeneousBEAGLE<charType>(*this);
}

//--}

//------------------------------------------------------------------------------------[ Get / Set ]
//--{1

template<class charType>
double This::sumRootLikelihood ( void )
{
    //return this->lnProb;
    return this->ln_beagle_probability;
}



//template<class charType>
//std::vector<double> This::getRootFrequencies ( size_t mixture = 0 ) const
//{
//
//}
//
//
//
//template<class charType>
//void This::getRootFrequencies ( std::vector<std::vector<double>>& ) const
//{
//
//}

//--}

//------------------------------------------------------------------------------[ BEAGLE Updaters ]
//--{1

template<class charType>
void This::setSitePatterns ( void )
{
    this->b_inPatternWeights = std::vector<double>(this->pattern_block_size);
    for ( size_t b_pattern = 0; b_pattern < this->pattern_block_size; ++b_pattern )
    {
        this->b_inPatternWeights[b_pattern] = (double) this->pattern_counts[b_pattern];
    }

    beagleSetPatternWeights( this->beagle_instance
                           , &this->b_inPatternWeights[0]
                           );
}



template<class charType>
void This::setStationaryDistribution ( void )
{
    int                 b_stateFrequenciesIndex  = 0;
    std::vector<double> &b_inStateFrequencies    = ff[0];
    beagleSetStateFrequencies( this->beagle_instance
                             , b_stateFrequenciesIndex
                             , &b_inStateFrequencies[0]
                             );

    // get root frequencies
    //std::vector<std::vector<double>> ff;
    //this->getRootFrequencies(ff);
    //this->b_inStateFrequencies = ff[0];

    //this->b_stateFrequenciesIndex = 0;
    //beagleSetStateFrequencies( this->beagle_instance
    //                         , this->b_stateFrequenciesIndex
    //                         , &this->b_inStateFrequencies[0]
    //                         );
}



template<class charType>
void This::setSiteRateDistribution ( void )
{
    // site rate categories not yet supported
    this->b_categoryWeightsIndex = this->active_eigen_system[0];

    this->b_inCategoryWeights = { 1.0 };
    beagleSetCategoryWeights( this->beagle_instance
                            , this->b_categoryWeightsIndex
                            , &this->b_inCategoryWeights[0]
                            );

    this->b_inCategoryRates = { 1.0 };
    beagleSetCategoryRates( this->beagle_instance
                          , &this->b_inCategoryRates[0]
                          );
}



template<class charType>
void This::setSubstitutionModels ( void )
{
    RbVector<RateGenerator> rate_matrices;
    if ( this->homogeneous_rate_matrix )
    {
        rate_matrices.push_back(this->homogeneous_rate_matrix->getValue());
    }
    else
    {
        rate_matrices = this->heterogeneous_rate_matrices->getValue();
    }

    size_t              model_idx;
    EigenSystem*        eigen_system;
    std::vector<double> my_eigen_values;
    std::vector<double> flat_eigen_vectors;
    std::vector<double> flat_inv_eigen_vectors;

    size_t num_models = rate_matrices.size();
    for ( size_t i = 0; i < num_models; ++i )
    {
        eigen_system = rate_matrices[i].getEigenSystem();
        model_idx    = i + this->active_eigen_system[i] * num_models;

        my_eigen_values        = eigen_system->getRealEigenvalues();
        flat_eigen_vectors     = eigen_system->getEigenvectors().flattenMatrix();
        flat_inv_eigen_vectors = eigen_system->getInverseEigenvectors().flattenMatrix();

        beagleSetEigenDecomposition( this->beagle_instance
                                   , model_idx
                                   , &flat_eigen_vectors[0]
                                   , &flat_inv_eigen_vectors[0]
                                   , &my_eigen_values[0]
                                   );

        this->b_model_indices.push_back(model_idx);
    }
}



//template<class charType>
//void This::updateTransitionProbabilities ( size_t node_idx )
//{
//    //-- We dont need to do anything here since operations are collected and only
//    //   evaluated at the end.
//}

//--}

//-----------------------------------------------------------------------[ Private Helper Methods ]
//--{1

template<class charType>
double This::calculateBranchLength ( const TopologyNode &node, size_t node_index )
{
    double branch_time = node.getBranchLength();
    double rate = 1.0;
    if ( this->branch_heterogeneous_clock_rates == true )
    {
        rate = this->heterogeneous_clock_rates->getValue()[node_index];
    }
    else if ( this->homogeneous_clock_rate != NULL)
    {
        rate = this->homogeneous_clock_rate->getValue();
    }
    return rate * branch_time;
}



template<class charType>
void This::computeLikelihood ( int              b_parentBufferIndices
                             , std::vector<int> b_childBufferIndices
                             , std::vector<int> b_probabilityIndices )
{
    // Reset the likelihood
    this->lnProb = 0.0;
    //this->b_ops.clear();
    //this->b_branch_lengths.clear();
    //this->b_node_indices.clear();
    //this->b_model_indices.clear();
    //this->b_inStateFrequencies.clear();
    //this->b_inPatternWeights.clear();

    //int     b_parentBufferIndices     = root_idx;
    //int     b_childBufferIndices      = &child_buf_idxs;
    //int     b_probabilityIndices      = &prob_buf_idxs;
    int*    b_firstDerivativeIndices  = NULL;
    int*    b_secondDerivativeIndices = NULL;
    int     b_cumulativeScaleIndices  = BEAGLE_OP_NONE;
    int     b_count                   = 1;
    double  b_outSumLogLikelihood     = 0;
    double* b_outSumFirstDerivative   = NULL;
    double* b_outSumSecondDerivative  = NULL;

    this->setSitePatterns();
    this->setStationaryDistribution();
    this->setSiteRateDistribution();
    this->setSubstitutionModels();

    this->ln_beagle_probability = 0;
    for ( auto model : this->b_model_indices )
    {
        beagleUpdateTransitionMatrices( this->beagle_instance
                                      , model
                                      , &this->b_node_indices[0]
                                      , NULL
                                      , NULL
                                      , &this->b_branch_lengths[0]
                                      , this->b_branch_lengths.size()
                                      );

        //-- Calculate and update all partial likelihood buffers
        beagleUpdatePartials( this->beagle_instance
                            , &this->b_ops[0]
                            , this->b_ops.size()
                            , BEAGLE_OP_NONE
                            );

        //-- Calclulate the lnLikelihood of the model
        beagleCalculateEdgeLogLikelihoods( this->beagle_instance
                                         , &b_parentBufferIndices
                                         , &b_childBufferIndices[0]
                                         , &b_probabilityIndices[0]
                                         , b_firstDerivativeIndices
                                         , b_secondDerivativeIndices
                                         , &this->b_categoryWeightsIndex
                                         , &this->b_stateFrequenciesIndex
                                         , &b_cumulativeScaleIndices
                                         , b_count
                                         , &b_outSumLogLikelihood
                                         , b_outSumFirstDerivative
                                         , b_outSumSecondDerivative
                                         );

        this->ln_beagle_probability += b_outSumLogLikelihood;
    }

    //-- Store the resulting likelihood
    //   Not sure why there is ln_beagle_probability and lnProb here...
    //this->lnProb = this->ln_beagle_probability;


    // reset the beagle operations queues
    this->b_ops.clear();
    this->b_branch_lengths.clear();
    this->b_node_indices.clear();
    this->b_model_indices.clear();
    this->b_inStateFrequencies.clear();
    this->b_inPatternWeights.clear();

}

//--}

//----------------------------------------------------------------------[ Likelihood Calculations ]
//--{1

template<class charType>
void This::computeRootLikelihood ( size_t root, size_t left, size_t right )
{
    size_t num_taxa  = (this->num_nodes + 2) / 2;
    size_t root_idx  = root   + this->num_nodes * this->activeLikelihood[root];
    size_t left_idx  = (left < num_taxa) ? left
                     : left + this->num_nodes * this->activeLikelihood[left];
    size_t right_idx = (right < num_taxa) ? right
                     : right + this->num_nodes * this->activeLikelihood[right];

    //-- Push the last operation onto the queue
    BeagleOperation b_operation;
    b_operation.destinationScaleWrite  = BEAGLE_OP_NONE;
    b_operation.destinationScaleRead   = BEAGLE_OP_NONE;
    b_operation.destinationPartials    = root_idx;
    b_operation.child1TransitionMatrix = left_idx;
    b_operation.child2TransitionMatrix = right_idx;
    b_operation.child1Partials         = left_idx;
    b_operation.child2Partials         = right_idx;
    this->b_ops.push_back(b_operation);

    std::vector<int> child_buf_idxs = { };
    std::vector<int> prob_buf_idxs  = { };

    this->computeLikelihood ( root_idx
                            , child_buf_idxs
                            , prob_buf_idxs
                            );
}



template<class charType>
void This::computeRootLikelihood ( size_t root, size_t left, size_t right, size_t middle )
{
    //size_t root_idx  = root   + this->num_nodes * this->activeLikelihood[root];
    //size_t mid_idx   = middle + this->num_nodes * this->activeLikelihood[middle];
    //size_t left_idx  = left   + this->num_nodes * this->activeLikelihood[left];
    //size_t right_idx = right  + this->num_nodes * this->activeLikelihood[right];

    size_t num_taxa  = (this->num_nodes + 2) / 2;
    size_t root_idx  = root   + this->num_nodes * this->activeLikelihood[root];
    size_t mid_idx   = middle + this->num_nodes * this->activeLikelihood[middle];
    size_t left_idx  = (left < num_taxa) ? left
                     : left + this->num_nodes * this->activeLikelihood[left];
    size_t right_idx = (right < num_taxa) ? right
                     : right + this->num_nodes * this->activeLikelihood[right];

    //-- Push the last operation onto the queue
    BeagleOperation b_operation;
    b_operation.destinationScaleWrite  = BEAGLE_OP_NONE;
    b_operation.destinationScaleRead   = BEAGLE_OP_NONE;
    b_operation.destinationPartials    = root_idx;
    b_operation.child1TransitionMatrix = left_idx;
    b_operation.child2TransitionMatrix = right_idx;
    b_operation.child1Partials         = left_idx;
    b_operation.child2Partials         = right_idx;
    this->b_ops.push_back(b_operation);

    std::vector<int> child_buf_idxs = { (int) mid_idx };
    std::vector<int> prob_buf_idxs  = { (int) mid_idx };

    this->computeLikelihood ( root_idx
                            , child_buf_idxs
                            , prob_buf_idxs
                            );
}



template<class charType>
void This::computeInternalNodeLikelihood ( const TopologyNode &node
                                         , size_t node_index
                                         , size_t left
                                         , size_t right
                                         )
{

    size_t node_idx  = node_index + this->num_nodes * this->activeLikelihood[node_index];
    size_t left_idx  = (node.getChild(0).isTip()) ? left
                     : left + this->num_nodes * this->activeLikelihood[left];
    size_t right_idx = (node.getChild(1).isTip()) ? right
                     : right + this->num_nodes * this->activeLikelihood[right];

    BeagleOperation b_operation;
    b_operation.destinationPartials    = node_idx;
    b_operation.destinationScaleWrite  = BEAGLE_OP_NONE;
    b_operation.destinationScaleRead   = BEAGLE_OP_NONE;
    b_operation.child1Partials         = left_idx;
    b_operation.child2Partials         = right_idx;
    b_operation.child1TransitionMatrix = left_idx;
    b_operation.child2TransitionMatrix = right_idx;

    double branch_length = calculateBranchLength(node, node_index);

    this->b_ops.push_back(b_operation);
    this->b_branch_lengths.push_back(branch_length);
    this->b_node_indices.push_back(node_idx);
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


