#pragma once

#include "Vulkanbase/Helperstructs/BaseComponent.h"
#include "VulkanBase/HelperStructs/IRenderable.h"
#include "VulkanBase/HelperStructs/HelperStructs.h"
#include "PhysicsGame/Camera.h"

class TransformGizmoComponent : public BaseComponent, public IRenderable
{
public:

	TransformGizmoComponent(Mesh* pParent, Camera* camera);

private:

	Camera* m_PlayerCamera{};


	// Rendering

	bool m_IsHidden{ true };

	std::vector<Vertex> m_Vertices{};

	std::vector<uint32_t> m_Indices{};

	std::optional<uint32_t> m_RenderID{};
	PipelinesEnum m_PipelineID{ PipelinesEnum::regular };


	const std::vector<uint32_t>& GetIndices() const override { return m_Indices; };
	const std::vector<Vertex>& GetVertices() const override { return m_Vertices; }
	
	uint32_t GetRenderID() const override { return m_RenderID.value(); }
	void SetRenderID(uint32_t index) override { m_RenderID = index; }
	
	PipelinesEnum GetPipelineID() const override { return m_PipelineID; }
	std::string GetAlbedoString() const { return "Resources/texs/Manny_BaseColor.png"; };
	
	void Render(VkCommandBuffer buffer) const override;
	
	bool IsHidden() const override { return m_IsHidden; }
	void SetHidden(bool newHidden) { m_IsHidden = newHidden; }
};