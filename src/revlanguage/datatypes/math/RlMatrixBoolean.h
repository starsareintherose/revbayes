#ifndef RlMatrixBoolean_H
#define RlMatrixBoolean_H

#include <iostream>
#include <vector>
#include <string>

#include "MatrixBoolean.h"
#include "ModelObject.h"
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
    
    
    /**
     * The RevLanguage wrapper of the boolean matrix.
     *
     * The RevLanguage wrapper of the boolean matrix simply
     * manages the interactions through the Rev with our core.
     * That is, the internal move object can be constructed and hooked up
     * in a DAG-nove (variable) that it works on.
     * See the MatrixBoolean.h for more details.
     *
     *
     * @author David Cerny
     * @since 2019-10-24, version 1.0
     *
     */
    class MatrixBoolean : public ModelObject<RevBayesCore::MatrixBoolean>  {
        
    public:
                                            MatrixBoolean(void);                                                                       //!< Default constructor
                                            MatrixBoolean(const RevBayesCore::MatrixBoolean &v);
                                            MatrixBoolean(RevBayesCore::MatrixBoolean *m);
                                            MatrixBoolean(RevBayesCore::TypedDagNode<RevBayesCore::MatrixBoolean> *mat);               //!< Construct from DAG node
        
        // the value type definition
        virtual MatrixBoolean*              clone(void) const;                                                                      //!< Clone object
        static const std::string&           getClassType(void);                                                                     //!< Get Rev type
        static const TypeSpec&              getClassTypeSpec(void);                                                                 //!< Get class type spec
        virtual const TypeSpec&             getTypeSpec(void) const;                                                                //!< Get language type of the object

        // Member method functions
        virtual RevPtr<RevVariable>         executeMethod(const std::string& name, const std::vector<Argument>& args, bool &f);     //!< Map member methods to internal functions

        std::string                         getGuiName(void) { return ""; }
        std::string                         getGuiUnicodeSymbol(void) { return ""; }
        std::string                         getGuiInfo(void) { return ""; }

    private:
        void                                initializeMethods(void);
    };

}

#endif /* defined(__revbayes__MatrixBoolean__) */
