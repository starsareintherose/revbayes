#ifndef Func_source_H
#define Func_source_H

#include <iosfwd>

#include "Procedure.h"
#include "RevPtr.h"

namespace RevLanguage {
class ArgumentRules;
class RevVariable;
class TypeSpec;

class Func_source : public Procedure {
    
public:
    Func_source( void );
    
    // Basic utility functions
    Func_source*                            clone(void) const;                                          //!< Clone object
    static const std::string&               getClassType(void);                                         //!< Get Rev type
    static const TypeSpec&                  getClassTypeSpec(void);                                     //!< Get class type spec
    std::string                             getFunctionName(void) const;                                //!< Get the primary name of the function in Rev
    const TypeSpec&                         getTypeSpec(void) const;                                    //!< Get language type of the object
    
    // Func_source functions
    const ArgumentRules&                    getArgumentRules(void) const;                               //!< Get argument rules
    const TypeSpec&                         getReturnType(void) const;                                  //!< Get type of return val
    
    RevPtr<RevVariable>                     execute(void);                                              //!< Execute function
    
};
    
}

#endif

