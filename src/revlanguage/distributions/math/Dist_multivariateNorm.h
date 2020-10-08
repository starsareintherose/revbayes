#ifndef Dist_multivariateNorm_H
#define Dist_multivariateNorm_H

#include <math.h>
#include <iosfwd>
#include <string>
#include <vector>

#include "MultivariateNormalDistribution.h"
#include "RlTypedDistribution.h"
#include "ModelVector.h"
#include "Real.h"
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
     * The RevLanguage wrapper of the multivariate normal distribution.
     *
     * The RevLanguage wrapper of the multivariate normal distribution takes care of create the internal distribution object
     * and provides the RevLanguage object that can be used within Rev.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (John Huelsenbeck and Risa Takenaka)
     * @since 2012-08-06, version 1.0
     *
     */
    class Dist_multivariateNorm :  public TypedDistribution<ModelVector<Real> > {
    
    public:
                                                        Dist_multivariateNorm( void );
    
        // Basic utility functions
        Dist_multivariateNorm*                          clone(void) const;                                                                      //!< Clone the object
        static const std::string&                       getClassType(void);                                                                     //!< Get Rev type
        static const TypeSpec&                          getClassTypeSpec(void);                                                                 //!< Get class type spec
        std::string                                     getDistributionFunctionName(void) const;                                                //!< Get the Rev-name for this distribution.
        const TypeSpec&                                 getTypeSpec(void) const;                                                                //!< Get the type spec of the instance
        const MemberRules&                              getParameterRules(void) const;                                                          //!< Get member rules (const)
        
//        // Member method functions
//        virtual RevPtr<RevVariable>                     executeMethod(const std::string& name, const std::vector<Argument>& args, bool &f);     //!< Map member methods to internal functions
//        virtual const MethodTable&                      getMethods(void) const;                                                                     //!< Get member methods

    
        // Distribution functions you have to override
        RevBayesCore::MultivariateNormalDistribution*   createDistribution(void) const;
    
    protected:
    
        void                                            setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var);       //!< Set member variable

    
    private:
        
        RevPtr<const RevVariable>                       mean;
        RevPtr<const RevVariable>                       covariance;
        RevPtr<const RevVariable>                       precision;
        RevPtr<const RevVariable>                       scale;
        
    };
    
}

#endif
