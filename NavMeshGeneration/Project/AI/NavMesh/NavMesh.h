#pragma once

#include "NavMeshGenerator.h"
#include "PathFinder.h"

class NavMesh : public Object, public IRenderable
{
public:
	
	NavMesh(NavMeshGenerator* navMeshGenerator, PathFinder* pathFinder);

	void GenerateNavMesh();
	void GenerateNavMeshesTest(int amount);

	void GenerateRandomPath();
	void GenerateRandomPathsTest(int amount);

	// Rendering
	virtual const std::vector<Vertex>& GetVertices() const override { return m_Vertices; }
	virtual const std::vector<uint32_t>& GetIndices() const override { return m_Indices; }

	virtual uint32_t GetRenderID() const override { return m_RenderID.value(); }
	virtual void SetRenderID(uint32_t index) override { m_RenderID = index; }

	virtual void Render(VkCommandBuffer buffer) const override { vkCmdDrawIndexed(buffer, static_cast<uint32_t>(m_Indices.size()), 1, 0, 0, 0); }

	virtual PipelinesEnum GetPipelineID() const override { return PipelinesEnum::opacity; }

	virtual std::string GetAlbedoString() const override { return "Resources/texs/Red.png"; }
	virtual std::string GetMetallicString() const override { return ""; }
	virtual std::string GetRoughnessString() const override { return ""; }

private:

	NavMeshGenerator* m_NavMeshGenerator{};
	PathFinder* m_PathFinder{};

	std::vector<NavMeshStructs::VoxelNode> m_VoxelNodes{};


	// Rendering

	void FillVerticesAndIndices(std::vector<const NavMeshStructs::Voxel*> path);

	float m_RenderHeightOffset{ 5.f };

	std::vector<Vertex> m_Vertices{};
	std::vector<uint32_t> m_Indices{};

	std::optional<uint32_t> m_RenderID{};

	std::vector<glm::mat4> m_ModelMatrices{};

};