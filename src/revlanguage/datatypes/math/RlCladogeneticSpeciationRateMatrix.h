//
//  RlCladogeneticSpeciationRateMatrix.h
//
//  Created by Will Freyman on 8/1/2017.
//

#ifndef RlCladogeneticSpeciationRateMatrix_h
#define RlCladogeneticSpeciationRateMatrix_h

#include <ostream>
#include <string>
#include <vector>

#include "ModelObject.h"
#include "CladogeneticSpeciationRateMatrix.h"
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
    
    class CladogeneticSpeciationRateMatrix : public ModelObject<RevBayesCore::CladogeneticSpeciationRateMatrix> {
        
    public:
        
        CladogeneticSpeciationRateMatrix(void); 
        CladogeneticSpeciationRateMatrix(const RevBayesCore::CladogeneticSpeciationRateMatrix& m);
        CladogeneticSpeciationRateMatrix(RevBayesCore::CladogeneticSpeciationRateMatrix *m);
        CladogeneticSpeciationRateMatrix(RevBayesCore::TypedDagNode<RevBayesCore::CladogeneticSpeciationRateMatrix> *d);
        
        // Basic utility functions
        CladogeneticSpeciationRateMatrix*       clone(void) const;                  //!< Clone object
        static const std::string&               getClassType(void);                 //!< Get Rev type
        static const TypeSpec&                  getClassTypeSpec(void);             //!< Get class type spec
        const TypeSpec&                         getTypeSpec(void) const;            //!< Get language type of the object
        
        // Member method functions
        virtual RevPtr<RevVariable>             executeMethod(const std::string& name, const std::vector<Argument>& args, bool &f);     //!< Map member methods to internal functions

        std::string                             getGuiName(void) { return ""; }
        std::string                             getGuiUnicodeSymbol(void) { return ""; }
        std::string                             getGuiInfo(void) { return ""; }
        
    protected:

        void                                    initMethods(void);

    };
    
}

#endif /* RlCladogeneticSpeciationRateMatrix_h */
