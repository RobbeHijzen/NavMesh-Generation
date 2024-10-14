#pragma once
#include "NavMeshStructs.h"
#include "VulkanBase/Scene/Scene.h"

class NavMeshGenerator : public Object, public IRenderable
{
public:

	NavMeshGenerator(Scene* scene);
	std::vector<Node> GenerateNavMesh();

private:

	AABB m_Boundaries{ {-1000.f, -1000.f, -1000.f}, {1000.f, 1000.f, 1000.f} };
	int m_VoxelsAmountX{50};
	int m_VoxelsAmountY{10};
	int m_VoxelsAmountZ{50};

	std::vector<std::vector<std::vector<Voxel>>> m_Voxels{};
	Scene* m_Scene{};

	void InitializeVoxels();
	void CheckForVoxelCollisions();
	void FillHeightMap();

	void FillVerticesAndIndices();

	// Members for rendering

	float m_RenderHeightOffset{0.5f};

	std::vector<Vertex> m_Vertices{};
	std::vector<uint32_t> m_Indices{};

	std::optional<uint32_t> m_RenderID{};

	virtual const std::vector<Vertex>& GetVertices() const override { return m_Vertices; }
	virtual const std::vector<uint32_t>& GetIndices() const override { return m_Indices; }

	virtual uint32_t GetRenderID() const override { return m_RenderID.value(); }
	virtual void SetRenderID(uint32_t index) override { m_RenderID = index; }

	virtual void Render(VkCommandBuffer buffer) const override { vkCmdDrawIndexed(buffer, static_cast<uint32_t>(m_Indices.size()), 1, 0, 0, 0); }

	virtual PipelinesEnum GetPipelineID() const override { return PipelinesEnum::opacity; }
	virtual std::string GetDiffuseString() const override { return "Resources/texs/NavMesh.png"; }

};