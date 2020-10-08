//
//  Func_vectorFlatten.h
//  revbayes-proj
//
//  Created by Michael Landis on 4/2/15.
//  Copyright (c) 2015 Michael Landis. All rights reserved.
//

#ifndef __revbayes_proj__Func_vectorFlatten__
#define __revbayes_proj__Func_vectorFlatten__

#include <string>
#include <iosfwd>
#include <vector>

#include "ModelVector.h"
#include "RealPos.h"
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
    
    class Func_vectorFlatten :  public TypedFunction<ModelVector<RealPos> > {
        
    public:
        Func_vectorFlatten();
        
        // Basic utility functions
        Func_vectorFlatten*                                                     clone(void) const;                                          //!< Clone the object
        static const std::string&                                               getClassType(void);                                         //!< Get Rev type (static)
        static const TypeSpec&                                                  getClassTypeSpec(void);                                     //!< Get Rev type spec (static)
        std::string                                                             getFunctionName(void) const;                                //!< Get the primary name of the function in Rev
        const TypeSpec&                                                         getTypeSpec(void) const;                                    //!< Get Rev type spec (from instance)
        
        // Regular functions
        RevBayesCore::TypedFunction< RevBayesCore::RbVector< double> >*         createFunction(void) const;                                                     //!< Create internal function object
        const ArgumentRules&                                                    getArgumentRules(void) const;                               //!< Get argument rules
        
    };
    
}


#endif /* defined(__revbayes_proj__Func_vectorFlatten__) */
