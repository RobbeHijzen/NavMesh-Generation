#pragma once

#include "Vulkanbase/Helperstructs/BaseComponent.h"
#include "VulkanBase/HelperStructs/IRenderable.h"
#include "PhysicsGame/Meshes/Mesh.h"
#include "VulkanBase/HelperStructs/HelperStructs.h"


class CollisionComponent : public BaseComponent , public IRenderable
{
public:

	CollisionComponent(Mesh* pParent, bool isStaticMesh, int aabbDepth, bool calculateAABBs = true);
	virtual void GameStart() override;

	bool HasStaticCollision() const { return m_HasStaticCollision; }

	auto GetAABBs() const { return m_TransformedAABBs; }

	bool IsInstanceable() const override { return true; }
	std::vector<glm::mat4> GetModelMatrices() const override { return m_ModelMatrices; }
	
	const std::vector<uint32_t>& GetIndices() const override { return m_Indices; };
	const std::vector<Vertex>& GetVertices() const override { return m_Vertices; }
	
	uint32_t GetRenderID() const override { return m_RenderID.value(); }
	void SetRenderID(uint32_t index) override { m_RenderID = index; }
	
	PipelinesEnum GetPipelineID() const override { return m_PipelineID; }

	Material* GetMaterial() const override { return m_Material.get(); }
	
	void Render(VkCommandBuffer buffer) const override;
	
	bool IsHidden() const override { return m_IsHidden; }
	void SetHidden(bool newHidden) { m_IsHidden = newHidden; }

	void SetAABBs(std::vector<AABB> newAABBs, bool transformAABBs = false) { m_AABBs = newAABBs; m_UsePresetAABBs = !transformAABBs; CalculateTransformedAABBs(); m_ModelMatrices.resize(m_AABBs.size()); }

private:

	bool m_IsHidden{ true };

	std::vector<glm::mat4> m_ModelMatrices{};
	void UpdateModelMatrix();

	bool m_HasStaticCollision;
	bool m_UsePresetAABBs{ false };

	std::vector<AABB> m_AABBs{};
	std::vector<AABB> m_TransformedAABBs{};

	void CalculateTransformedAABBs();

	static std::vector<Vertex> m_Vertices;
	static std::vector<uint32_t> m_Indices;

	std::optional<uint32_t> m_RenderID{};
	PipelinesEnum m_PipelineID{ PipelinesEnum::linesOnly };

	std::unique_ptr<Material> m_Material{};

};
