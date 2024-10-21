#pragma once
#include "VulkanBase/HelperStructs/HelperStructs.h"

enum class VoxelTypes
{
	Empty,
	Solid
};

struct Voxel
{
	AABB bounds{};
	VoxelTypes type{};
};

struct Node
{

};

struct Span
{
	VoxelTypes type{};
	int amount{};

	int startIndex{-1};
};

class HeightMapPixel
{
public:
	HeightMapPixel(const std::vector<Voxel>& allVoxels, int startIndex, int length)
		: m_AllVoxels{allVoxels}
	{
		for (int index{ startIndex}; index < startIndex + length;)
		{
			VoxelTypes currentType{ allVoxels[index].type };

			Span newSpan{};
			newSpan.type = currentType;
			newSpan.startIndex = index;
			int spanSize{ 1 };

			++index;

			while (index < startIndex + length && allVoxels[index].type == currentType)
			{
				++spanSize;
				++index;
			}

			newSpan.amount = spanSize;
			m_Spans.emplace_back(newSpan);
		}

		CalculateWalkableIndices();
	}

	void CalculateWalkableIndices()
	{
		for (int index{}; index < m_Spans.size(); ++index)
		{
			auto& span{ m_Spans[index] };
			if (span.type == VoxelTypes::Empty) continue;
			
			if (index == m_Spans.size() - 1) m_WalkableIndices.emplace_back(span.startIndex + span.amount - 1);

			if (m_Spans[index + 1].amount < m_AgentHeightInVoxels) { ++index; continue; }

			m_WalkableIndices.emplace_back(span.startIndex + span.amount - 1);
		}
	}

	void SetAgentHeight(int heightInVoxels) { m_AgentHeightInVoxels = heightInVoxels; }

	auto GetWalkableIndices() const { return m_WalkableIndices; }

private:
	
	const std::vector<Voxel>& m_AllVoxels{};
	std::vector<Span> m_Spans{};

	std::vector<int> m_WalkableIndices{};

	int m_AgentHeightInVoxels;
};
