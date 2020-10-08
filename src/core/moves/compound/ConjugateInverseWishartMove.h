#ifndef ConjugateInverseWishartMove_H
#define ConjugateInverseWishartMove_H

#include <ostream>
#include <string>

#include "AbstractGibbsMove.h"

namespace RevBayesCore {
class DagNode;
class MatrixReal;
template <class variableType> class StochasticNode;
    
    class ConjugateInverseWishartMove : public AbstractGibbsMove {
        
    public:
        ConjugateInverseWishartMove(StochasticNode<MatrixReal>* s, double w);                                                         //!<  constructor
        virtual                                ~ConjugateInverseWishartMove(void);                                                             //!< Destructor
        
        // Basic utility functions
        ConjugateInverseWishartMove*            clone(void) const;                                                                  //!< Clone object
        const std::string&                      getMoveName(void) const;                                                            //!< Get the name of the move for summary printing
        
    protected:
        void                                    performGibbsMove(void);                                 //!< Perform move
        void                                    swapNodeInternal(DagNode *oldN, DagNode *newN);                                             //!< Swap the pointers to the variable on which the move works on.
        
    private:
        
        // member variables
        StochasticNode<MatrixReal>*             sigma;
        
    };
    
}

#endif
