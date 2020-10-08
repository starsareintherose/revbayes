#ifndef ContinuousEventBirthDeathProposal_H
#define ContinuousEventBirthDeathProposal_H

#include <string>
#include <iosfwd>

#include "EventBirthDeathProposal.h"

namespace RevBayesCore {
    
    class CharacterEvent;
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
    class ContinuousEventBirthDeathProposal : public EventBirthDeathProposal {
        
    public:
        ContinuousEventBirthDeathProposal( StochasticNode<Tree> *n);                                                                //!<  constructor
        
        // Basic utility functions
        ContinuousEventBirthDeathProposal*        clone(void) const;                                                                  //!< Clone object
        const std::string&                      getProposalName(void) const;                                                        //!< Get the name of the proposal for summary printing
        
    protected:
        
        // pure virtual methods
        CharacterEvent*                         drawNewEvent(double event_time);
        double                                  computeEventProposalProbability( CharacterEvent* event );
        
    };
    
}

#endif


