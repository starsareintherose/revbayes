
  
#ifndef DivergenceTimeBinaryRateProposal_H
#define DivergenceTimeBinaryRateProposal_H

#include <iosfwd>

#include "Proposal.h"

#include "RlMonitor.h"
#include "RevObject.h"
#include "RevPtr.h"
#include "RevVariable.h"
#include "TypedDagNode.h"
#include "AbstractPhyloCTMCSiteHomogeneous.h"
#include "MetropolisHastingsMove.h"


namespace RevBayesCore {
    

template<class characterType>
class DivergenceTimeBinaryRateProposal : public Proposal {
        
    public:
        
        DivergenceTimeBinaryRateProposal(StochasticNode<AbstractHomologousDiscreteCharacterData> *n);                                                                              //!<  constructor
        void                                            cleanProposal(void);                                                                //!< Clean up proposal
        DivergenceTimeBinaryRateProposal*              clone(void) const;                                                                  //!< Clone object
        double                                          doProposal(void);                                                                   //!< Perform proposal
        const std::string&                              getProposalName(void) const;                                                        //!< Get the name of the proposal for summary printing
        double                                          getProposalTuningParameter(void) const;

        void                                            prepareProposal(void);                                                              //!< Prepare the proposal
        void                                            printParameterSummary(std::ostream &o, bool name_only) const;                                       //!< Print the parameter summary
        void                                            setProposalTuningParameter(double tp);
        void                                            tune(double r);                                                                     //!< Tune the proposal to achieve a better acceptance/rejection ratio
        void                                            undoProposal(void);                                                                 //!< Reject the proposal
        
    protected:

        void                                            swapNodeInternal(DagNode *oldN, DagNode *newN);                                     //!< Swap the DAG nodes on which the Proposal is working on
        
        AbstractPhyloCTMCSiteHomogeneous<characterType>*      ctmc_dist;

    private:
        
        StochasticNode<AbstractHomologousDiscreteCharacterData>*     ctmc;                                            //!< The variable the Proposal is working on
        TypedDagNode<Tree>*                             tree;
        size_t                                          index;


        
    };
    
}


#include <stddef.h>
#include <typeinfo>
#include <vector>

#include "RbException.h"
#include "StateDependentSpeciationExtinctionProcess.h"
#include "Tree.h"
#include "AbstractHomologousDiscreteCharacterData.h"
#include "Cloneable.h"
#include "StochasticNode.h"
#include "TypedDistribution.h"

#include "AbstractPhyloCTMCSiteHomogeneous.h"
#include "DagNode.h"
#include "Proposal.h"


namespace RevBayesCore { class DagNode; }

using namespace RevBayesCore;

/**
 * Constructor
 *
 * Here we simply allocate and initialize the Proposal object.
 */
template<class characterType>
DivergenceTimeBinaryRateProposal<characterType>::DivergenceTimeBinaryRateProposal( StochasticNode<AbstractHomologousDiscreteCharacterData>* n ):
        Proposal(), ctmc( n ),
        index(0)
{

    // add the node to the base class
    AbstractPhyloCTMCSiteHomogeneous<characterType> *ctmc_dist = NULL;
    ctmc_dist = static_cast<AbstractPhyloCTMCSiteHomogeneous<characterType>* >( &ctmc->getDistribution() );
    tree = const_cast<TypedDagNode<Tree>* >( ctmc_dist->getTree() );
    
    addNode( ctmc );

}


/**
 * The cleanProposal function may be called to clean up memory allocations after AbstractMove
 * decides whether to accept, reject, etc. the proposed value.
 *
 */
template<class characterType>
void DivergenceTimeBinaryRateProposal<characterType>::cleanProposal( void )
{
    
    
}


template<class characterType>
DivergenceTimeBinaryRateProposal<characterType>* DivergenceTimeBinaryRateProposal<characterType>::clone( void ) const
{
    return new DivergenceTimeBinaryRateProposal<characterType>( *this );
}

/**
 * Perform the proposal.
 *
 * \return The hastings ratio.
 */
template<class characterType>
double DivergenceTimeBinaryRateProposal<characterType>::doProposal( void )
{
    
    size_t num_nodes;
    num_nodes = tree->getValue().getNumberOfNodes();
    
    std::vector<std::string> character_histories(num_nodes);

    // draw stochastic character map
    index = 1; // Note that for now it's only calculated for a single index (index is initialized to 0 in the constructor)
    ctmc_dist->drawStochasticCharacterMap( character_histories, index, true );
    
    // extract the branches that follow each rate
    
    
//    double log_augmented_likelihood = ctmc_dist->log_augmented_likelihood;
    
    return 0.0;
}


template<class characterType>
const std::string& DivergenceTimeBinaryRateProposal<characterType>::getProposalName( void ) const
{
    static std::string name = "DivergenceTimeBinaryRateProposal";
    return name;
}


template<class characterType>
double DivergenceTimeBinaryRateProposal<characterType>::getProposalTuningParameter( void ) const
{
    // this proposal has no tuning parameter
    return RbConstants::Double::nan;
}


template<class characterType>
void DivergenceTimeBinaryRateProposal<characterType>::prepareProposal( void )
{
    
}


template<class characterType>
void DivergenceTimeBinaryRateProposal<characterType>::printParameterSummary(std::ostream &o, bool name_only) const
{


}


template<class characterType>
void DivergenceTimeBinaryRateProposal<characterType>::undoProposal( void )
{
    
    
}


/**
 * Swap the current variable for a new one.
 *
 * \param[in]     oldN     The old ctmc that needs to be replaced.
 * \param[in]     newN     The new RevVariable.
 */
template<class characterType>
void DivergenceTimeBinaryRateProposal<characterType>::swapNodeInternal(DagNode *oldN, DagNode *newN)
{

    ctmc = static_cast< StochasticNode<AbstractHomologousDiscreteCharacterData>* >(newN) ;

    ctmc_dist = dynamic_cast< AbstractPhyloCTMCSiteHomogeneous<characterType>* >( &ctmc->getDistribution() );
    if ( ctmc_dist == NULL )
    {
        throw RbException("The DivergenceTimeBinaryRateProposal is currently only implemented for CDBDP distributions.");
    }
}

template<class characterType>
void DivergenceTimeBinaryRateProposal<characterType>::setProposalTuningParameter(double tp)
{
    // this proposal has no tuning parameter: nothing to do
}


template<class characterType>
void DivergenceTimeBinaryRateProposal<characterType>::tune( double rate )
{
    
    
}

#endif
