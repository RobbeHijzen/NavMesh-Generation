#pragma once
#include "VulkanBase/HelperStructs/HelperStructs.h"
#include "NavMeshStructs.h"
#include "PathFindingStructs.h"
#include "VulkanBase/Scene/Scene.h"

class PathFinder : public Object
{
public:

	std::vector<const NavMeshStructs::Voxel*> GetPath(const std::vector<NavMeshStructs::VoxelNode>& graph,
		const NavMeshStructs::VoxelNode* startVoxel, const NavMeshStructs::VoxelNode* endVoxel);
	std::vector<const NavMeshStructs::Voxel*> GetPath(const std::vector<NavMeshStructs::VoxelNode>& graph,
														int startIndex, int endIndex);

	const NavMeshStructs::VoxelNode* GetVoxelNodeFromVoxel(const std::vector<NavMeshStructs::VoxelNode>& voxelNodes, const NavMeshStructs::Voxel* voxel) const;

private:

	float GetCost(const NavMeshStructs::Voxel* v1, const NavMeshStructs::Voxel* v2);
	float GetCost(const NavMeshStructs::VoxelNode* v1, const NavMeshStructs::VoxelNode* v2);
	float GetCost(const NavMeshStructs::VoxelNode* v1, const NavMeshStructs::Voxel* v2);


	struct NodeRecordCompare
	{
		bool operator()(const PathFindingStructs::NodeRecord& a, const PathFindingStructs::NodeRecord& b) const
		{
			return a.estimatedTotalCost > b.estimatedTotalCost;
		}
	};

};