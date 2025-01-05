#include "AIMovementComponent.h"

#include "CollisionComponent.h"
#include "PhysicsGame/Collision/CollisionFixer.h"
#include "Vulkanbase/Scene/Scene.h"

#include <iostream>

void AIMovementComponent::Update(GLFWwindow* window)
{
	CalculateIsOnGround();
	HandleGravity();
	HandleAIMovement();

	GetOwner()->SetVelocity(m_Velocity * m_MoveSpeed);

	float angle{ glm::atan(m_Velocity.z / m_Velocity.x) + PI / 2.f };
	GetOwner()->SetRotation({ 0.f, angle, 0.f });
}

void AIMovementComponent::SetFollowPath(const std::vector<glm::vec3>& path)
{
	if (path.size() == 0) return;

	m_CurrentFollowPath = path;
	m_CurrentFollowPathIndex = 0;

	AIMoveTo(m_CurrentFollowPath[m_CurrentFollowPathIndex]);
}

void AIMovementComponent::AIMoveTo(glm::vec3 pos)
{
	glm::vec3 startPoint{ GetOwner()->GetWorldPosition() };
	startPoint.z *= -1;

	m_CurrentMoveToPath = m_NavMesh->GeneratePath(startPoint, pos);
	if (m_CurrentMoveToPath.size() == 0)
	{
		m_IsFollowingAIPath = false;
		return;
	}

	m_IsFollowingAIPath = true;
	m_CurrentMoveToPathIndex = 0;
}

void AIMovementComponent::HandleAIMovement()
{
	if (m_IsFollowingAIPath)
	{
		if (IsOnPoint(m_CurrentFollowPath[m_CurrentFollowPathIndex], 1.f))
		{
			m_CurrentFollowPathIndex = ++m_CurrentFollowPathIndex;
			if (m_CurrentFollowPathIndex >= m_CurrentFollowPath.size())
			{
				m_IsFollowingAIPath = false;
				return;
			}

			AIMoveTo(m_CurrentFollowPath[m_CurrentFollowPathIndex]);
		}
		else if(IsOnPoint(m_CurrentMoveToPath[m_CurrentMoveToPathIndex], 1.f))
		{
			++m_CurrentMoveToPathIndex;
			if (m_CurrentMoveToPathIndex >= m_CurrentMoveToPath.size())
			{
				m_CurrentFollowPathIndex = ++m_CurrentFollowPathIndex % m_CurrentFollowPath.size();
				AIMoveTo(m_CurrentFollowPath[m_CurrentFollowPathIndex]);
			}
		}
		if (!m_IsFollowingAIPath) return;
		
		glm::vec3 worldPos{ GetOwner()->GetWorldPosition() };
		worldPos.z *= -1;

		glm::vec3 newVelocity{ m_CurrentMoveToPath[m_CurrentMoveToPathIndex] - worldPos};
		glm::vec2 outVel{ glm::normalize(glm::vec2{newVelocity.x, -newVelocity.z}) };

		m_Velocity.x = outVel.x;
		m_Velocity.z = outVel.y;

	}
}

bool AIMovementComponent::IsOnPoint(glm::vec3 point, float range)
{
	glm::vec2 point2D{ point.x, point.z};
	glm::vec3 worldPos{ GetOwner()->GetWorldPosition() };
	glm::vec2 worldPos2D{ worldPos.x, -worldPos.z };

	return glm::length(point2D - worldPos2D) < range;
}

void AIMovementComponent::HandleGravity()
{
	if (!m_IsOnGround)
	{
		m_Velocity.y -= m_Gravity * Time::GetInstance()->GetDeltaTime();
	}
}

void AIMovementComponent::CalculateIsOnGround()
{
	auto meshes{ Scene::GetInstance()->GetObjects() };
	std::erase(meshes, GetOwner());

	auto collisionComp{ GetOwner()->GetComponent<CollisionComponent>() };
	if (!collisionComp) return;

	if (CollisionFixer::IsOnGround(collisionComp.get(), meshes))
	{
		m_IsOnGround = true;
		if (m_Velocity.y < 0)
			m_Velocity.y = 0.f;
	}
	else
	{
		m_IsOnGround = false;
	}
}
