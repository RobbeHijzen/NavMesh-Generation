#include "MovingObjectComponent.h"
#include "VulkanBase/Time/Time.h"
#include "AI/NavMesh/NavMesh.h"
#include "CollisionComponent.h"

void MovingObjectComponent::GameStart()
{
	m_CurrentLifeTime = 0.f;
	m_CollisionComp = GetOwner()->GetComponent<CollisionComponent>().get();
	m_LastNavMeshUpdateAreas = m_CollisionComp->GetAABBs();
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
			if (m_UpdateNavmeshLocally)
			{
				std::vector<AABB> currentAABB{ m_CollisionComp->GetAABBs() };

				if (currentAABB.size() == m_LastNavMeshUpdateAreas.size())
				{
					for (int index{}; index < currentAABB.size(); ++index)
					{
						m_NavMesh->SetNavMeshDirty(currentAABB[index].Merge(m_LastNavMeshUpdateAreas[index]));
					}
				}

				m_LastNavMeshUpdateAreas = currentAABB;
			}
			else
			{
				m_NavMesh->SetNavMeshDirty();
			}
		}

		if (m_CurrentLifeTime >= m_TriggerDuration)
		{
			GetOwner()->SetPosition(m_StartLocation + m_DeltaLocation);
			m_HasMoved = true;

			if (m_UpdateNavmeshOnMovementCompleted && m_NavMesh)
			{
				if (m_UpdateNavmeshLocally)
				{
					std::vector<AABB> currentAABB{ m_CollisionComp->GetAABBs() };

					if (currentAABB.size() == m_LastNavMeshUpdateAreas.size())
					{
						for (int index{}; index < currentAABB.size(); ++index)
						{
							m_NavMesh->SetNavMeshDirty(currentAABB[index].Merge(m_LastNavMeshUpdateAreas[index]));
						}
					}

					m_LastNavMeshUpdateAreas = currentAABB;
				}
				else
				{
					m_NavMesh->SetNavMeshDirty();
				}
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

