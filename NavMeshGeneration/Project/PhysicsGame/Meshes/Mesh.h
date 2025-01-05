#pragma once

#include "vulkan/vulkan_core.h"
#include "glm/glm.hpp"
#include <vector>
#include <string>
#include <optional>

#include "VulkanBase/Scene/Object.h"
#include "VulkanBase/HelperStructs/IRenderable.h"
#include "VulkanBase/Materials/Material.h"

#include "VulkanBase/HelperStructs/VertexInfo.h"
#include "PhysicsGame/Camera.h"
#include "Vulkanbase/EventSystem/Events.h"
#include "Vulkanbase/EventSystem/Observer.h"

#include "Vulkanbase/Helperstructs/BaseComponent.h"

class Mesh final : public Object, public IRenderable
{
public:
	Mesh(std::string objPath);

	//----------
	// Rendering
	//----------

	void Render(VkCommandBuffer buffer) const override;
	void Update(GLFWwindow* window) override;

	glm::mat4 GetModelMatrix() const override { return m_ModelMatrix; }

	const std::vector<uint32_t>& GetIndices() const override { return m_Indices; };
	const std::vector<Vertex>& GetVertices() const override { return m_Vertices; }

	uint32_t GetRenderID() const override { return m_RenderID.value(); }
	void SetRenderID(uint32_t index) override { m_RenderID = index; }
	PipelinesEnum GetPipelineID() const override { return m_PipelineID; }

	void SetMaterial(Material* material) { m_Material = material; }
	Material* GetMaterial() const override { return m_Material; }

	virtual bool IsInstanceable() const override { return m_IsInstanceable; }
	virtual std::vector<glm::mat4> GetModelMatrices() const override { return m_InstancedModelMatrices; }

	void SetInstanceable(bool newInstanceable) { m_IsInstanceable = newInstanceable; }
	void AddInstance(glm::mat4 newMatrix) { m_InstancedModelMatrices.emplace_back(newMatrix); }

	//----------
	// Transformation Handling
	//----------

	void AddPosition(glm::vec3 addedPos);
	void AddRotation(glm::vec3 addedRot);
	void AddScale(glm::vec3 addedScale);

	void SetPosition(glm::vec3 newPos);
	void SetRotation(glm::vec3 newRot);
	void SetScale(glm::vec3 newScale);

	
	glm::vec3 GetWorldPosition() const { return m_WorldPos; }
	glm::vec3 GetWorldRotation() const { return m_WorldRot; }
	glm::vec3 GetWorldScale() const { return m_WorldScale; }

	//-----------
	// Movement Handling
	//-----------

	void SetVelocity(glm::vec3 inputVelocity) { m_Velocity = inputVelocity; }

private:

	// Rendering

	Material* m_Material{ nullptr };

	std::vector<uint32_t> m_Indices{};
	std::vector<Vertex> m_Vertices{};

	std::optional<uint32_t> m_RenderID{};
	PipelinesEnum m_PipelineID{ PipelinesEnum::regular };

	
	//----------
	// Transformation Handling
	//----------
	glm::mat4 m_ModelMatrix{ glm::mat4{1.f} };

	glm::vec3 m_WorldPos{0.f, 0.f, 0.f};
	glm::vec3 m_WorldRot{0.f, 0.f, 0.f};
	glm::vec3 m_WorldScale{1.f, 1.f, 1.f};

	glm::mat4 m_TranslationMatrix{};
	glm::mat4 m_RotationMatrix{};
	glm::mat4 m_ScaleMatrix{};

	void CalculateWorldMatrix();

	// Instance Handling
	std::vector<glm::mat4> m_InstancedModelMatrices{};
	bool m_IsInstanceable{ false };

	//-----------
	// Movement Handling
	//-----------
	glm::vec3 m_Velocity{};

private:

	// Components
	std::vector<std::shared_ptr<BaseComponent>> m_Components{};

	// Observers
	std::vector<std::shared_ptr<Observer>> m_Observers{};


};