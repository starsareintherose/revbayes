//
//  RlWhiteNoiseProcess.h
//  revbayes
//
//  Created by Nicolas Lartillot on 2014-03-22.
//  Copyright (c) 2014 revbayes team. All rights reserved.
//

#ifndef Dist_PhyloWhiteNoise_H
#define Dist_PhyloWhiteNoise_H

#include <math.h>
#include <iostream>
#include <string>
#include <vector>

#include "PhyloWhiteNoiseProcess.h"
#include "ModelVector.h"
#include "RlTypedDistribution.h"
#include "RealPos.h"
#include "ConstantNode.h"
#include "DagMemberFunction.h"
#include "DagNode.h"
#include "DeterministicNode.h"
#include "DynamicNode.h"
#include "IndirectReferenceFunction.h"
#include "ModelObject.h"
#include "RbVector.h"
#include "RevObject.h"
#include "RevPtr.h"
#include "RevVariable.h"
#include "RlConstantNode.h"
#include "RlDagMemberFunction.h"
#include "RlDeterministicNode.h"
#include "RlStochasticNode.h"
#include "RlTypedFunction.h"
#include "StochasticNode.h"
#include "TypedDagNode.h"
#include "TypedDistribution.h"
#include "TypedFunction.h"
#include "UserFunctionNode.h"

namespace RevLanguage {
class TypeSpec;

    class Dist_PhyloWhiteNoise :  public TypedDistribution< ModelVector<RealPos>  > {
        
    public:
                                                        Dist_PhyloWhiteNoise( void );
        virtual                                        ~Dist_PhyloWhiteNoise();
        
        // Basic utility functions
        Dist_PhyloWhiteNoise*                           clone(void) const;                                                                      //!< Clone the object
        static const std::string&                       getClassType(void);                                                                     //!< Get Rev type
        static const TypeSpec&                          getClassTypeSpec(void);                                                                 //!< Get class type spec
        std::string                                     getDistributionFunctionName(void) const;                                                //!< Get the Rev-name for this distribution.
        const TypeSpec&                                 getTypeSpec(void) const;                                                                //!< Get the type spec of the instance
        const MemberRules&                              getParameterRules(void) const;                                                          //!< Get member rules (const)
        void                                            printValue(std::ostream& o) const;                                                      //!< Print the general information on the function ('usage')
        
        
        
        // Distribution functions you have to override
        RevBayesCore::PhyloWhiteNoiseProcess*           createDistribution(void) const;
        
    protected:
        
        void                                            setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var);       //!< Set member variable
        
        
    private:
        
        RevPtr<const RevVariable>                       tree;
        RevPtr<const RevVariable>                       sigma;
        
    };
    
}

#endif /* defined(Dist_PhyloWhiteNoise_H) */
