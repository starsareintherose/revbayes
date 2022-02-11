#ifndef ConcreteTimeReversibleRateMatrix_H
#define ConcreteTimeReversibleRateMatrix_H

#include "TimeReversibleRateMatrix.h"
#include <complex>
#include <vector>


namespace RevBayesCore {

    class TransitionProbabilityMatrix;

    /**
     * @brief Concrete GTR
     *
     * @copyright Copyright 2021-
     * @author Benjamin D Redelings
     * @since 2021-11-24, version 1.0
     */
    class ConcreteTimeReversibleRateMatrix : public TimeReversibleRateMatrix
    {

    public:
        ConcreteTimeReversibleRateMatrix(const std::vector<double>& er, const std::vector<double>& pi);
        ConcreteTimeReversibleRateMatrix(const ConcreteTimeReversibleRateMatrix& m) = default;

        // RateMatrix functions
        virtual ConcreteTimeReversibleRateMatrix&               assign(const Assignable &m);
        ConcreteTimeReversibleRateMatrix*                       clone(void) const;

        void                                                    calculateTransitionProbabilities(double startAge, double endAge, double rate, TransitionProbabilityMatrix& P) const;

        void                                                    update(void);
    };
}

#endif

