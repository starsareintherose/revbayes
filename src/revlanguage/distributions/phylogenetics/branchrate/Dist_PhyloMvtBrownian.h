#ifndef Dist_PhyloMvtBrownian_H
#define Dist_PhyloMvtBrownian_H

#include <math.h>
#include <iostream>
#include <string>
#include <vector>

#include "PhyloMultivariateBrownianProcess.h"
#include "RlTypedDistribution.h"
#include "Real.h"
#include "ModelVector.h" // IWYU pragma: keep
#include "ConstantNode.h"
#include "DagMemberFunction.h"
#include "DagNode.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "IndirectReferenceFunction.h"
#include "ModelObject.h"
#include "RbVector.h"
#include "RbVectorImpl.h"
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

    class Dist_PhyloMvtBrownian :  public TypedDistribution< ModelVector< ModelVector<Real> >  > {
        
    public:
                                                        Dist_PhyloMvtBrownian( void ) {};
        virtual                                        ~Dist_PhyloMvtBrownian() {};
        
        // Basic utility functions
        Dist_PhyloMvtBrownian*                          clone(void) const;                                                                      //!< Clone the object
        static const std::string&                       getClassType(void);                                                                     //!< Get Rev type
        static const TypeSpec&                          getClassTypeSpec(void);                                                                 //!< Get class type spec
        std::string                                     getDistributionFunctionName(void) const;                                                //!< Get the Rev-name for this distribution.
        const TypeSpec&                                 getTypeSpec(void) const;                                                                //!< Get the type spec of the instance
        const MemberRules&                              getParameterRules(void) const;                                                          //!< Get member rules (const)
        void                                            printValue(std::ostream& o) const;                                                      //!< Print the general information on the function ('usage')
                
        // Distribution functions you have to override
        RevBayesCore::PhyloMultivariateBrownianProcess* createDistribution(void) const;
        
    protected:
        
        void                                            setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var);       //!< Set member variable
        
        
    private:
        
        RevPtr<const RevVariable>                       tree;
        RevPtr<const RevVariable>                       sigma;
 //       RevPtr<const RevVariable>                          rootval;
        
    };
    
}

#endif /* defined(__revbayes__Dist_mvtBrownian__) */
