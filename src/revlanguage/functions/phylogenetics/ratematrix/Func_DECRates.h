//
//  Func_DECRates.h
//  revbayes-proj
//
//  Created by Michael Landis on 3/3/15.
//  Copyright (c) 2015 Michael Landis. All rights reserved.
//

#ifndef __revbayes_proj__Func_DECRates__
#define __revbayes_proj__Func_DECRates__


#include <string>
#include <vector>
#include <iosfwd>

#include "RlTypedFunction.h"
#include "RbVector.h"
#include "ModelVector.h"
#include "RealPos.h"
#include "ConstantNode.h"
#include "DagNode.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "IndirectReferenceFunction.h"
#include "ModelObject.h"
#include "RevPtr.h"
#include "RlConstantNode.h"
#include "RlDeterministicNode.h"
#include "TypedDagNode.h"
#include "TypedFunction.h"
#include "UserFunctionNode.h"

namespace RevLanguage {
class ArgumentRules;
class TypeSpec;
    
    class Func_DECRates :  public TypedFunction<ModelVector<RealPos> > {
        
    public:
        Func_DECRates( void );
        
        // Basic utility functions
        Func_DECRates*                                                  clone(void) const;                                          //!< Clone the object
        static const std::string&                                       getClassType(void);                                         //!< Get Rev type
        static const TypeSpec&                                          getClassTypeSpec(void);                                     //!< Get class type spec
        std::string                                                     getFunctionName(void) const;                                //!< Get the primary name of the function in Rev
        const TypeSpec&                                                 getTypeSpec(void) const;                                    //!< Get the type spec of the instance
        
        // Function functions you have to override
        RevBayesCore::TypedFunction< RevBayesCore::RbVector<double> >*  createFunction(void) const;                                 //!< Execute function
        const ArgumentRules&                                            getArgumentRules(void) const;                               //!< Get argument rules
        
    };
    
}

#endif /* defined(__revbayes_proj__Func_DECRates__) */
