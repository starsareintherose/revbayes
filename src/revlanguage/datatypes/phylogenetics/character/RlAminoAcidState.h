/**
 * @file
 * This file contains the declaration of RlAminoAcidState, which is
 * a RevBayes wrapper around a regular AminoAcid character.
 *
 * @brief Declaration of RlBoolean
 *
 * (c) Copyright 2009-
 * @date Last modified: $Date: 2012-08-23 09:27:32 +0200 (Thu, 23 Aug 2012) $
 * @author The RevBayes Development Core Team
 * @license GPL version 3
 * @version 1.0
 * @since 2012-09-08, version 1.0
 * @extends RbObject
 *
 * $Id: RlBoolean.h 1766 2012-08-23 07:27:32Z hoehna $
 */

#ifndef RlAminoAcidState_H
#define RlAminoAcidState_H

#include <ostream>
#include <string>
#include <vector>

#include "AminoAcidState.h"
#include "ModelObject.h"
#include "TypedDagNode.h"
#include "CharacterState.h"
#include "ConstantNode.h"
#include "DagNode.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "IndirectReferenceFunction.h"
#include "RevPtr.h"
#include "RlConstantNode.h"
#include "TypedFunction.h"
#include "UserFunctionNode.h"

namespace RevLanguage {
class TypeSpec;
    
    class AminoAcidState : public ModelObject<RevBayesCore::AminoAcidState> {
        
    public:
                                        AminoAcidState(void);                                                   //!< Default constructor
                                        AminoAcidState(const RevBayesCore::AminoAcidState &d);                  //!< Construct from AminoAcid
        
        // Operators
        
        // Basic utility functions
        AminoAcidState*                 clone(void) const;                                                      //!< Clone object
        static const std::string&       getClassType(void);                                                     //!< Get Rev type
        static const TypeSpec&          getClassTypeSpec(void);                                                 //!< Get class type spec
        const TypeSpec&                 getTypeSpec(void) const;                                                //!< Get language type of the object
        
        std::string                     getGuiName(void) { return "Amino Acid State"; }
        std::string                     getGuiUnicodeSymbol(void) { return "S(AA)"; }
        std::string                     getGuiInfo(void) { return ""; }
    };
    
}

#endif

