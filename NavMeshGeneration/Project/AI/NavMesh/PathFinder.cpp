#include "PathFinder.h"
#include <list>
#include <queue>

using namespace NavMeshStructs;
using namespace PathFindingStructs;

std::vector<const NavMeshStructs::Voxel*> PathFinder::GetPath(const std::vector<VoxelNode>& graph, const VoxelNode* startVoxel, const VoxelNode* endVoxel)
{
    if (!startVoxel || !endVoxel) return {};

	std::vector<const Voxel*> result{};
    
	std::priority_queue<NodeRecord, std::vector<NodeRecord>, NodeRecordCompare> openList{};
	std::unordered_map<const VoxelNode*, NodeRecord> closedList{};
    NodeRecord startNodeRecord{startVoxel, {}, 0, GetCost(startVoxel, endVoxel)};

    openList.emplace(startNodeRecord);

    while (!openList.empty()) 
	{
        NodeRecord currentNodeRecord = openList.top();
        openList.pop();

        // Check if we reached the goal
        if (currentNodeRecord.voxelNode == endVoxel) 
		{
            closedList[endVoxel] = currentNodeRecord;
            break;
        }

        // Explore neighbors
        for (auto neighbor : currentNodeRecord.voxelNode->neighbors) 
		{
            float totalGCost = currentNodeRecord.costSoFar + GetCost(currentNodeRecord.voxelNode, neighbor);

            auto closedIter = closedList.find(GetVoxelNodeFromVoxel(graph, neighbor));
            if (closedIter != closedList.end() && closedIter->second.costSoFar <= totalGCost) 
			{
                continue;
            }

            NodeRecord newNodeRecord
			{
                GetVoxelNodeFromVoxel(graph, neighbor),
                {currentNodeRecord.voxelNode->voxel, neighbor},
                totalGCost,
                totalGCost + GetCost(endVoxel, neighbor)
            };

            openList.emplace(newNodeRecord);
            closedList[newNodeRecord.voxelNode] = newNodeRecord;
        }
    }

    // If we did not reach the end voxel, return an empty path
    if (closedList.find(endVoxel) == closedList.end()) 
	{
        return result;
    }

    // Backtrack to construct the path
    NodeRecord currentNodeRecord = closedList[endVoxel];
    while (currentNodeRecord.voxelNode != startVoxel) 
	{
        result.emplace_back(currentNodeRecord.voxelNode->voxel);
        currentNodeRecord = closedList[GetVoxelNodeFromVoxel(graph, currentNodeRecord.connection.fromVoxel)];
    }
    result.emplace_back(startVoxel->voxel);

    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<const NavMeshStructs::Voxel*> PathFinder::GetPath(const std::vector<NavMeshStructs::VoxelNode>& graph, int startIndex, int endIndex)
{
    return GetPath(graph, &graph[startIndex], &graph[endIndex]);
}

float PathFinder::GetCost(const NavMeshStructs::Voxel* v1, const NavMeshStructs::Voxel* v2)
{
	//return v1->bounds.min.x * v2->bounds.min.x + v1->bounds.min.y * v2->bounds.min.y + v1->bounds.min.z * v2->bounds.min.z;
	return glm::distance(v1->bounds.min, v2->bounds.min);
}

float PathFinder::GetCost(const NavMeshStructs::VoxelNode* v1, const NavMeshStructs::VoxelNode* v2)
{
	return GetCost(v1->voxel, v2->voxel);
}

float PathFinder::GetCost(const NavMeshStructs::VoxelNode* v1, const NavMeshStructs::Voxel* v2)
{
	return GetCost(v1->voxel, v2);
}

const NavMeshStructs::VoxelNode* PathFinder::GetVoxelNodeFromVoxel(const std::vector<NavMeshStructs::VoxelNode>& voxelNodes, const NavMeshStructs::Voxel* voxel) const
{
	for (const auto& voxelNode : voxelNodes)
	{
		if (voxelNode.voxel == voxel)
			return &voxelNode;
	}

	return nullptr;
}
