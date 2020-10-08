#ifndef UniformSerialSampledTimeTreeDistribution_H
#define UniformSerialSampledTimeTreeDistribution_H

#include <stddef.h>
#include <vector>

#include "Tree.h"
#include "TypedDistribution.h"
#include "Taxon.h"

namespace RevBayesCore {
class DagNode;
class TopologyNode;
template <class valueType> class RbOrderedSet;
template <class valueType> class TypedDagNode;
    
    class UniformSerialSampledTimeTreeDistribution : public TypedDistribution<Tree> {
        
    public:
        UniformSerialSampledTimeTreeDistribution(const TypedDagNode<double> *a, const std::vector<Taxon> &n, const bool &ur);                                                                                  //!< Constructor

        virtual                                            ~UniformSerialSampledTimeTreeDistribution(void);                          //!< Virtual destructor
        
        // public member functions
        UniformSerialSampledTimeTreeDistribution*           clone(void) const;                                          //!< Create an independent clone
        double                                              computeLnProbability(void);                                 //!< Compute ln prob of current value
        void                                                redrawValue(void);                                          //!< Draw a new random value from distribution

        
    protected:
        // Parameter management functions
        virtual void                                        getAffected(RbOrderedSet<DagNode *>& affected, DagNode* affecter);                                      //!< get affected nodes
        virtual void                                        keepSpecialization(DagNode* affecter);
        virtual void                                        restoreSpecialization(DagNode *restorer);
        virtual void                                        touchSpecialization(DagNode *toucher, bool touchAll);

        void                                                swapParameterInternal(const DagNode *oldP, const DagNode *newP);            //!< Swap a parameter
        
    private:


        // helper functions
        void                                                simulateTree(void);
        void                                                buildSerialSampledRandomBinaryTree(Tree *psi, std::vector<TopologyNode*> &nodes, const std::vector<double> &ages);
        std::vector<double>                                 simulateCoalescentAges() const;
        
        // members
        const TypedDagNode<double>*                         start_age;
        size_t                                              num_taxa;
        std::vector<Taxon>                                  taxa;
        bool                                                has_root_age;

    };
    
}

#endif
