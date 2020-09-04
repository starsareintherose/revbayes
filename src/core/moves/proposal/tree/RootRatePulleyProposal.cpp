#include "DistributionBeta.h"
#include "RootRatePulleyProposal.h"
#include "RandomNumberFactory.h"
#include "RandomNumberGenerator.h"
#include "RbException.h"
#include "TreeUtilities.h"
#include "TypedDagNode.h"

#include <cmath>
#include <iostream>

using namespace RevBayesCore;

/**
 * Constructor
 *
 * Here we simply allocate and initialize the Proposal object.
 */
RootRatePulleyProposal::RootRatePulleyProposal(StochasticNode<Tree> *n, double p) : Proposal(p),
    tree( n )
{
    // tell the base class to add the node
    addNode( tree );

}


/**
 * Add a variable.
 */
void RootRatePulleyProposal::addRates( std::vector<StochasticNode<double> *> v)
{

    // add it to the nodes vector
    for (std::vector<StochasticNode<double>* >::iterator it = v.begin(); it != v.end(); ++it)
    {
        // get the pointer to the current node
        DagNode* the_node = *it;
        
        addNode( the_node );
    }

    branch_rates.push_back( v );
    
}

void RootRatePulleyProposal::addRates(StochasticNode<RbVector<double> > *v)
{

    // add it to the nodes vector
	addNode( v );

    branch_vectors.push_back( v );

}

/**
 * The cleanProposal function may be called to clean up memory allocations after AbstractMove
 * decides whether to accept, reject, etc. the proposed value.
 *
 */
void RootRatePulleyProposal::cleanProposal( void )
{
    
}

/**
 * The clone function is a convenience function to create proper copies of inherited objected.
 * E.g. a.clone() will create a clone of the correct type even if 'a' is of derived type 'b'.
 *
 * \return A new copy of the proposal.
 */
RootRatePulleyProposal* RootRatePulleyProposal::clone( void ) const
{
    
    return new RootRatePulleyProposal( *this );
}


/**
 * Get Proposals' name of object
 *
 * \return The Proposals' name.
 */
const std::string& RootRatePulleyProposal::getProposalName( void ) const
{
    static std::string name = "RootRatePulleyProposal";
    
    return name;
}


double RootRatePulleyProposal::getProposalTuningParameter( void ) const
{
    return 0.0;
}


/**
 * Perform the proposal.
 *
 * A scaling Proposal draws a random uniform number u ~ unif (-0.5,0.5)
 * and scales the current vale by a scaling factor
 * sf = exp( alpha * u )
 * where alpha is the tuning parameter of the Proposal to influence the size of the proposals.
 *
 * \return The hastings ratio.
 */
double RootRatePulleyProposal::doProposal( void )
{
    
    // Get random number generator
    RandomNumberGenerator* rng     = GLOBAL_RNG;

    Tree& tau = tree->getValue();
    RbOrderedSet<DagNode*> affected;
    tree->getAffectedNodes( affected );

    // get the root
    TopologyNode* node = &tau.getRoot();
    size_t node_index = node->getIndex();

    abort = node->getChild(0).isSampledAncestor() || node->getChild(1).isSampledAncestor();

    // abort if one descendant is a sampled ancestor
    if ( abort == true )
    {
    	return RbConstants::Double::neginf;
    }

    stored_rates.clear();
    for( size_t i = 0; i < branch_rates.size(); ++i )
    {

        // make a container for the old values for this vector of rates
        std::vector<double> these_rates;

        // add all of the child rates
        for (size_t j = 0; j < node->getNumberOfChildren(); j++)
        {
            size_t child_index = node->getChild(j).getIndex();
            these_rates.push_back( branch_rates[i][child_index]->getValue() );
        }

        // add the vector to the stored rates
        stored_rates.push_back( these_rates );

    }

    stored_vectors.clear();
    for( size_t i = 0; i < branch_vectors.size(); ++i )
    {
        // make a container for the old values for this vector of rates
        std::vector<double> these_rates;

        // add all of the child rates
        for (size_t j = 0; j < node->getNumberOfChildren(); j++)
        {
            size_t child_index = node->getChild(j).getIndex();
            these_rates.push_back( branch_vectors[i]->getValue()[child_index] );
        }

        // add the vector to the stored rates
        stored_vectors.push_back( these_rates );

    }

	// make sure there's only two descendants
	if ( node->getNumberOfChildren() > 2 )
	{
		throw RbException("RootRatePulleyMove only works with bifurcation at the root.");
	}

	// get the descendants
	TopologyNode* left_node  = &node->getChild(0);
	size_t left_index        = left_node->getIndex();
	double t_left            = left_node->getBranchLength();

	TopologyNode* right_node = &node->getChild(1);
	size_t right_index       = right_node->getIndex();
	double t_right           = right_node->getBranchLength();

    // set the rates
    for(size_t i = 0; i < branch_rates.size(); ++i )
    {

    	// get the rates
    	double r_left  = branch_rates[i][left_index]->getValue();
    	double r_right = branch_rates[i][right_index]->getValue();

    	// get the total effective branch length
    	double v = r_left * t_left + r_right * t_right;

    	// draw the new values
    	double u = rng->uniform01();

    	// compute the new rates
    	double v_left  = v * u;
    	double v_right = v * (1 - u);

    	double r_left_prime  = v_left  / t_left;
    	double r_right_prime = v_right / t_right;

    	branch_rates[i][left_index]->getValue()  = r_left_prime;
    	branch_rates[i][right_index]->getValue() = r_right_prime;

    }

    for(size_t i = 0; i < branch_vectors.size(); ++i )
    {

    	// get the rates
    	double r_left  = branch_vectors[i]->getValue()[left_index];
    	double r_right = branch_vectors[i]->getValue()[right_index];

    	// get the total effective branch length
    	double v = r_left * t_left + r_right * t_right;

    	// draw the new values
    	double u = rng->uniform01();

    	// compute the new rates
    	double v_left  = v * u;
    	double v_right = v * (1 - u);

    	double r_left_prime  = v_left / t_left;
    	double r_right_prime = v_right / t_right;

    	branch_vectors[i]->getValue()[left_index]  = r_left_prime;
    	branch_vectors[i]->getValue()[right_index] = r_right_prime;


    }

    return 0.0;
    
}


/**
 * Prepare the proposal, e.g., pick the UpDown that we want to change.
 * Here we do not need to do any preparation.
 */
void RootRatePulleyProposal::prepareProposal( void )
{
    
}


/**
 * Print the summary of the Proposal.
 *
 * The summary just contains the current value of the tuning parameter.
 * It is printed to the stream that it passed in.
 *
 * \param[in]     o     The stream to which we print the summary.
 */
void RootRatePulleyProposal::printParameterSummary(std::ostream &o, bool name_only) const
{
    
    o << "alpha = ";
    if (name_only == false)
    {
        o << 0.0;
    }
    
}

/**
 * Reject the Proposal.
 *
 * Since the Proposal stores the previous value and it is the only place
 * where complex undo operations are known/implement, we need to revert
 * the value of the variable/DAG-node to its original value.
 */
void RootRatePulleyProposal::undoProposal( void )
{

    // undo the proposal

    // get the root
	Tree& tau = tree->getValue();
    TopologyNode* node = &tau.getRoot();
    size_t node_index = node->getIndex();

    // reset the rates
    for( size_t i = 0; i < branch_rates.size(); ++i )
    {

        for ( size_t j = 0; j < node->getNumberOfChildren(); j++ )
        {
            size_t child_index = node->getChild(j).getIndex();
            branch_rates[i][child_index]->getValue() = stored_rates[i][j];
        }

    }

    for( size_t i = 0; i < branch_vectors.size(); ++i )
    {

        for ( size_t j = 0; j < node->getNumberOfChildren(); j++ )
        {
            size_t child_index = node->getChild(j).getIndex();
            branch_vectors[i]->getValue()[child_index] = stored_rates[i][j];
        }

    }

}


/**
 * Swap the current variable for a new one.
 *
 * \param[in]     oldN     The old variable that needs to be replaced.
 * \param[in]     newN     The new RevVariable.
 */
void RootRatePulleyProposal::swapNodeInternal(DagNode *oldN, DagNode *newN)
{
    
    if (oldN == tree)
    {
        tree = static_cast<StochasticNode<Tree>* >(newN) ;
    }
    else
    {

        for (size_t i = 0; i < branch_rates.size(); ++i)
        {
            
            for (size_t j = 0; j < branch_rates[i].size(); j++)
            {
                if (oldN == branch_rates[i][j])
                {
                    branch_rates[i][j] = static_cast<StochasticNode<double>* >(newN);
                }
            }
            
        }

    }

    
}


void RootRatePulleyProposal::setProposalTuningParameter(double tp)
{
}


/**
 * Tune the Proposal to accept the desired acceptance ratio.
 *
 * The acceptance ratio for this Proposal should be around 0.44.
 * If it is too large, then we increase the proposal size,
 * and if it is too small, then we decrease the proposal size.
 */
void RootRatePulleyProposal::tune( double rate )
{
    
	return;
}
