#ifndef RlMove_MultiValueEventScale_H
#define RlMove_MultiValueEventScale_H

#include <ostream>
#include <string>

#include "RlMove.h"
#include "RevObject.h"
#include "RevPtr.h"
#include "RevVariable.h"

namespace RevLanguage {
class TypeSpec;
    
    
    /**
     * The RevLanguage wrapper of the random-geometric-walk move.
     *
     * The RevLanguage wrapper of the random-geometric-walk move simply
     * manages the interactions through the Rev with our core.
     * That is, the internal move object can be constructed and hooked up
     * in a DAG-nove (variable) that it works on.
     * See the Move_MultiValueEventScale.h for more details.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (Sebastian Hoehna)
     *
     */
    class Move_MultiValueEventScale : public Move {
        
    public:
        
        Move_MultiValueEventScale(void);                                                                                                         //!< Default constructor
        
        // Basic utility functions
        virtual Move_MultiValueEventScale*              clone(void) const;                                                                          //!< Clone object
        void                                            constructInternalObject(void);                                                              //!< We construct the a new internal SlidingMove.
        static const std::string&                       getClassType(void);                                                                         //!< Get Rev type
        static const TypeSpec&                          getClassTypeSpec(void);                                                                     //!< Get class type spec
        std::string                                     getMoveName(void) const;                                                                    //!< Get the name used for the constructor function in Rev.
        const MemberRules&                              getParameterRules(void) const;                                                              //!< Get member rules (const)
        virtual const TypeSpec&                         getTypeSpec(void) const;                                                                    //!< Get language type of the object
        virtual void                                    printValue(std::ostream& o) const;                                                          //!< Print value (for user)
        
    protected:
        
        void                                            setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var);           //!< Set member variable
        
        RevPtr<const RevVariable>                       x;                                                                                          //!< If autotuning should be used.
        RevPtr<const RevVariable>                       val_name;                                                                                       //!< If autotuning should be used
        RevPtr<const RevVariable>                       lambda;                                                                                     //!< If autotuning should be used
        RevPtr<const RevVariable>                       tune;                                                                                       //!< If autotuning should be used

    };
    
}

#endif
