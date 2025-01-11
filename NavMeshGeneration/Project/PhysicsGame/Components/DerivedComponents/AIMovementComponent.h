#pragma once

#include "Vulkanbase/Helperstructs/BaseComponent.h"
#include "PhysicsGame/Meshes/Mesh.h"
#include "AI/NavMesh/NavMesh.h"

class AIMovementComponent : public BaseComponent
{
public:

	AIMovementComponent(Mesh* pParent, NavMesh* navMesh) : BaseComponent(pParent), m_NavMesh{navMesh} {}
	virtual void Update(GLFWwindow* window) override;

	void SetFollowPath(const std::vector<glm::vec3>& path);

	void AIMoveTo(glm::vec3 pos);

	void RecalculateCurrentPath();

private:

	NavMesh* m_NavMesh{};

	bool m_IsFollowingAIPath{ false };
	std::vector<glm::vec3> m_CurrentFollowPath{};
	std::vector<glm::vec3> m_CurrentMoveToPath{};

	int m_CurrentFollowPathIndex{};
	int m_CurrentMoveToPathIndex{};

	glm::vec3 m_CurrentPathPoint{};

	void HandleAIMovement();
	bool IsOnPoint(glm::vec3 point, float range = 25.f);

	glm::vec3 m_Velocity{};
	const float m_MoveSpeed{ 150.f };

	float m_Gravity{ 0.f };

	bool m_IsOnGround{ true };

	void HandleGravity();
	void CalculateIsOnGround();

	int m_FrameCount{};
	float m_LifeTime{};
};