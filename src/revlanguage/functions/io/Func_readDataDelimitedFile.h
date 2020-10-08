#ifndef Func_readDataDelimitedFile_hpp
#define Func_readDataDelimitedFile_hpp


#include <string>
#include <vector>
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
     * @author The RevBayes Development Core Team (Michael Landis)
     * @since 2015-03-03, version 1.0
     *
     */
    class Func_readDataDelimitedFile : public Procedure {
        
    public:
        // Basic utility functions
        Func_readDataDelimitedFile*         clone(void) const;                                          //!< Clone the object
        static const std::string&           getClassType(void);                                         //!< Get Rev type
        static const TypeSpec&              getClassTypeSpec(void);                                     //!< Get class type spec
        std::string                         getFunctionName(void) const;                                //!< Get the primary name of the function in Rev
        std::vector<std::string>            getFunctionNameAliases(void) const;                         //!< Get the aliases of the function in Rev
        const TypeSpec&                     getTypeSpec(void) const;                                    //!< Get language type of the object
        
        // Regular functions
        RevPtr<RevVariable>                 execute(void);                                              //!< Execute function
        const ArgumentRules&                getArgumentRules(void) const;                               //!< Get argument rules
        const TypeSpec&                     getReturnType(void) const;                                  //!< Get type of return value
        
    private:
        std::string                         bitToState(const std::string &s);
        
    };
    
}

#endif /* Func_readDataDelimitedFile_hpp */
