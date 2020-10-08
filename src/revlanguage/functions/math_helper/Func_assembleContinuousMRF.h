#ifndef Func_assembleContinuousMRF_H
#define Func_assembleContinuousMRF_H

#include <string>
#include <iosfwd>
#include <vector>

#include "ModelVector.h"
#include "RealPos.h"
#include "RbVector.h"
#include "RlTypedFunction.h"
#include "ConstantNode.h"
#include "DagNode.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "IndirectReferenceFunction.h"
#include "ModelObject.h"
#include "RevPtr.h"
#include "RlConstantNode.h"
#include "RlDeterministicNode.h"
#include "TypedDagNode.h"
#include "TypedFunction.h"
#include "UserFunctionNode.h"

namespace RevLanguage {
class ArgumentRules;
class TypeSpec;

    /**
     * The RevLanguage wrapper of the assembleContinuousMRF function.
     *
     * The RevLanguage wrapper of the assembleContinuousMRF function connects
     * the variables/parameters of the function and creates the internal vector.
     * Please read the assembleContinuousMRFRateMatrixFunction.h for more info.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team
     * @since 2014-08-14, version 1.0
     *
     */
    class Func_assembleContinuousMRF : public TypedFunction<ModelVector<RealPos> > {

    public:
        Func_assembleContinuousMRF( void );

        // Basic utility functions
        Func_assembleContinuousMRF*                                                       clone(void) const;                                          //!< Clone the object
        static const std::string&                                       getClassType(void);                                         //!< Get Rev type
        static const TypeSpec&                                          getClassTypeSpec(void);                                     //!< Get class type spec
        std::string                                                     getFunctionName(void) const;                                //!< Get the primary name of the function in Rev
        const TypeSpec&                                                 getTypeSpec(void) const;                                    //!< Get the type spec of the instance

        // Function functions you have to override
        RevBayesCore::TypedFunction< RevBayesCore::RbVector<double> >*  createFunction(void) const;                                 //!< Create internal function object
        const ArgumentRules&                                            getArgumentRules(void) const;                               //!< Get argument rules

    };

}

#endif
