#include "vulkanbase/VulkanBase.h"

void SpawnFloorTile(glm::vec3 location, glm::vec3 rotation, Scene* scene, Material* material);

void VulkanBase::LoadScene()
{
	// Door
	auto door{ new Mesh("Resources/objs/Doors/Door.obj") };
	door->SetPosition({ -500, 0, 0 });
	door->SetRotation({ 0, -PI / 2.f, 0 });

	auto doorMat{m_Scene->CreateMaterial()};
	doorMat->SetAlbedoString("Resources/texs/Door/Door_Albedo.png");
	doorMat->SetMetallicString("Resources/texs/Door/Door_Metallic.png");
	doorMat->SetRoughnessString("Resources/texs/Door/Door_Roughness.png");
	doorMat->SetNormalString("Resources/texs/Door/Door_Normal.png");

	door->SetMaterial(doorMat);

	door->AddComponent(std::make_shared<CollisionComponent>(door, true, 0));
	m_Scene->AddObject(door);

	// Floor
	int floorTilesPerRow{ 15 };

	auto floorMat{ m_Scene->CreateMaterial() };
	floorMat->SetAlbedoString("Resources/texs/TrimTexture_Base/TrimTexture_Base_Albedo.png");
	floorMat->SetMetallicString("Resources/texs/TrimTexture_Base/TrimTexture_Base_Metallic.png");
	floorMat->SetRoughnessString("Resources/texs/TrimTexture_Base/TrimTexture_Base_Roughness.png");
	floorMat->SetNormalString("Resources/texs/TrimTexture_Base/TrimTexture_Base_Normal.png");

	for (int index{}; index < floorTilesPerRow * floorTilesPerRow; ++index)
	{
		glm::vec3 loc{};
		loc.x = (-100 * floorTilesPerRow / 2.f) + 100.f * int(index / floorTilesPerRow);
		loc.z = (-100 * floorTilesPerRow / 2.f) + 100.f * int(index % floorTilesPerRow);
	
		SpawnFloorTile(loc, {}, m_Scene, floorMat);
	}

	// Loot Boxes
	auto lootBoxMat{ m_Scene->CreateMaterial() };
	lootBoxMat->SetAlbedoString("Resources/texs/LootItems/LootItems_Albedo.png");
	lootBoxMat->SetMetallicString("Resources/texs/LootItems/LootItems_Metallic.png");
	lootBoxMat->SetRoughnessString("Resources/texs/LootItems/LootItems_Roughness.png");
	lootBoxMat->SetNormalString("Resources/texs/LootItems/LootItems_Normal.png");

	auto lootBox_01{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_01->SetPosition({ 100.f, 0.f, 150.f });
	lootBox_01->SetRotation({ 0, -PI / 2.7f, 0 });

	lootBox_01->SetMaterial(lootBoxMat);
	
	lootBox_01->AddComponent(std::make_shared<CollisionComponent>(lootBox_01, true, 2));
	m_Scene->AddObject(lootBox_01);

	auto lootBox_02{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_02->SetPosition({ -130.f, 0.f, -60.f });
	lootBox_02->SetRotation({ 0, -PI / 1.4f, 0 });

	lootBox_02->SetMaterial(lootBoxMat);

	lootBox_02->AddComponent(std::make_shared<CollisionComponent>(lootBox_02, true, 2));
	m_Scene->AddObject(lootBox_02);

	
	// NavMesh
	auto redMat{ m_Scene->CreateMaterial() };
	redMat->SetAlbedoString("Resources/texs/Red.png");
	redMat->SetOpacityString("Resources/texs/Gray_02.png");

	auto greenMat{ m_Scene->CreateMaterial() };
	greenMat->SetAlbedoString("Resources/texs/Green.png");
	greenMat->SetOpacityString("Resources/texs/Gray_02.png");


	auto navMeshGenerator{ new NavMeshGenerator(m_Scene)};
	auto pathFinder{ new PathFinder() };
	auto navMesh{ new NavMesh(navMeshGenerator, pathFinder)};
	
	navMeshGenerator->SetMaterial(greenMat);
	navMesh->SetMaterial(redMat);

	m_Scene->AddObject(navMeshGenerator);
	m_Scene->AddObject(pathFinder);
	m_Scene->AddObject(navMesh);
	
	m_NavMesh = navMesh;
	m_NavMesh->GenerateNavMesh();
	

	// AI guy
	auto ai{ new Mesh("Resources/objs/cube.obj") };
	ai->SetPosition({ 0.f, 50.f, 0.f });
	ai->SetScale({ 0.1f, 1.f, 0.1f });

	ai->SetMaterial(doorMat);
	
	ai->AddComponent(std::make_shared<CollisionComponent>(ai, false, 0));
	
	auto aiMovementComp{ std::make_shared<AIMovementComponent>(ai, navMesh) };
	
	std::vector<glm::vec3> path{ {-500.f, 0.f, -500.f}, {-500.f, 0.f, 500.f}, {500.f, 0.f, -500.f}, {500.f, 0.f, 500.f} };
	aiMovementComp->SetFollowPath(path);
	
	ai->AddComponent(aiMovementComp);
	
	m_Scene->AddObject(ai);
}
void SpawnFloorTile(glm::vec3 location, glm::vec3 rotation, Scene* scene, Material* material)
{
	auto tile{ new Mesh("Resources/objs/Floors/FloorTile_01.obj") };
	tile->SetPosition(location);
	tile->SetRotation(rotation);

	tile->SetMaterial(material);

	tile->AddComponent(std::make_shared<CollisionComponent>(tile, true, 0));
	scene->AddObject(tile);
}


void VulkanBase::HandleInput(GLFWwindow* window)
{
	//if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && m_CanRepathNavMesh)
	//{
	//	m_CanRepathNavMesh = false;
	//
	//	m_NavMesh->GenerateRandomPath();
	//
	//	FillVertexBuffer(m_NavMesh->GetVertices(), m_NavMesh->GetRenderID());
	//	FillIndexBuffer(m_NavMesh->GetIndices(), m_NavMesh->GetRenderID());
	//}
	//else if(glfwGetKey(window, GLFW_KEY_R) != GLFW_PRESS)
	//{
	//	m_CanRepathNavMesh = true;
	//}

}
