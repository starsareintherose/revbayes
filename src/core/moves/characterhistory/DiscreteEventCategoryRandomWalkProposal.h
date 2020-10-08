#ifndef DiscreteEventCategoryRandomWalkProposal_H
#define DiscreteEventCategoryRandomWalkProposal_H

#include <stddef.h>
#include <string>
#include <iosfwd>

#include "Proposal.h"

namespace RevBayesCore {
class CharacterEventDiscrete;
class DagNode;
class HeterogeneousRateBirthDeath;
class Tree;
template <class variableType> class StochasticNode;
    
    /**
     * The birth-death proposal for events along a tree.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team
     * @since 2009-09-08, version 1.0
     *
     */
    class DiscreteEventCategoryRandomWalkProposal : public Proposal {
        
    public:
        DiscreteEventCategoryRandomWalkProposal( StochasticNode<Tree> *n);                                                                //!<  constructor
        
        // Basic utility functions
        void                                            cleanProposal(void);                                                                //!< Clean up proposal
        DiscreteEventCategoryRandomWalkProposal*        clone(void) const;                                                                  //!< Clone object
        double                                          doProposal(void);                                                                   //!< Perform proposal
        const std::string&                              getProposalName(void) const;                                                        //!< Get the name of the proposal for summary printing
        double                                          getProposalTuningParameter(void) const;
        void                                            printParameterSummary(std::ostream &o, bool name_only) const;                                       //!< Print the parameter summary
        void                                            prepareProposal(void);                                                              //!< Prepare the proposal
        void                                            setProposalTuningParameter(double tp);
        void                                            tune(double r);                                                                     //!< Tune the proposal to achieve a better acceptance/rejection ratio
        void                                            undoProposal(void);                                                                 //!< Reject the proposal
        
    protected:
        
        void                                            swapNodeInternal(DagNode *oldN, DagNode *newN);                                     //!< Swap the DAG nodes on which the Proposal is working on
        
    private:
        // parameters
        
        StochasticNode<Tree>*                           variable;                                                                           //!< The variable the Proposal is working on
        HeterogeneousRateBirthDeath*                    distribution;
        
        CharacterEventDiscrete*                         stored_value;                                                                        //!< The stored value of the Proposal used for rejections.
        size_t                                          stored_category;                                                                              //!< The value we propose.
        bool                                            failed;
    };
    
}

#endif

