#pragma once

#include "NavMeshStructs.h"

namespace PathFindingStructs
{
	struct Connection
	{
		const NavMeshStructs::Voxel* fromVoxel{};
		const NavMeshStructs::Voxel* toVoxel{};

		bool operator==(const Connection& other) const
		{
			return fromVoxel == other.fromVoxel
				&& toVoxel == other.toVoxel;
		};
	};

	struct NodeRecord
	{
		const NavMeshStructs::VoxelNode* voxelNode{};
		Connection connection{};

		float costSoFar{};
		float estimatedTotalCost{};

		bool operator==(const NodeRecord& other) const
		{
			return voxelNode == other.voxelNode
				&& connection == other.connection
				&& costSoFar == other.costSoFar
				&& estimatedTotalCost == other.estimatedTotalCost;
		};

		bool operator<(const NodeRecord& other) const
		{
			return estimatedTotalCost < other.estimatedTotalCost;
		};
	};


}
