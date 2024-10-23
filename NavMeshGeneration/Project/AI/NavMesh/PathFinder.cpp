#include "PathFinder.h"
#include <list>

using namespace NavMeshStructs;
using namespace PathFindingStructs;

std::vector<const NavMeshStructs::Voxel*> PathFinder::GetPath(std::vector<VoxelNode> graph, int startIndex, int endIndex)
{
	std::vector<const Voxel*> result{};

	VoxelNode* startVoxel{ &graph[startIndex] };
	VoxelNode* endVoxel{ &graph[endIndex] };
	
	std::list<NodeRecord> openList{};
	std::list<NodeRecord> closedList{};
	NodeRecord currentNodeRecord{};

	currentNodeRecord.voxelNode = startVoxel;
	currentNodeRecord.connection = {};
	currentNodeRecord.costSoFar = 0;
	currentNodeRecord.estimatedTotalCost = GetCost(startVoxel, endVoxel);

	openList.emplace_back(currentNodeRecord);

	while (!openList.empty())
	{
		currentNodeRecord = *std::min_element(openList.begin(), openList.end());

		if (currentNodeRecord.voxelNode == endVoxel)
		{
			break;
		}

		for (auto neighbor : currentNodeRecord.voxelNode->neighbors)
		{
			float totalGCost{ currentNodeRecord.costSoFar + GetCost(currentNodeRecord.voxelNode, neighbor) };

			NodeRecord newNodeRecord{}; // Done here because of goto complaining

			for (auto& nodeRecord : closedList)
			{
				if (nodeRecord.voxelNode->voxel == neighbor)
				{
					if (nodeRecord.costSoFar > totalGCost)
					{
						closedList.remove(nodeRecord);
					}
					else
					{
						goto nextConnection;
					}
					break;
				}
			}
			for (auto& nodeRecord : openList)
			{
				if (nodeRecord.voxelNode->voxel == neighbor)
				{
					if (nodeRecord.costSoFar > totalGCost)
					{
						openList.remove(nodeRecord);
					}
					else
					{
						goto nextConnection;
					}
					break;
				}
			}

			newNodeRecord.voxelNode = GetVoxelNodeFromVoxel(graph, neighbor);
			newNodeRecord.costSoFar = totalGCost;
			newNodeRecord.estimatedTotalCost = totalGCost + GetCost(endVoxel, neighbor);
			newNodeRecord.connection = Connection{ currentNodeRecord.voxelNode->voxel, neighbor };

			openList.emplace_back(newNodeRecord);
		nextConnection:;
		}
		closedList.emplace_back(currentNodeRecord);
		openList.remove(currentNodeRecord);

	}
	closedList.emplace_back(currentNodeRecord);

	// Checks if the EndNode is in the list
	bool foundEndNode{ false };
	for (auto& nodeRecord : closedList)
	{
		if (nodeRecord.voxelNode == endVoxel)
		{
			foundEndNode = true;
			break;
		}
	}
	if (!foundEndNode) return result;

	// BackTracking
	while (currentNodeRecord.voxelNode != startVoxel)
	{
		result.emplace_back(currentNodeRecord.voxelNode->voxel);
		for (const auto& nodeRecord : closedList)
		{
			if (nodeRecord.voxelNode->voxel == currentNodeRecord.connection.fromVoxel)
			{
				currentNodeRecord = nodeRecord;
				break;
			}
		}
	}
	result.emplace_back(startVoxel->voxel);
	
	std::reverse(result.begin(), result.end());
	return result;
}

float PathFinder::GetCost(const NavMeshStructs::Voxel* v1, const NavMeshStructs::Voxel* v2)
{
	return v1->bounds.min.x * v2->bounds.min.x + v1->bounds.min.y * v2->bounds.min.y + v1->bounds.min.z * v2->bounds.min.z;
}

float PathFinder::GetCost(const NavMeshStructs::VoxelNode* v1, const NavMeshStructs::VoxelNode* v2)
{
	return GetCost(v1->voxel, v2->voxel);
}

float PathFinder::GetCost(const NavMeshStructs::VoxelNode* v1, const NavMeshStructs::Voxel* v2)
{
	return GetCost(v1->voxel, v2);
}

const NavMeshStructs::VoxelNode* PathFinder::GetVoxelNodeFromVoxel(const std::vector<NavMeshStructs::VoxelNode>& voxelNodes, const NavMeshStructs::Voxel* voxel)
{
	for (const auto& voxelNode : voxelNodes)
	{
		if (voxelNode.voxel == voxel)
			return &voxelNode;
	}

	return nullptr;
}
