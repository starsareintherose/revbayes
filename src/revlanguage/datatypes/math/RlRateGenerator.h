#ifndef RlRateGenerator_H
#define RlRateGenerator_H

#include <ostream>
#include <string>
#include <vector>

#include "ModelObject.h"
#include "RateGenerator.h"
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

    class RateGenerator : public ModelObject<RevBayesCore::RateGenerator> {

    public:

        RateGenerator(void);                                                                                                        //!< Default constructor
        RateGenerator(const RevBayesCore::RateGenerator& m);                                                                        //!< Default constructor
        RateGenerator(RevBayesCore::RateGenerator *m);                                                                              //!< Default constructor
        RateGenerator(RevBayesCore::TypedDagNode<RevBayesCore::RateGenerator> *d);                                                                                                        //!< Default constructor

        // Basic utility functions
        RateGenerator*                      clone(void) const;                                                                      //!< Clone object
        static const std::string&           getClassType(void);                                                                     //!< Get Rev type
        static const TypeSpec&              getClassTypeSpec(void);                                                                 //!< Get class type spec
        const TypeSpec&                     getTypeSpec(void) const;                                                                //!< Get language type of the object

        // Member method functions
        virtual RevPtr<RevVariable>         executeMethod(const std::string& name, const std::vector<Argument>& args, bool &f);     //!< Map member methods to internal functions
        void                                printValue( std::ostream& o, bool user ) const;

        std::string                         getGuiName(void) { return ""; }
        std::string                         getGuiUnicodeSymbol(void) { return ""; }
        std::string                         getGuiInfo(void) { return ""; }

    protected:
        void                                initMethods(void);
    };

}

#endif /* defined(RlRateGenerator_H) */
