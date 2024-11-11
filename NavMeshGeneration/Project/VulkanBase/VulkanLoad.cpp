#include "vulkanbase/VulkanBase.h"

void VulkanBase::LoadScene()
{
	// Plane
	auto plane{ new Mesh("Resources/objs/Plane.obj", "Resources/texs/Ground/Plane_BaseColor.png", "", "")};
	plane->AddComponent(std::make_shared<CollisionComponent>(plane, true, 0));
	m_Scene->AddObject(plane);
	
	
	// Cubes
	auto cube01{ new Mesh("Resources/objs/cube.obj", "Resources/texs/gray.png", "", "", "", { -700, 0, 0 }, {0, 0, 0}, {0.5f, 6, 10})};
	auto cube02{ new Mesh("Resources/objs/cube.obj", "Resources/texs/gray.png", "", "", "", { -500, 0, 500 }, { 0, 0, 0 }, {5, 6, 0.5f}) };
	auto cube03{ new Mesh("Resources/objs/cube.obj", "Resources/texs/gray.png", "", "", "", { 0, 0, 0 }, { 0, 0, 0 }, {3, 2, 3}) };
	auto cube04{ new Mesh("Resources/objs/cube.obj", "Resources/texs/gray.png", "", "", "", { 700, 220, 300 }, { 0, 0, 0 }, {3, 0.5, 3}) };
	
	cube01->AddComponent(std::make_shared<CollisionComponent>(cube01, true, 0));
	cube02->AddComponent(std::make_shared<CollisionComponent>(cube02, true, 0));
	cube03->AddComponent(std::make_shared<CollisionComponent>(cube03, true, 0));
	cube04->AddComponent(std::make_shared<CollisionComponent>(cube04, true, 0));
	
	m_Scene->AddObject(cube01);
	m_Scene->AddObject(cube02);
	m_Scene->AddObject(cube03);
	m_Scene->AddObject(cube04);


	// Door
	auto doorBot{ new Mesh("Resources/objs/Door/Door.obj", "Resources/texs/Door/Door_Albedo.png", "Resources/texs/Door/Door_Metallic.png", "Resources/texs/Door/Door_Roughness.png", "Resources/texs/Door/Door_Normal.png", { -200, 200, 0 })};
	doorBot->AddComponent(std::make_shared<CollisionComponent>(doorBot, true, 0));

	m_Scene->AddObject(doorBot);

	// NavMesh
	//auto navMeshGenerator{ new NavMeshGenerator(m_Scene)};
	//auto pathFinder{ new PathFinder() };
	//auto navMesh{ new NavMesh(navMeshGenerator, pathFinder)};
	//
	//m_Scene->AddObject(navMeshGenerator);
	//m_Scene->AddObject(pathFinder);
	//m_Scene->AddObject(navMesh);
	//
	//m_NavMesh = navMesh;
	//m_NavMesh->GenerateNavMesh();
	//
	//m_NavMesh->GenerateRandomPath();
}

void VulkanBase::HandleInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && m_CanRepathNavMesh)
	{
		m_CanRepathNavMesh = false;
	
		m_NavMesh->GenerateRandomPath();

		FillVertexBuffer(m_NavMesh->GetVertices(), m_NavMesh->GetRenderID());
		FillIndexBuffer(m_NavMesh->GetIndices(), m_NavMesh->GetRenderID());
	}
	else if(glfwGetKey(window, GLFW_KEY_R) != GLFW_PRESS)
	{
		m_CanRepathNavMesh = true;
	}

}
