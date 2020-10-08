/**
 * @file
 * This file contains the declaration of the RevLanguage dec_biogeo function, 
 * which is used to created deterministic variable associated with the dec_biogeo
 * function.
 *
 * @brief Declaration and implementation of Func_biogeo_de
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: $Date: 2012-04-20 04:06:14 +0200 (Fri, 20 Apr 2012) $
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 * @version 1.0
 *
 * $Id: Func__add.h 1406 2012-04-20 02:06:14Z hoehna $
 */


#ifndef Func_biogeo_de_H
#define Func_biogeo_de_H

#include <string>
#include <iosfwd>
#include <vector>

#include "RlRateGeneratorSequence.h"
#include "RlTypedFunction.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "RateGeneratorSequence.h"
#include "RevPtr.h"
#include "RlDeterministicNode.h"
#include "TypedDagNode.h"
#include "TypedFunction.h"

namespace RevLanguage {
class ArgumentRules;
class TypeSpec;
    
    class Func_biogeo_de : public TypedFunction<RateGeneratorSequence> {
        
    public:
        Func_biogeo_de( void );
        
        // Basic utility functions
        Func_biogeo_de*                                                 clone(void) const;                                          //!< Clone the object
        static const std::string&                                       getClassType(void);                                         //!< Get Rev type
        static const TypeSpec&                                          getClassTypeSpec(void);                                     //!< Get class type spec
        std::string                                                     getFunctionName(void) const;                                //!< Get the primary name of the function in Rev
        const TypeSpec&                                                 getTypeSpec(void) const;                                    //!< Get the type spec of the instance
        
        // Function functions you have to override
        RevBayesCore::TypedFunction< RevBayesCore::RateGeneratorSequence >*           createFunction(void) const;                                 //!< Create internal function object
        const ArgumentRules&                                            getArgumentRules(void) const;                               //!< Get argument rules

    };
}

#endif
