#include "Mesh.h"
#include "PhysicsGame/Utils.h"
#include "Vulkanbase/Time/Time.h"

#include <glm/gtc/matrix_transform.hpp>

Mesh::Mesh(std::string objPath)
{
    ParseOBJ(objPath, m_Vertices, m_Indices);

    AddObserver(new Observer(GameEvents::ModelMatrixChanged, [&] { this->CalculateWorldMatrix(); }));

    SetPosition(m_WorldPos);
    SetRotation(m_WorldRot);
    SetScale(m_WorldScale);
}

void Mesh::Render(VkCommandBuffer buffer) const
{
    vkCmdDrawIndexed(buffer, static_cast<uint32_t>(m_Indices.size()), 1, 0, 0, 0);
}

void Mesh::Update(GLFWwindow* window)
{
    Object::Update(window);

    AddPosition(m_Velocity * Time::GetInstance()->GetDeltaTime());
}

void Mesh::AddPosition(glm::vec3 addedPos)
{
    SetPosition(m_WorldPos + addedPos);
}

void Mesh::AddRotation(glm::vec3 addedRot)
{
    SetPosition(m_WorldPos + addedRot);
}

void Mesh::AddScale(glm::vec3 addedScale)
{
    SetPosition(m_WorldPos + addedScale);
}

void Mesh::SetPosition(glm::vec3 newPos)
{
    m_WorldPos = newPos;

    m_TranslationMatrix = glm::translate(glm::mat4{ 1.f }, { m_WorldPos.x, m_WorldPos.y, -m_WorldPos.z });

    NotifyObservers(GameEvents::ModelMatrixChanged);
}
void Mesh::SetRotation(glm::vec3 newRot)
{
    m_WorldRot = newRot;

    m_RotationMatrix = glm::rotate(glm::mat4{ 1.f }, m_WorldRot.z, glm::vec3{ 0.f, 0.f, 1.f })
        * glm::rotate(glm::mat4{ 1.f }, -m_WorldRot.y, glm::vec3{ 0.f, 1.f, 0.f })
        * glm::rotate(glm::mat4{ 1.f }, m_WorldRot.x, glm::vec3{ 1.f, 0.f, 0.f });

    NotifyObservers(GameEvents::ModelMatrixChanged);
}
void Mesh::SetScale(glm::vec3 newScale)
{
    m_WorldScale = newScale;

    m_ScaleMatrix = glm::scale(glm::mat4{ 1.f }, m_WorldScale);

    NotifyObservers(GameEvents::ModelMatrixChanged);
}


void Mesh::CalculateWorldMatrix()
{
    m_ModelMatrix = m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix;
}

