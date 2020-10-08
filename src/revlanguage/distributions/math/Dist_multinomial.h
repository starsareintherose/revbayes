#ifndef Dist_multinomial_H
#define Dist_multinomial_H

#include <math.h>
#include <iosfwd>
#include <string>
#include <vector>

#include "MultinomialDistribution.h"
#include "ModelVector.h"
#include "Natural.h"
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
     * The RevLanguage wrapper of the multinomial distribution.
     *
     * The RevLanguage wrapper of the multinomial distribution simply
     * manages the interactions through the Rev with our core.
     * That is, the internal distribution object can be constructed and hooked up
     * in a model graph.
     * See the MultinomialDistribution for more details.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (Sebastian Hoehna)
     * @since 2015-04-19, version 1.0
     *
     */
    class Dist_multinomial : public TypedDistribution< ModelVector<Natural> > {
        
    public:
        Dist_multinomial(void);
        virtual                                        ~Dist_multinomial(void);
        
        // Basic utility functions
        Dist_multinomial*                               clone(void) const;                                                                      //!< Clone the object
        static const std::string&                       getClassType(void);                                                                     //!< Get Rev type
        static const TypeSpec&                          getClassTypeSpec(void);                                                                 //!< Get class type spec
        const TypeSpec&                                 getTypeSpec(void) const;                                                                //!< Get the type spec of the instance
        std::string                                     getDistributionFunctionName(void) const;                                                //!< Get the Rev-name for this distribution.
        const MemberRules&                              getParameterRules(void) const;                                                          //!< Get member rules (const)
        void                                            printValue(std::ostream& o) const;                                                      //!< Print the general information on the function ('usage')
        
        
        // Distribution functions you have to override
        RevBayesCore::MultinomialDistribution*          createDistribution(void) const;
        
    protected:
        
        void                                            setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var);       //!< Set member variable
        
        
    private:
        
        RevPtr<const RevVariable>                       p;
        RevPtr<const RevVariable>                       n;
    };
    
}

#endif
