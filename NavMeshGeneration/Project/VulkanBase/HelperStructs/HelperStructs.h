#pragma once

#include "VulkanUtil/VulkanUtil.h"
#include <glm/gtc/matrix_transform.hpp>
#include <optional>

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool IsComplete() const
	{
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct ShaderUBO
{
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj; 

	int useNormalMap{ 0 };
};

struct AABB2D
{
	glm::vec2 min{};
	glm::vec2 max{};
};

struct AABB
{
	glm::vec3 min;
	glm::vec3 max;

	bool operator==(const AABB& other) const
	{
		return min == other.min && max == other.max;
	}
	bool AreColliding(AABB other) const
	{
		return
			other.max.x > min.x &&
			other.max.y > min.y &&
			other.max.z > min.z &&

			other.min.x < max.x &&
			other.min.y < max.y &&
			other.min.z < max.z;
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
	
	bool Contains(glm::vec3 point) const
	{
		return point.x > min.x && point.y > min.y && point.z > min.z &&
			point.x < max.x && point.y < max.y && point.z < max.z;
	}

	glm::vec3 GetMiddle() const
	{
		return min + ((max - min) / 2.f);
	}

};
