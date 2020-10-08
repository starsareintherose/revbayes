#ifndef Dist_PhyloBranchRateBM_H
#define Dist_PhyloBranchRateBM_H

#include <math.h>
#include <iostream>
#include <string>
#include <vector>

#include "PhyloBranchRatesBM.h"
#include "ModelVector.h"
#include "RlTypedDistribution.h"
#include "RealPos.h"
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

    class Dist_PhyloBranchRateBM : public TypedDistribution< ModelVector<RealPos> > {
        
    public:
                                                        Dist_PhyloBranchRateBM( void ) {};
        virtual                                        ~Dist_PhyloBranchRateBM() {};
        
        // Basic utility functions
        Dist_PhyloBranchRateBM*                         clone(void) const;                                                                      //!< Clone the object
        static const std::string&                       getClassType(void);                                                                     //!< Get Rev type
        static const TypeSpec&                          getClassTypeSpec(void);                                                                 //!< Get class type spec
        std::vector<std::string>                        getDistributionFunctionAliases(void) const;                                             //!< Get the alternative names used for the constructor function in Rev.
        std::string                                     getDistributionFunctionName(void) const;                                                //!< Get the Rev-name for this distribution.
        const TypeSpec&                                 getTypeSpec(void) const;                                                                //!< Get the type spec of the instance
        const MemberRules&                              getParameterRules(void) const;                                                          //!< Get member rules (const)
        void                                            printValue(std::ostream& o) const;                                                      //!< Print the general information on the function ('usage')
        
        
        // Distribution functions you have to override
        RevBayesCore::PhyloBranchRatesBM*               createDistribution(void) const;
        
    protected:
        
        void                                            setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var);       //!< Set member variable
        
        
    private:
        
        RevPtr<const RevVariable>                       tree;
        RevPtr<const RevVariable>                       root_state;
        RevPtr<const RevVariable>                       sigma;
        RevPtr<const RevVariable>                       drift;
        
    };
    
}

#endif
