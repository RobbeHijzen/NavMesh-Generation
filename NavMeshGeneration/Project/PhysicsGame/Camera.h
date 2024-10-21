#pragma once
#include <cassert>
#include "VulkanUtil/VulkanUtil.h"
#include "VulkanBase/Time/Time.h"

#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


struct Camera
{

	Camera(const glm::vec3& _origin, float _fovAngle, GLFWwindow* window) :
		origin{ _origin },
		fovAngle{ _fovAngle }
	{
		fov = glm::radians(fovAngle / 2.f);

		CalculateProjectionMatrix();


		double x, y;
		glfwGetCursorPos(window, &x, &y);
		m_LastMouseX = static_cast<int>(x);
		m_LastMouseY = static_cast<int>(y);
	}

	glm::vec3 origin;
	float fovAngle;
	float fov;
	
	glm::mat4 unitMatrix{ glm::mat4{1.f} };

	glm::vec3 forward{ 0.f, 0.f, 1.f };
	glm::vec3 up{ 0.f, 1.f, 0.f };
	glm::vec3 right{ 1.f, 0.f, 0.f };

	float totalPitch{ glm::radians(40.f) };
	float totalYaw{0.f};

	glm::mat4 invViewMatrix{};
	glm::mat4 viewMatrix{};

	glm::mat4 projectionMatrix{};

	const float nearDistance{ 0.1f };
	const float farDistance{ 100000.f };

	void CalculateViewMatrix()
	{
		const glm::mat4 finalRotation{   glm::rotate(unitMatrix, totalPitch, glm::vec3{1.f, 0.f, 0.f})
									    * glm::rotate(unitMatrix,  totalYaw, glm::vec3{0.f, 1.f, 0.f}) };
		const glm::mat4 finalTranslation{ glm::translate(unitMatrix, glm::vec3{-origin.x, -origin.y, origin.z} ) };

		auto inverseRot{glm::inverse(finalRotation)};
		glm::vec4 transformedForward = inverseRot * glm::vec4(0.f, 0.f, 1.f, 0.f);

		forward = glm::normalize(glm::vec3{ -transformedForward.x, -transformedForward.y, transformedForward.z });
		right = glm::normalize(glm::cross({ 0.f, 1.f, 0.f }, forward));
		up = glm::normalize(glm::cross(forward, right));

		viewMatrix = finalRotation * finalTranslation;
	}

	void CalculateProjectionMatrix()
	{
		float width{ WIDTH };
		float height{ HEIGHT };

		projectionMatrix = glm::perspective(fov, width / height, nearDistance, farDistance);
		projectionMatrix[1][1] *= -1;
	}


	void Update(GLFWwindow* window)
	{
		CalculateViewMatrix();
		HandleKeyboardInputs(window);
	}


	float m_PanSpeed{ 1.f / 180.f };
	int m_LastMouseY{};
	int m_LastMouseX{};
	float m_MoveSpeed{400.f};

	void HandleKeyboardInputs(GLFWwindow* window)
	{
		const float deltaTime = Time::GetInstance()->GetDeltaTime();

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			origin += m_MoveSpeed * deltaTime * forward;

		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			origin -= m_MoveSpeed * deltaTime * right;

		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			origin -= m_MoveSpeed * deltaTime * forward;

		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			origin += m_MoveSpeed * deltaTime * right;

		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			origin.y += m_MoveSpeed * deltaTime;

		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			origin.y -= m_MoveSpeed * deltaTime;

		}


		//Mouse Input

		double x, y;
		glfwGetCursorPos(window, &x, &y);
		int mouseX{ static_cast<int>(x) - m_LastMouseX };
		int mouseY{ static_cast<int>(y) - m_LastMouseY };
		m_LastMouseX = static_cast<int>(x);
		m_LastMouseY = static_cast<int>(y);

		totalYaw += mouseX * m_PanSpeed;
		totalPitch += mouseY * m_PanSpeed;
		
	}
};

