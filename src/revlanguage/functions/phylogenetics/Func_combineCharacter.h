#ifndef Func_combineCharacter_H
#define Func_combineCharacter_H

#include <iosfwd>

#include "Procedure.h"
#include "RevPtr.h"

namespace RevLanguage {
class ArgumentRules;
class RevVariable;
class TypeSpec;
    
    /**
     * @brief Rev function to concatenate two or more data matrices.
     *
     * This procedure concatenates the sequences of two or more data matrices.
     * The concatenation builds a new data matrix by concatenating sequences.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (Sebastian Hoehna)
     * @since Version 1.0, 2014-12-09
     *
     */
    class Func_combineCharacter : public Procedure {
        
    public:
        Func_combineCharacter( void );
        
        // Basic utility functions
        Func_combineCharacter*                          clone(void) const;                                          //!< Clone object
        static const std::string&                       getClassType(void);                                         //!< Get Rev concatenate
        static const TypeSpec&                          getClassTypeSpec(void);                                     //!< Get class concatenate spec
        std::string                                     getFunctionName(void) const;                                //!< Get the primary name of the function in Rev
        const TypeSpec&                                 getTypeSpec(void) const;                                    //!< Get language concatenate of the object
        
        // Func_source functions
        const ArgumentRules&                            getArgumentRules(void) const;                               //!< Get argument rules
        const TypeSpec&                                 getReturnType(void) const;                                  //!< Get concatenate of return val
        
        RevPtr<RevVariable>                             execute(void);                                              //!< Execute function
        
    protected:
        
    };
    
}

#endif

