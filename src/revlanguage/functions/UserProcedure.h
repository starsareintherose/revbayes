#ifndef UserProcedure_H
#define UserProcedure_H

#include <string>
#include <iosfwd>

#include "RlFunction.h"
#include "RevPtr.h"
#include "UserFunctionDef.h"


namespace RevLanguage {
class ArgumentRules;
class RevVariable;
class TypeSpec;

    /**
     * @brief Class holding user procedures
     *
     * The UserProcedure class holds information about and executes user procedures. A procedure
     * does not have to know how to create a deterministic variable, it just executes the code
     * in static procedure calls. Another difference is taht a user procedure does not have to
     * be able to return its parameters, since this function is only used in parent management
     * in model DAGs.
     */
    class UserProcedure :  public Function {
        
    public:
        UserProcedure(UserFunctionDef* def);                                                //!< Standard constructor
        virtual                                     ~UserProcedure() {}                     //!< Virtual destructor
        
        // Basic utility functions
        UserProcedure*                              clone(void) const;                      //!< Clone the object
        static const std::string&                   getClassType(void);                     //!< Get type (static)
        static const TypeSpec&                      getClassTypeSpec(void);                 //!< Get type spec (static)
        std::string                                 getFunctionName(void) const;            //!< Get the primary name of the function in Rev
        const TypeSpec&                             getTypeSpec(void) const;                //!< Get type spec (dynamic)
        
        // Regular functions
        virtual RevPtr<RevVariable>                 execute(void);                          //!< Execute function
        const ArgumentRules&                        getArgumentRules(void) const;           //!< Get argument rules
        const TypeSpec&                             getReturnType(void) const;              //!< Get type spec of return value
        
    protected:
        // Member variable
        RevPtr<UserFunctionDef>                     functionDef;                            //!< The definition of the procedure
    };
    
}

#endif

