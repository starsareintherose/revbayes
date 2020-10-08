#ifndef RlRelativeNodeAgeWeightedConstraints_H
#define RlRelativeNodeAgeWeightedConstraints_H

#include <stddef.h>
#include <ostream>
#include <string>
#include <vector>

#include "ModelObject.h"
#include "RelativeNodeAgeWeightedConstraints.h"
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
    
    class RlRelativeNodeAgeWeightedConstraints : public ModelObject<RevBayesCore::RelativeNodeAgeWeightedConstraints>  {
        
        public:
                                                    RlRelativeNodeAgeWeightedConstraints(void);                                                                                                              //!< Default constructor
                                                    RlRelativeNodeAgeWeightedConstraints(const RevBayesCore::RelativeNodeAgeWeightedConstraints &m);                                                                                        //!< Default constructor
                                                    RlRelativeNodeAgeWeightedConstraints(RevBayesCore::RelativeNodeAgeWeightedConstraints *m);                                                                                        //!< Default constructor
                                                    RlRelativeNodeAgeWeightedConstraints(RevBayesCore::TypedDagNode<RevBayesCore::RelativeNodeAgeWeightedConstraints> *d);                                                            //!< Default constructor
            
            
            // Basic utility functions
            RlRelativeNodeAgeWeightedConstraints*   clone(void) const;                                                                      //!< Clone object
            static const std::string&               getClassType(void);                                                                     //!< Get Rev type
            static const TypeSpec&                  getClassTypeSpec(void);                                                                 //!< Get class type spec
            const TypeSpec&                         getTypeSpec(void) const;                                                                //!< Get language type of the object
            
            
            // STL-like vector functions provided here
            //virtual void                          push_back(const RevObject &x);                                                          //!< Append element to end
            //virtual RevObject*                    getElement(size_t idx) const;                                                           //!< Get element variable
            virtual size_t                          getNumberOfConstraints(void) const;                                                     //!< Get number of elements in container
            
         /* Might be desirable to have a function like that, but then we need to define a class for an individual RelativeNodeAgeConstraint
            const Real*                             getConstraint(size_t idx) const; */
            
            // Member method inits
            RevPtr<RevVariable>                     executeMethod(const std::string& name, const std::vector<Argument>& args, bool &f);     //!< Override to map member methods to internal functions

            std::string                             getGuiName(void) { return ""; }
            std::string                             getGuiUnicodeSymbol(void) { return ""; }
            std::string                             getGuiInfo(void) { return ""; }
            
        private:
    };
}

#endif
