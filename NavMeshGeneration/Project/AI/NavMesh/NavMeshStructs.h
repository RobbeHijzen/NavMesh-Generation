#pragma once
#include "VulkanBase/HelperStructs/HelperStructs.h"


struct Voxel
{
	AABB bounds{};
	float currentHighestPoint{ -FLT_MAX };
	AABB2D intersectedAABB{};

	bool isSolid{ false };
};

struct Node
{

};
