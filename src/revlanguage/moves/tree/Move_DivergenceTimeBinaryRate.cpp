//
//  Move_DivergenceTimeBinaryRate.cpp
//  revbayes
//
//  Created by Shiran Abadi on 6/17/20.
//  Copyright © 2020 Shiran Abadi. All rights reserved.
//

#include "Move_DivergenceTimeBinaryRate.h"
#include "DivergenceTimeBinaryRateProposal.h"
#include <stddef.h>
#include <ostream>
#include <string>

#include "ArgumentRule.h"
#include "ArgumentRules.h"
#include "AbstractHomologousDiscreteCharacterData.h"
#include "RlAbstractHomologousDiscreteCharacterData.h"
#include "MetropolisHastingsMove.h"
#include "RealPos.h"
#include "RlTimeTree.h"
#include "TypeSpec.h"
#include "Move.h"
#include "RevObject.h"
#include "RevPtr.h"
#include "RevVariable.h"
#include "RlMove.h"
#include "StochasticNode.h"

namespace RevBayesCore { class Proposal; }
namespace RevBayesCore { class AbstractHomologousDiscreteCharacterData; }
namespace RevBayesCore { template <class valueType> class TypedDagNode; }


using namespace RevLanguage;

Move_DivergenceTimeBinaryRate::Move_DivergenceTimeBinaryRate() : Move()
{
    
}


/**
 * The clone function is a convenience function to create proper copies of inherited objected.
 * E.g. a.clone() will create a clone of the correct type even if 'a' is of derived type 'b'.
 *
 * \return A new copy of the process.
 */
Move_DivergenceTimeBinaryRate* Move_DivergenceTimeBinaryRate::clone(void) const
{
    
    return new Move_DivergenceTimeBinaryRate(*this);
}


void Move_DivergenceTimeBinaryRate::constructInternalObject( void )
{
    
    // we free the memory first
    delete value;
    
    double w = static_cast<const RealPos &>( weight->getRevObject() ).getValue();

    RevBayesCore::TypedDagNode<RevBayesCore::AbstractHomologousDiscreteCharacterData>* ctmc_tdn = NULL;
    RevBayesCore::StochasticNode<RevBayesCore::AbstractHomologousDiscreteCharacterData>* ctmc_sn = NULL;

    if ( static_cast<const RevLanguage::AbstractHomologousDiscreteCharacterData&>( ctmc->getRevObject() ).isModelObject() )
    {
        ctmc_tdn = static_cast<const RevLanguage::AbstractHomologousDiscreteCharacterData&>( ctmc->getRevObject() ).getDagNode();
        ctmc_sn  = static_cast<RevBayesCore::StochasticNode<RevBayesCore::AbstractHomologousDiscreteCharacterData>* >(ctmc_tdn);
    }
    else
    {
        throw RbException("mvDivergenceTimeBinaryRate() requires a CTMC.");
    }
    
    std::string charTypeSTR = (ctmc_sn->getValue()).getDataType();
    RevBayesCore::Proposal *p ;

    if (charTypeSTR == "NaturalNumbers")
    {
        p = new RevBayesCore::DivergenceTimeBinaryRateProposal<RevBayesCore::NaturalNumbersState>(ctmc_sn);
    }
    else if (charTypeSTR == "DNA")
    {
        p = new RevBayesCore::DivergenceTimeBinaryRateProposal<RevBayesCore::DnaState>(ctmc_sn);
    }
    else
    {
        throw RbException( "Invalid data type. Valid data types are: NaturalNumbers|DNA" );
    }
        
    value = new RevBayesCore::MetropolisHastingsMove(p,w);

    
}

/** Get Rev type of object */
const std::string& Move_DivergenceTimeBinaryRate::getClassType(void)
{
    
    static std::string rev_type = "Move_DivergenceTimeBinaryRate";
    
    return rev_type;
}

/** Get class type spec describing type of object */
const TypeSpec& Move_DivergenceTimeBinaryRate::getClassTypeSpec(void)
{
    
    static TypeSpec rev_type_spec = TypeSpec( getClassType(), new TypeSpec( Move::getClassTypeSpec() ) );
    
    return rev_type_spec;
}


/**
 * Get the Rev name for the constructor function.
 *
 * \return Rev name of constructor function.
 */
std::string Move_DivergenceTimeBinaryRate::getMoveName( void ) const
{
    // create a constructor function name variable that is the same for all instance of this class
    std::string c_name = "DivergenceTimeBinaryRate";
    
    return c_name;
}


/** Return member rules (no members) */
const MemberRules& Move_DivergenceTimeBinaryRate::getParameterRules(void) const
{
    
    static MemberRules memberRules;
    static bool rules_set = false;
    
    if ( !rules_set )
    {
        memberRules.push_back( new ArgumentRule("ctmc", AbstractHomologousDiscreteCharacterData::getClassTypeSpec(), "The continuous-time Markov process to monitor.", ArgumentRule::BY_REFERENCE, ArgumentRule::ANY, NULL ) );

        /* Inherit weight from Move, put it after variable */
        const MemberRules& inheritedRules = Move::getParameterRules();
        memberRules.insert( memberRules.end(), inheritedRules.begin(), inheritedRules.end() );
        
        rules_set = true;
    }
    
    return memberRules;
}

/** Get type spec */
const TypeSpec& Move_DivergenceTimeBinaryRate::getTypeSpec( void ) const
{
    
    static TypeSpec type_spec = getClassTypeSpec();
    
    return type_spec;
}



/** Get type spec */
void Move_DivergenceTimeBinaryRate::printValue(std::ostream &o) const
{
    
    o << "Move_DivergenceTimeBinaryRate(";
    if (ctmc != NULL)
    {
        o << ctmc->getName();
    }
    else
    {
        o << "?";
    }
    o << ")";
}


/** Set a NearestNeighborInterchange variable */
void Move_DivergenceTimeBinaryRate::setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var)
{
    
    if ( name == "ctmc" )
    {
        ctmc = var;
    }
    else
    {
        Move::setConstParameter(name, var);
    }
}
