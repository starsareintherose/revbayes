#ifndef RlAtlas_H
#define RlAtlas_H

#include <ostream>
#include <string>
#include <vector>

#include "ModelObject.h"
#include "TimeAtlas.h"
#include "TypedDagNode.h"
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
class Argument;
class RevVariable;
class TypeSpec;
    
    class RlAtlas : public ModelObject<RevBayesCore::TimeAtlas> {
        
    public:
        
                                            RlAtlas(void);                                                                          //!< Default constructor
                                            RlAtlas(RevBayesCore::TimeAtlas *m);                                                    //!< Default constructor
                                            RlAtlas(RevBayesCore::TypedDagNode<RevBayesCore::TimeAtlas> *d);                        //!< Default constructor
        
        // Basic utility functions
        RlAtlas*                            clone(void) const;                                                                      //!< Clone object
        static const std::string&           getClassType(void);                                                                     //!< Get Rev type
        static const TypeSpec&              getClassTypeSpec(void);                                                                 //!< Get class type spec
        const TypeSpec&                     getTypeSpec(void) const;                                                                //!< Get language type of the object
        
        // Member method inits
        RevPtr<RevVariable>                 executeMethod(const std::string& name, const std::vector<Argument>& args, bool &f);     //!< Override to map member methods to internal functions

        std::string                         getGuiName(void) { return ""; }
        std::string                         getGuiUnicodeSymbol(void) { return ""; }
        std::string                         getGuiInfo(void) { return ""; }
        
    private:
        RevBayesCore::TimeAtlas*            atlas;
    };
    
}
#endif /* defined(RlAtlas_H) */
