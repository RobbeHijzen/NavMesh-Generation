#pragma once
#include "VertexInfo.h"
#include "PipelinesEnum.h"
#include <vector>
#include <string>

class IRenderable
{
public:
	
	virtual const std::vector<Vertex>& GetVertices() const = 0 ;
	virtual const std::vector<uint32_t>& GetIndices() const = 0 ;

	virtual uint32_t GetRenderID() const = 0;
	virtual void SetRenderID(uint32_t id) = 0;

	virtual void Render(VkCommandBuffer buffer) const = 0;

	virtual PipelinesEnum GetPipelineID() const = 0;

	virtual std::string GetAlbedoString() const = 0;
	virtual std::string GetMetallicString() const { return ""; }
	virtual std::string GetRoughnessString() const { return ""; }
	virtual std::string GetNormalMapString() const { return ""; }
	virtual bool UseNormalMap() const { return false; }
	
	virtual bool IsHidden() const { return false; }
	virtual bool IsInstanceable() const { return false; }

	virtual glm::mat4 GetModelMatrix() const { return glm::mat4{ 1 }; };
	virtual std::vector<glm::mat4> GetModelMatrices() const { return { glm::mat4{ 1 } }; };
};