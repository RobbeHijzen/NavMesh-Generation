#include "vulkanbase/VulkanBase.h"
#include "AI/NavMesh/NavMeshGenerator.h"

void VulkanBase::LoadScene()
{
	// Plane
	auto plane{ new Mesh("Resources/objs/Plane.obj", "Resources/texs/Plane_BaseColor.png") };
	plane->AddComponent(std::make_shared<CollisionComponent>(plane, true, 0));
	m_Scene->AddObject(plane);

	// Vehicle
	//auto vehicle{ new Mesh("Resources/objs/vehicle.obj", "Resources/texs/vehicle_diffuse.png", { -200, 82.f, 0 }, { 0, -90, 0 }) };
	//vehicle->AddComponent(std::make_shared<CollisionComponent>(vehicle, true, 3));
	//m_Scene->AddObject(vehicle);

	// Cubes

	auto cube01{ new Mesh("Resources/objs/cube.obj", "Resources/texs/null_BaseColor.png", { -700, 0, 0 }, { 0, 0, 0 }, {0.5f, 6, 10}) };
	auto cube02{ new Mesh("Resources/objs/cube.obj", "Resources/texs/null_BaseColor.png", { -500, 0, 500 }, { 0, 0, 0 }, {5, 6, 0.5f}) };
	auto cube03{ new Mesh("Resources/objs/cube.obj", "Resources/texs/null_BaseColor.png", { 0, 0, 0 }, { 0, 0, 0 }, {3, 2, 3}) };
	auto cube04{ new Mesh("Resources/objs/cube.obj", "Resources/texs/null_BaseColor.png", { 700, 220, 300 }, { 0, 0, 0 }, {3, 0.5, 3}) };
	
	cube01->AddComponent(std::make_shared<CollisionComponent>(cube01, true, 0));
	cube02->AddComponent(std::make_shared<CollisionComponent>(cube02, true, 0));
	cube03->AddComponent(std::make_shared<CollisionComponent>(cube03, true, 0));
	cube04->AddComponent(std::make_shared<CollisionComponent>(cube04, true, 0));

	m_Scene->AddObject(cube01);
	m_Scene->AddObject(cube02);
	m_Scene->AddObject(cube03);
	m_Scene->AddObject(cube04);

	// NavMesh
	auto navMeshGenerator{ new NavMeshGenerator(m_Scene)};
	m_Scene->AddObject(navMeshGenerator);
}

void VulkanBase::HandleToggleKeyboardPresses(GLFWwindow* window)
{
	//if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && m_CanToggleDrawOutlines)
	//{
	//	m_CanToggleDrawOutlines = false;
	//	m_DrawOutlines = !m_DrawOutlines;
	//
	//	for (auto& object : m_Scene->GetObjects())
	//	{
	//		if (auto col = object->GetComponent<CollisionComponent>())
	//		{
	//			col->SetHidden(!m_DrawOutlines);
	//		}
	//	}
	//}
	//else if(glfwGetKey(window, GLFW_KEY_E) != GLFW_PRESS)
	//{
	//	m_CanToggleDrawOutlines = true;
	//}

}
