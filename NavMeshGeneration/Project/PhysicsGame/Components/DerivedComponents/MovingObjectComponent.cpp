#include "MovingObjectComponent.h"
#include "VulkanBase/Time/Time.h"
#include "AI/NavMesh/NavMesh.h"

void MovingObjectComponent::GameStart()
{
	m_CurrentLifeTime = 0.f;
}
void MovingObjectComponent::Update(GLFWwindow* window)
{
	if (m_HasMoved) return;

	float deltaTime{Time::GetInstance()->GetDeltaTime()};
	m_CurrentLifeTime += deltaTime;

	if (m_IsCurrentlyMoving)
	{
		if (m_UpdateNavmeshEveryFrame && m_NavMesh)
		{
			m_NavMesh->SetNavMeshDirty();
		}

		if (m_CurrentLifeTime >= m_TriggerDuration)
		{
			GetOwner()->SetPosition(m_StartLocation + m_DeltaLocation);
			m_HasMoved = true;

			if (m_UpdateNavmeshOnMovementCompleted && m_NavMesh)
			{
				m_NavMesh->SetNavMeshDirty();
			}
		}
		else
		{
			GetOwner()->AddPosition((m_DeltaLocation / m_TriggerDuration) * deltaTime);
		}
		return;
	}

	if (m_CurrentLifeTime >= m_TriggerTime)
	{
		m_IsCurrentlyMoving = true;
		m_CurrentLifeTime = 0.f;
		m_StartLocation = GetOwner()->GetWorldPosition();
	}
}

