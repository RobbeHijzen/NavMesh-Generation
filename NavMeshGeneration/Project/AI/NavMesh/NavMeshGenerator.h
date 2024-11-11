#pragma once
#include "NavMeshStructs.h"
#include "PathfindingStructs.h"
#include "VulkanBase/Scene/Scene.h"

class NavMeshGenerator : public Object, public IRenderable
{
public:

	NavMeshGenerator(Scene* scene);
	std::vector<NavMeshStructs::VoxelNode> GenerateNavMesh();

private:

	AABB m_Boundaries{ {-1000.f, -1000.f, -1000.f}, {1000.f, 1000.f, 1000.f} };
	int m_VoxelsAmountX{100};
	int m_VoxelsAmountY{51};
	int m_VoxelsAmountZ{100};


	std::vector<NavMeshStructs::Voxel> m_Voxels{};

	std::vector<int> m_WalkableVoxelsIndices{};	// pair: voxel and the index of the voxel in m_Voxels
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

	std::vector<Vertex> m_Vertices{};
	std::vector<uint32_t> m_Indices{};

	std::optional<uint32_t> m_RenderID{};

	std::vector<glm::mat4> m_ModelMatrices{};

	virtual const std::vector<Vertex>& GetVertices() const override { return m_Vertices; }
	virtual const std::vector<uint32_t>& GetIndices() const override { return m_Indices; }

	virtual uint32_t GetRenderID() const override { return m_RenderID.value(); }
	virtual void SetRenderID(uint32_t index) override { m_RenderID = index; }

	virtual void Render(VkCommandBuffer buffer) const override { vkCmdDrawIndexed(buffer, static_cast<uint32_t>(m_Indices.size()), 1, 0, 0, 0); }

	virtual PipelinesEnum GetPipelineID() const override { return PipelinesEnum::opacity; }

	virtual std::string GetAlbedoString() const override { return "Resources/texs/Green.png"; }
	virtual std::string GetMetallicString() const override { return ""; }
	virtual std::string GetRoughnessString() const override { return ""; }

	virtual std::vector<glm::mat4> GetModelMatrices() const override { return m_ModelMatrices; }
	virtual bool IsInstanceable() const override { return false; }
};