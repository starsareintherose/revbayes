//
//  Move_DivergenceTimeBinaryRate.h
//  revbayes
//
//  Created by Shiran Abadi on 6/17/20.
//  Copyright © 2020 Shiran Abadi. All rights reserved.
//

#ifndef Move_DivergenceTimeBinaryRate_h
#define Move_DivergenceTimeBinaryRate_h

#include "RlMove.h"
#include "TypedDagNode.h"

#include <ostream>
#include <string>

namespace RevLanguage {
    
    class Move_DivergenceTimeBinaryRate : public Move {
        
    public:
        
        Move_DivergenceTimeBinaryRate(void);                                                                                                           //!< Default constructor
        
        // Basic utility functions
        virtual Move_DivergenceTimeBinaryRate*                 clone(void) const;                                                                      //!< Clone object
        void                                            constructInternalObject(void);                                                          //!< We construct the a new internal Move.
        static const std::string&                       getClassType(void);                                                                     //!< Get Rev type
        static const TypeSpec&                          getClassTypeSpec(void);                                                                 //!< Get class type spec
        std::string                                     getMoveName(void) const;                                                                //!< Get the name used for the constructor function in Rev.
        const MemberRules&                              getParameterRules(void) const;                                                          //!< Get member rules (const)
        virtual const TypeSpec&                         getTypeSpec(void) const;                                                                //!< Get language type of the object
        virtual void                                    printValue(std::ostream& o) const;                                                      //!< Print value (for user)
        
    protected:
        
        void                                            setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var);       //!< Set member variable
        RevPtr<const RevVariable>                       ctmc;
        
    };
    
}

#endif
