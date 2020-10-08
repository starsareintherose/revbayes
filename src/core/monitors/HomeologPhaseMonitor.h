#ifndef HomeologPhaseMonitor_H
#define HomeologPhaseMonitor_H
#include <fstream>
#include <string>

#include "VariableMonitor.h"

namespace RevBayesCore {
class AbstractHomologousDiscreteCharacterData;
class DagNode;
template <class variableType> class StochasticNode;
    
    class HomeologPhaseMonitor : public VariableMonitor {
        
    public:
        // Constructors and Destructors
		HomeologPhaseMonitor(StochasticNode<AbstractHomologousDiscreteCharacterData>* ch, unsigned long g, const std::string &fname, const std::string &del);                                  //!< Constructor
        virtual ~HomeologPhaseMonitor(void);
        
        HomeologPhaseMonitor*          clone(void) const;                                                  //!< Clone the object
        
        // functions you may want to overwrite
        virtual void                                    monitorVariables(unsigned long gen);                                //!< Monitor at generation gen
        virtual void                                    printFileHeader(void);                                              //!< Print header
        virtual void                                    swapNode(DagNode *oldN, DagNode *newN);

    private:
        
        // members
		StochasticNode<AbstractHomologousDiscreteCharacterData>*            ctmc;
    };
    
}


#endif 
