#include "vulkanbase/VulkanBase.h"

void VulkanBase::LoadScene()
{
	// Door
	auto door{ new Mesh("Resources/objs/Door/Door.obj", "Resources/texs/Door/Door_Albedo.png", "Resources/texs/Door/Door_Metallic.png", "Resources/texs/Door/Door_Roughness.png", "Resources/texs/Door/Door_Normal.png", { -200, 200, 0 }, {0, -45, 0}) };
	door->AddComponent(std::make_shared<CollisionComponent>(door, true, 0));

	m_Scene->AddObject(door);

	// Table
	auto table{ new Mesh("Resources/objs/Table/Table.obj", "Resources/texs/Table/Table_Albedo.png", "Resources/texs/Table/Table_Metallic.png", "Resources/texs/Table/Table_Roughness.png", "Resources/texs/Table/Table_Normal.png", { 200, 200, 0 }, {0, 180, 0}) };
	table->AddComponent(std::make_shared<CollisionComponent>(table, true, 0));

	m_Scene->AddObject(table);

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
