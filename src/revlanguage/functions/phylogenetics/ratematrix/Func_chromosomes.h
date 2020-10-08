/**
 * @file
 * This file contains the declaration of the RevLanguage chromosomes function, which
 * is used to created a deterministic variable associated with the chromosomes function.
 *
 * @brief Declaration of Func_chromosomes
 *
 * (c) Copyright 2014- under GPL version 3
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 * @version 1.0
 *
 */


#ifndef Func_chromosomes_H
#define Func_chromosomes_H

#include <string>
#include <iosfwd>
#include <vector>

#include "RlRateMatrix.h"
#include "RlTypedFunction.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "RateGenerator.h"
#include "RevPtr.h"
#include "RlDeterministicNode.h"
#include "TypedDagNode.h"
#include "TypedFunction.h"

namespace RevLanguage {
class ArgumentRules;
class TypeSpec;
    
    class Func_chromosomes : public TypedFunction<RateMatrix> {
        
    public:
        Func_chromosomes( void );
        
        // Basic utility functions
        Func_chromosomes*                                               clone(void) const;                                          //!< Clone the object
        static const std::string&                                       getClassType(void);                                         //!< Get Rev type
        static const TypeSpec&                                          getClassTypeSpec(void);                                     //!< Get class type spec
        std::string                                                     getFunctionName(void) const;                                //!< Get the primary name of the function in Rev
        const TypeSpec&                                                 getTypeSpec(void) const;                                    //!< Get the type spec of the instance
        
        // Function functions you have to override
        RevBayesCore::TypedFunction< RevBayesCore::RateGenerator>*      createFunction(void) const;                                 //!< Create internal function object
        const ArgumentRules&                                            getArgumentRules(void) const;                                                   		
    };
    
}

#endif
