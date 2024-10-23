#include "TransformGizmoComponent.h"

TransformGizmoComponent::TransformGizmoComponent(Mesh* pParent, Camera* camera)
	: BaseComponent(pParent)
	, m_PlayerCamera{camera}
{

}

void TransformGizmoComponent::Render(VkCommandBuffer buffer) const
{
	vkCmdDrawIndexed(buffer, static_cast<uint32_t>(m_Indices.size()), 1, 0, 0, 0);
}
