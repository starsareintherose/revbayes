#ifndef HeterochronousCoalescent_H
#define HeterochronousCoalescent_H

#include <stddef.h>
#include <vector>

#include "AbstractCoalescent.h"
#include "DemographicFunction.h"
#include "RbVector.h"
#include "RbVectorImpl.h"

namespace RevBayesCore {
    
    class Clade;
class DagNode;
class Taxon;
template <class valueType> class TypedDagNode;
    
    
    
    /**
     * @brief Constant population size coalescent process.
     *
     *
     * The constant population size coalescent process is the simplest available coalescent process.
     * It contains only a single parameter NE, the population size.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (Sebastian Hoehna)
     * @since 2014-01-17, version 1.0
     *
     */
    class HeterochronousCoalescent : public AbstractCoalescent {
        
    public:
        HeterochronousCoalescent(const TypedDagNode< RbVector<double> > *iv, const RbVector< DemographicFunction > &df, const std::vector<Taxon> &tn, const std::vector<Clade> &c);
//        HeterochronousCoalescent(const HeterochronousCoalescent &d);
        virtual                                            ~HeterochronousCoalescent(void);                                                                 //!< Virtual destructor
        
//        HeterochronousCoalescent&                           operator=(const HeterochronousCoalescent &d);

        // public member functions
        HeterochronousCoalescent*                           clone(void) const;                                                                              //!< Create an independent clone
        
    protected:
        // Parameter management functions
        void                                                swapParameterInternal(const DagNode *oldP, const DagNode *newP);                                //!< Swap a parameter
        
        // derived helper functions
        double                                              computeLnProbabilityTimes(void) const;                                                          //!< Compute the log-transformed probability of the current value.
        std::vector<double>                                 simulateCoalescentAges(size_t n) const;                                                         //!< Simulate n coalescent events.
        
        
    private:
        
        enum EVENT_TYPE { COALESCENT, SERIAL_SAMPLE, DEMOGRAPHIC_MODEL_CHANGE };
        
        // members
        const TypedDagNode< RbVector<double> >*             intervals;
        RbVector< DemographicFunction >                     demographies;
    };
    
}

#endif
