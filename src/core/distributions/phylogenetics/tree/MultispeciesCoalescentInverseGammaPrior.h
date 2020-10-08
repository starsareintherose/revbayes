#ifndef MultispeciesCoalescentInverseGammaPrior_H
#define MultispeciesCoalescentInverseGammaPrior_H

#include <stddef.h>
#include <vector>

#include "AbstractMultispeciesCoalescent.h"

namespace RevBayesCore {
class DagNode;
class Taxon;
class Tree;
template <class valueType> class TypedDagNode;
    
    class MultispeciesCoalescentInverseGammaPrior : public AbstractMultispeciesCoalescent {
        
    public:
        MultispeciesCoalescentInverseGammaPrior(const TypedDagNode<Tree> *st, const std::vector<Taxon> &t);
        virtual                                            ~MultispeciesCoalescentInverseGammaPrior(void);                                                                       //!< Virtual destructor
        
        // public member functions
        MultispeciesCoalescentInverseGammaPrior*            clone(void) const;                                                                                  //!< Create an independent clone
        void                                                setShape(TypedDagNode<double>* s);
        void                                                setRate(TypedDagNode<double>* r);
        
    protected:
        // Parameter management functions
        void                                                swapParameterInternal(const DagNode *oldP, const DagNode *newP);            //!< Swap a parameter
        double                                              computeLnCoalescentProbability(size_t k, const std::vector<double> &t, double a, double b, size_t index, bool f);
        double                                              drawNe(size_t index);
        
        
        
    private:
        
        // members
        const TypedDagNode<double>*                          shape;
        const TypedDagNode<double>*                          rate;

    };
    
}

#endif
