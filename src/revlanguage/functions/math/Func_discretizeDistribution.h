#ifndef Func_discretizeDistribution_H
#define Func_discretizeDistribution_H

#include <string>
#include <iosfwd>
#include <vector>

#include "ModelVector.h"
#include "Real.h"
#include "RlTypedFunction.h"
#include "ConstantNode.h"
#include "DagNode.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "IndirectReferenceFunction.h"
#include "ModelObject.h"
#include "RbVector.h"
#include "RevPtr.h"
#include "RlConstantNode.h"
#include "RlDeterministicNode.h"
#include "TypedDagNode.h"
#include "TypedFunction.h"
#include "UserFunctionNode.h"

namespace RevLanguage {
class ArgumentRules;
class TypeSpec;
    
    class Func_discretizeDistribution :  public TypedFunction< ModelVector< Real > > {
        
    public:
        Func_discretizeDistribution();
        
        // Basic utility functions
        Func_discretizeDistribution*                                        clone(void) const;                                          //!< Clone the object
        static const std::string&                                           getClassName(void);                                         //!< Get class name
        static const TypeSpec&                                              getClassTypeSpec(void);                                     //!< Get class type spec
        std::string                                                         getFunctionName(void) const;                                //!< Get the primary name of the function in Rev
        const TypeSpec&                                                     getTypeSpec(void) const;                                    //!< Get language type of the object
        
        // Regular functions
        RevBayesCore::TypedFunction< RevBayesCore::RbVector<double> >*      createFunction(void) const;                                 //!< Create internal function object
        const ArgumentRules&                                                getArgumentRules(void) const;                               //!< Get argument rules
        
        
    protected:
        
    };
    
}


#endif


