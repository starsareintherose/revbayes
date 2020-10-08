#ifndef RlString_H
#define RlString_H

#include <fstream>
#include <string>
#include <vector>

#include "ModelObject.h"
#include "TypedDagNode.h"
#include "ConstantNode.h"
#include "DagNode.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "IndirectReferenceFunction.h"
#include "RevObject.h"
#include "RevPtr.h"
#include "RlConstantNode.h"
#include "TypedFunction.h"
#include "UserFunctionNode.h"

namespace RevLanguage {
class Argument;
class RevVariable;
class TypeSpec;

    class RlString : public ModelObject<std::string> {

        public:
                                            RlString(void);                                                         //!< Default: empty RlString
                                            RlString(const std::string& v, bool parse=true);                        //!< Constructor from RlString
                                            RlString(RevBayesCore::TypedDagNode<std::string> *x, bool parse=true);  //!< Construct from DAG node
        
            // Basic operator functions
            RevObject*                      add(const RevObject &rhs) const;                                        //!< Addition operator used for example in '+=' statements
            RlString*                       add(const RlString &rhs) const;                                         //!< Addition operator used for example in '+=' statements

            // Basic utility functions
            RlString*                       clone(void) const;                                                      //!< Copy
            RevPtr<RevVariable>             executeMethod( std::string const &name, const std::vector<Argument> &args, bool &found );
            static const std::string&       getClassType(void);                                                     //!< Get Rev type
            static const TypeSpec&          getClassTypeSpec(void);                                                 //!< Get class type spec
            const TypeSpec&                 getTypeSpec(void) const;                                                //!< Get language type of the object
        
            std::string                     getGuiName(void) { return "String"; }
            std::string                     getGuiUnicodeSymbol(void) { return "S"; }
            std::string                     getGuiInfo(void) { return ""; }

        protected:

        private:
            void                            initMethods(void);
            void                            parseValue(void);
    };
}

#endif

