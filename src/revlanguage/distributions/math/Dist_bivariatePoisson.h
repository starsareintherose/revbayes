#ifndef Dist_bivariatePoisson_h
#define Dist_bivariatePoisson_h

#include <math.h>
#include <iosfwd>
#include <string>
#include <vector>

#include "BivariatePoissonDistribution.h"
#include "Natural.h"
#include "ModelVector.h"
#include "RlTypedDistribution.h"
#include "ConstantNode.h"
#include "DagMemberFunction.h"
#include "DagNode.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "IndirectReferenceFunction.h"
#include "ModelObject.h"
#include "RbVector.h"
#include "RevObject.h"
#include "RevPtr.h"
#include "RevVariable.h"
#include "RlConstantNode.h"
#include "RlDagMemberFunction.h"
#include "RlDeterministicNode.h"
#include "RlStochasticNode.h"
#include "RlTypedFunction.h"
#include "StochasticNode.h"
#include "TypedDagNode.h"
#include "TypedDistribution.h"
#include "TypedFunction.h"
#include "UserFunctionNode.h"

namespace RevLanguage {
class TypeSpec;

    /**
     * The RevLanguage wrapper of the Bivariate Poisson distribution.
     *
     * The RevLanguage wrapper of the bivariate Poisson distribution simply
     * manages the interactions through the Rev with our core. That is, the
     * internal distribution object can be constructed and hooked up in a model
     * graph.
     *
     * @copyright Copyright 2009-
     * @author Alexander E. Zarebski
     * @since 2014-03-18, version 1.0
     *
     */
    class Dist_bivariatePoisson : public TypedDistribution< ModelVector<Natural> > {

    public:
        Dist_bivariatePoisson( void );                                                                                                                           //!< Default constructor

        // Basic utility functions
        Dist_bivariatePoisson*                          clone(void) const;                                                                              //!< Clone the object
        static const std::string&                       getClassType(void);                                                                             //!< Get Rev type
        static const TypeSpec&                          getClassTypeSpec(void);                                                                         //!< Get class type spec
        std::vector<std::string>                        getDistributionFunctionAliases(void) const;                                                     //!< Get the alternative names used for the constructor function in Rev.
        std::string                                     getDistributionFunctionName(void) const;                                                        //!< Get the Rev-name for this distribution.
        const TypeSpec&                                 getTypeSpec(void) const;                                                                        //!< Get the type spec of the instance
        const MemberRules&                              getParameterRules(void) const;                                                                  //!< Get member rules (const)


        // Distribution functions you have to override
        RevBayesCore::BivariatePoissonDistribution*     createDistribution(void) const;                                                                 //!< Create the internal distribution object

    protected:

        void                                            setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var);               //!< Set member variable


    private:

        RevPtr<const RevVariable>                       theta1;
        RevPtr<const RevVariable>                       theta2;
        RevPtr<const RevVariable>                       theta0;
    };

}


#endif
