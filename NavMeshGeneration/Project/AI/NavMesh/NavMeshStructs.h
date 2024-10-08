#pragma once
#include "VulkanBase/HelperStructs/HelperStructs.h"

struct AABB2D
{
	glm::vec2 min{};
	glm::vec2 max{};

	bool AreColliding(AABB other) const
	{
		return
			other.max.x > min.x &&
			other.max.z > min.y &&
			other.min.x < max.x &&
			other.min.z < max.y;
	}

	AABB2D IntersectionRegion(AABB other) const
	{
		AABB2D result{};

		result.min.x = std::max(min.x, other.min.x);
		result.min.y = std::max(min.y, other.min.z);

		result.max.x = std::min(max.x, other.max.x);
		result.max.y = std::min(max.y, other.max.z);

		return result;
	}
};

struct Voxel
{
	AABB2D bounds{};
	float currentHighestPoint{ -FLT_MAX };
	AABB2D intersectedAABB{};
};

struct Node
{

};
