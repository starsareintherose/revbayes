#ifndef Func_posteriorPredictiveProbability_H
#define Func_posteriorPredictiveProbability_H

#include <string>
#include <iosfwd>
#include <vector>

#include "RlSimplex.h"
#include "RlTypedFunction.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "RevPtr.h"
#include "RlDeterministicNode.h"
#include "Simplex.h"
#include "TypedDagNode.h"
#include "TypedFunction.h"

namespace RevLanguage {
class ArgumentRules;
class TypeSpec;
    
    /**
     * The RevLanguage wrapper of the arithmetic posteriorPredictiveProbability function.
     *
     * The RevLanguage wrapper of the posteriorPredictiveProbability function connects
     * the variables/parameters of the function and creates the internal posteriorPredictiveProbabilityFunction object.
     * Please read the posteriorPredictiveProbabilityFunction.h for more info.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (Sebastian Hoehna)
     * @since 2014-07-27, version 1.0
     *
     */
    class Func_posteriorPredictiveProbability : public TypedFunction<Simplex> {
        
    public:
        Func_posteriorPredictiveProbability( void );
        
        // Basic utility functions
        Func_posteriorPredictiveProbability*                                    clone(void) const;                                          //!< Clone the object
        static const std::string&                                               getClassType(void);                                         //!< Get Rev type
        static const TypeSpec&                                                  getClassTypeSpec(void);                                     //!< Get class type spec
        std::string                                                             getFunctionName(void) const;                                //!< Get the primary name of the function in Rev
        const TypeSpec&                                                         getTypeSpec(void) const;                                    //!< Get the type spec of the instance
        
        // Function functions you have to override
        RevBayesCore::TypedFunction< RevBayesCore::Simplex >*                   createFunction(void) const;                                 //!< Create internal function object
        const ArgumentRules&                                                    getArgumentRules(void) const;                               //!< Get argument rules
        
    };
    
}

#endif
