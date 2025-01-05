#pragma once

#include "Vulkanbase/Helperstructs/BaseComponent.h"
#include "PhysicsGame/Meshes/Mesh.h"

class NavMesh;

class MovingObjectComponent : public BaseComponent
{
public:

	MovingObjectComponent(Mesh* pParent, float triggerTime, glm::vec3 deltaLoc, NavMesh* navMesh) : BaseComponent(pParent), m_TriggerTime{ triggerTime }, m_DeltaLocation{ deltaLoc }, m_NavMesh{ navMesh } {}

	virtual void Update(GLFWwindow* window) override;
	virtual void GameStart() override;

	void SetTriggerTime(float triggerTime) { m_TriggerTime = triggerTime; }
	void SetTriggerDuration(float triggerDuration) { m_TriggerDuration = triggerDuration; }

private:

	bool m_HasMoved{ false };
	bool m_IsCurrentlyMoving{ false };

	glm::vec3 m_StartLocation{};
	glm::vec3 m_DeltaLocation{};

	float m_CurrentLifeTime{};

	float m_TriggerTime{};
	float m_TriggerDuration{ 3.f };

	NavMesh* m_NavMesh{};

	bool m_UpdateNavmeshEveryFrame{ false };
	bool m_UpdateNavmeshOnMovementCompleted{ true };
};