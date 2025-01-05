#pragma once
#include "NavMeshStructs.h"
#include "PathfindingStructs.h"
#include "VulkanBase/Scene/Scene.h"

class NavMeshGenerator : public Object, public IRenderable
{
public:

	NavMeshGenerator(Scene* scene);
	std::vector<NavMeshStructs::VoxelNode> GenerateNavMesh();
	const NavMeshStructs::Voxel* GetVoxelFromPosition(glm::vec3 position) const;

	void SetMaterial(Material* material) { m_Material = material; }
	Material* GetMaterial() const override { return m_Material; }

	const std::vector<NavMeshStructs::VoxelNode>& GetVoxelNodes() const { return m_VoxelNodes; }

	glm::vec3 GetVoxelSize() const;

private:

	AABB m_Boundaries{ {-1500.f, -400.f, -1500.f}, {1500.f, 400.f, 1500.f} };
	int m_VoxelsAmountX{75};
	int m_VoxelsAmountY{51};
	int m_VoxelsAmountZ{75};
	
	std::vector<NavMeshStructs::Voxel> m_Voxels{};

	std::vector<int> m_WalkableVoxelsIndices{};
	std::vector<NavMeshStructs::VoxelNode> m_VoxelNodes{};
	std::vector<NavMeshStructs::HeightMapPixel> m_HeightMap{};
	Scene* m_Scene{};

	void InitializeVoxels();
	void CheckForVoxelCollisions();
	void FillHeightMap();
	void FillWalkableVoxels();

	void FillVerticesAndIndices();

	void CreateVoxelNodes();
	std::vector<const NavMeshStructs::Voxel*> GetNeighborsFromVoxelIndex(int index);

	glm::i32vec3 GetXYZFromIndex(int index) const;
	int GetIndexFromXYZ(int x, int y, int z) const;

	//************************
	// Rendering
	//************************

	float m_RenderHeightOffset{0.5f};

	std::vector<Vertex> m_Vertices{ {{0.f, 0.f, 0.f}} };
	std::vector<uint32_t> m_Indices{0, 0, 0};

	std::optional<uint32_t> m_RenderID{};

	std::vector<glm::mat4> m_ModelMatrices{};

	virtual const std::vector<Vertex>& GetVertices() const override { return m_Vertices; }
	virtual const std::vector<uint32_t>& GetIndices() const override { return m_Indices; }

	virtual uint32_t GetRenderID() const override { return m_RenderID.value(); }
	virtual void SetRenderID(uint32_t index) override { m_RenderID = index; }

	virtual void Render(VkCommandBuffer buffer) const override { vkCmdDrawIndexed(buffer, static_cast<uint32_t>(m_Indices.size()), 1, 0, 0, 0); }

	virtual PipelinesEnum GetPipelineID() const override { return PipelinesEnum::opacity; }
	virtual bool IsHidden() const override { return false; }

	Material* m_Material{};

	virtual std::vector<glm::mat4> GetModelMatrices() const override { return m_ModelMatrices; }
	virtual bool IsInstanceable() const override { return false; }
};