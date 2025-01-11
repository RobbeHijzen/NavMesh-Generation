#pragma once

#include "NavMeshGenerator.h"
#include "PathFinder.h"

class NavMesh : public Object, public IRenderable
{
public:
	
	NavMesh(NavMeshGenerator* navMeshGenerator, PathFinder* pathFinder);
	virtual void Update(GLFWwindow* window) override;

	void GenerateNavMesh();
	void GenerateNavMeshLocally(std::vector<AABB> areas);
	void GenerateNavMeshesTest(int amount);

	std::vector<glm::vec3> GeneratePath(glm::vec3 startPoint, glm::vec3 endPoint);
	void GenerateRandomPath();
	void GenerateRandomPathsTest(int amount);

	// Rendering
	virtual const std::vector<Vertex>& GetVertices() const override { return m_Vertices; }
	virtual const std::vector<uint32_t>& GetIndices() const override { return m_Indices; }

	virtual uint32_t GetRenderID() const override { return m_RenderID.value(); }
	virtual void SetRenderID(uint32_t index) override { m_RenderID = index; }

	virtual void Render(VkCommandBuffer buffer) const override 
	{ 
		vkCmdDrawIndexed(buffer, static_cast<uint32_t>(m_Indices.size()), 1, 0, 0, 0); 
	}

	virtual PipelinesEnum GetPipelineID() const override { return PipelinesEnum::opacity; }
	virtual bool IsHidden() const override { return true; }

	void SetMaterial(Material* material) { m_Material = material; }
	Material* GetMaterial() const override { return m_Material; }

	void SetNavMeshDirty(const AABB& area);
	void SetNavMeshDirty();

private:

	NavMeshGenerator* m_NavMeshGenerator{};
	PathFinder* m_PathFinder{};

	std::vector<NavMeshStructs::VoxelNode> m_VoxelNodes{};

	bool m_IsNavMeshDirty{ false };
	std::vector<AABB> m_DirtyAreas{};

	// Rendering

	void FillVerticesAndIndices(std::vector<const NavMeshStructs::Voxel*> path);

	float m_RenderHeightOffset{ 0.6f };

	std::vector<Vertex> m_Vertices{ {{0.f, 0.f, 0.f}} };
	std::vector<uint32_t> m_Indices{0, 0, 0};

	std::optional<uint32_t> m_RenderID{};

	Material* m_Material{};

	std::vector<glm::mat4> m_ModelMatrices{};
};