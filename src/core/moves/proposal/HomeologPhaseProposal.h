#ifndef HomeologPhaseProposal_H
#define HomeologPhaseProposal_H

#include <iostream>
#include <string>

#include "Proposal.h"

namespace RevBayesCore {
class AbstractHomologousDiscreteCharacterData;
class DagNode;
template <class variableType> class StochasticNode;


    class HomeologPhaseProposal : public Proposal {

    public:
        HomeologPhaseProposal( StochasticNode<AbstractHomologousDiscreteCharacterData> *c, std::string t1, std::string t2);                                  //!<  constructor

        // Basic utility functions
        HomeologPhaseProposal*                                      clone(void) const;                                              //!< Clone object
        void                                                        cleanProposal(void);
        double                                                      doProposal(void);                                               //!< Perform proposal
        const std::string&                                          getProposalName(void) const;                                    //!< Get the name of the proposal for summary printing
        double                                                      getProposalTuningParameter(void) const;
        void                                                        prepareProposal(void);                                                              //!< Propose a new state
        void                                                        printParameterSummary(std::ostream &o, bool name_only) const;                   //!< Print the parameter summary
        void                                                        setProposalTuningParameter(double tp);
        void                                                        tune(double r);                                                                     //!< Tune the parameters of the proposal.
        void                                                        undoProposal(void);                                             //!< Reject the proposal

    protected:

        void                                                        swapNodeInternal(DagNode *oldN, DagNode *newN);                 //!< Swap the DAG nodes on which the Proposal is working on

        // parameters
        StochasticNode<AbstractHomologousDiscreteCharacterData>*    ctmc;
        std::string                                                 tip1;
        std::string                                                 tip2;
    

    };

}

#endif 
