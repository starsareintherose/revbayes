#ifndef Func_readCharacterDataDelimited_H
#define Func_readCharacterDataDelimited_H

#include <string>
#include <iosfwd>

#include "Procedure.h"
#include "RevPtr.h"


namespace RevLanguage {
class ArgumentRules;
class RevVariable;
class TypeSpec;
    
    /**
     * The Rev procedure to read character data from delimited files.
     *
     * This procedure can read several data types.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (Sebastian Hoehna)
     * @since 2015-03-03, version 1.0
     *
     */
    class Func_readCharacterDataDelimited :  public Procedure {
        
    public:
        // Basic utility functions
        Func_readCharacterDataDelimited*    clone(void) const;                                          //!< Clone the object
        static const std::string&           getClassType(void);                                         //!< Get Rev type
        static const TypeSpec&              getClassTypeSpec(void);                                     //!< Get class type spec
        std::string                         getFunctionName(void) const;                                //!< Get the primary name of the function in Rev
        const TypeSpec&                     getTypeSpec(void) const;                                    //!< Get language type of the object
        
        // Regular functions
        RevPtr<RevVariable>                 execute(void);                                              //!< Execute function
        const ArgumentRules&                getArgumentRules(void) const;                               //!< Get argument rules
        const TypeSpec&                     getReturnType(void) const;                                  //!< Get type of return value
        
    private:
        std::string                         bitToState(const std::string &s);

    };
    
}

#endif