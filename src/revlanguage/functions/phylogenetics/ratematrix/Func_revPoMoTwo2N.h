/**
 * @file
 * This file contains the declaration of the RevLanguage revPoMoTwo4N function, which
 * is used to created a deterministic variable associated with the revPoMoTwo4N function.
 *
 * @brief Declaration and implementation of Func_revPoMoTwo2N
 *
 * (c) Copyright 2009- under GPL version 3
 * @date Last modified: 17/09/2019
 * @author Rui Borges
 * @license GPL version 3
 * @version 1.0
 *
 */


#ifndef Func_revPoMoTwo2N_H
#define Func_revPoMoTwo2N_H

#include "RlRateMatrix.h"
#include "RlTypedFunction.h"

#include <map>
#include <string>

namespace RevLanguage {

    class Func_revPoMoTwo2N : public TypedFunction<RateMatrix> {

    public:
        Func_revPoMoTwo2N( void );

        // Basic utility functions
        Func_revPoMoTwo2N*                                                   clone(void) const;                                          //!< Clone the object
        static const std::string&                                       getClassType(void);                                         //!< Get Rev type
        static const TypeSpec&                                          getClassTypeSpec(void);                                     //!< Get class type spec
        std::string                                                     getFunctionName(void) const;                                //!< Get the primary name of the function in Rev
        const TypeSpec&                                                 getTypeSpec(void) const;                                    //!< Get the type spec of the instance

        // Function functions you have to override
        RevBayesCore::TypedFunction< RevBayesCore::RateGenerator>*      createFunction(void) const;                                 //!< Create internal function object
        const ArgumentRules&                                            getArgumentRules(void) const;                               //!< Get argument rules

    };

}

#endif
