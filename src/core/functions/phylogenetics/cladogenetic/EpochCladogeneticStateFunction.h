//
//  EpochCladogeneticStateFunction.h
//  revbayes-proj
//
//  Created by Michael Landis on 10/23/16.
//  Copyright © 2016 Michael Landis. All rights reserved.
//

#ifndef EpochCladogeneticStateFunction_h
#define EpochCladogeneticStateFunction_h

#include <vector>
#include <map>

#include "AbstractCladogenicStateFunction.h"
#include "TypedFunction.h"
#include "CladogeneticProbabilityMatrix.h"

namespace RevBayesCore {
class DagNode;
template <class valueType> class RbVector;
template <class valueType> class TypedDagNode;
    
    class EpochCladogeneticStateFunction : public AbstractCladogenicStateFunction, public TypedFunction<CladogeneticProbabilityMatrix> {
        
    public:
        
        EpochCladogeneticStateFunction( const TypedDagNode< RbVector< double > >* et, const TypedDagNode< RbVector< CladogeneticProbabilityMatrix > >* cp, unsigned ns);
        virtual                                                 ~EpochCladogeneticStateFunction(void);                                              //!< Virtual destructor
        
        // public member functions
        EpochCladogeneticStateFunction*                         clone(void) const;                     //!< Create an independent clone
        std::map< std::vector<unsigned>, double >               getEventMap(double t=0.0);
        const std::map< std::vector<unsigned>, double >&        getEventMap(double t=0.0) const;
        
        void                                                    update(void);
        
    protected:
        
        void                                                    swapParameterInternal(const DagNode *oldP, const DagNode *newP);                        //!< Implementation of swaping parameters
        
    private:

        // members
        const TypedDagNode< RbVector<double> >*                 epochTimes;
        const TypedDagNode< RbVector<CladogeneticProbabilityMatrix> >*             cladoProbs;
        unsigned                                                numEpochs;

    };
    
}

#endif /* EpochCladogeneticStateFunction_h */
