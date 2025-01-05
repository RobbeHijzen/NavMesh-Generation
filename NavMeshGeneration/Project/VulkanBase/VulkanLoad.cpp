#include "vulkanbase/VulkanBase.h"

void VulkanBase::LoadScene()
{
	// NavMesh
	auto redMat{ m_Scene->CreateMaterial() };
	redMat->SetAlbedoString("Resources/texs/Red.png");
	redMat->SetOpacityString("Resources/texs/Gray_02.png");

	auto greenMat{ m_Scene->CreateMaterial() };
	greenMat->SetAlbedoString("Resources/texs/Green.png");
	greenMat->SetOpacityString("Resources/texs/Gray_02.png");


	auto navMeshGenerator{ new NavMeshGenerator(m_Scene) };
	auto pathFinder{ new PathFinder() };
	auto navMesh{ new NavMesh(navMeshGenerator, pathFinder) };

	navMeshGenerator->SetMaterial(greenMat);
	navMesh->SetMaterial(redMat);

	// Floor
	auto floorMat{ m_Scene->CreateMaterial() };
	floorMat->SetAlbedoString("Resources/texs/TrimTexture_Base/TrimTexture_Base_Albedo.png");
	floorMat->SetMetallicString("Resources/texs/TrimTexture_Base/TrimTexture_Base_Metallic.png");
	floorMat->SetRoughnessString("Resources/texs/TrimTexture_Base/TrimTexture_Base_Roughness.png");
	floorMat->SetNormalString("Resources/texs/TrimTexture_Base/TrimTexture_Base_Normal.png");

	auto tile{ new Mesh("Resources/objs/Floors/FloorTile_01.obj") };
	tile->SetMaterial(floorMat);
	tile->SetInstanceable(true);

	{
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, -900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, -900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, -900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, -900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, -900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, -900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -100.f, 0.f, -900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 0.f, 0.f,	  -900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 100.f, 0.f,  -900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 200.f, 0.f,  -900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  -900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  -900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  -900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  -900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  -900.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, -800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, -800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, -800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, -800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, -800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, -800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -100.f, 0.f, -800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 0.f, 0.f,	  -800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 100.f, 0.f,  -800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 200.f, 0.f,  -800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  -800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  -800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  -800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  -800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  -800.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, -700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, -700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, -700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, -700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, -700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, -700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -100.f, 0.f, -700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 0.f, 0.f,	  -700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 100.f, 0.f,  -700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 200.f, 0.f,  -700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  -700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  -700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  -700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  -700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  -700.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, -600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, -600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, -600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, -600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, -600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, -600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -100.f, 0.f, -600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 0.f, 0.f,	  -600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 100.f, 0.f,  -600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 200.f, 0.f,  -600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  -600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  -600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  -600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  -600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  -600.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, -500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, -500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, -500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, -500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, -500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, -500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -100.f, 0.f, -500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 0.f, 0.f,	  -500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 100.f, 0.f,  -500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 200.f, 0.f,  -500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  -500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  -500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  -500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  -500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  -500.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, -400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, -400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, -400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, -400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, -400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, -400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  -400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  -400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  -400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  -400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  -400.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, -300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, -300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, -300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, -300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, -300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, -300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  -300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  -300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  -300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  -300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  -300.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, -200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, -200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, -200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, -200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, -200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, -200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  -200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  -200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  -200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  -200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  -200.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, -100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, -100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, -100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, -100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, -100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, -100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  -100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  -100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  -100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  -100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  -100.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, 0.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, 0.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, 0.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, 0.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, 0.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, 0.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  0.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  0.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  0.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  0.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  0.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, 100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, 100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, 100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, 100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, 100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, 100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  100.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  100.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, 200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, 200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, 200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, 200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, 200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, 200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  200.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  200.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, 300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, 300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, 300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, 300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, 300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, 300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  300.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  300.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, 400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, 400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, 400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, 400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, 400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, 400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  400.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  400.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, 500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, 500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, 500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, 500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, 500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, 500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  500.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  500.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, 600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, 600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, 600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, 600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, 600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, 600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -100.f, 0.f, 600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 0.f, 0.f,	  600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 100.f, 0.f,  600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 200.f, 0.f,  600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  600.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  600.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, 700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, 700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, 700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, 700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, 700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, 700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -100.f, 0.f, 700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 0.f, 0.f,	  700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 100.f, 0.f,  700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 200.f, 0.f,  700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  700.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  700.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, 800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, 800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, 800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, 800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, 800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, 800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -100.f, 0.f, 800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 0.f, 0.f,	  800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 100.f, 0.f,  800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 200.f, 0.f,  800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  800.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  800.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, 900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, 900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, 900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, 900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, 900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, 900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -100.f, 0.f, 900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 0.f, 0.f,	  900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 100.f, 0.f,  900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 200.f, 0.f,  900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  900.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  900.f }));

		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -700.f, 0.f, 1000.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -600.f, 0.f, 1000.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -500.f, 0.f, 1000.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -400.f, 0.f, 1000.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -300.f, 0.f, 1000.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -200.f, 0.f, 1000.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { -100.f, 0.f, 1000.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 0.f, 0.f,	  1000.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 100.f, 0.f,  1000.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 200.f, 0.f,  1000.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 300.f, 0.f,  1000.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 400.f, 0.f,  1000.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 500.f, 0.f,  1000.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 600.f, 0.f,  1000.f }));
		tile->AddInstance(glm::translate(glm::mat4{ 1.f }, { 700.f, 0.f,  1000.f }));
	}

	auto col{ std::make_shared<CollisionComponent>(tile, true, 0) };
	col->SetAABBs({ AABB{{-750.f, 0, -950.f}, {700.f, 0, 1000.f}} });
	tile->AddComponent(col);
	m_Scene->AddObject(tile);

	// 5x5 Walls
	auto wallMat{ m_Scene->CreateMaterial() };
	wallMat->SetAlbedoString("Resources/texs/WallTile/WallTile_Albedo.png");
	wallMat->SetRoughnessString("Resources/texs/WallTile/WallTile_Roughness.png");
	wallMat->SetNormalString("Resources/texs/WallTile/WallTile_Normal.png");

	auto wallTile_01{ new Mesh("Resources/objs/Walls/WallTile_02_5x5.obj") };
	wallTile_01->SetMaterial(wallMat);
	wallTile_01->SetInstanceable(true);

	{
		wallTile_01->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 0.f, -250.f, 450.f }), 0.f, {0.f, 1.f, 0.f}));
		wallTile_01->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 0.f, -250.f, -550.f }), 0.f, { 0.f, 1.f, 0.f }));
		wallTile_01->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 150.f, -250.f, 250.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
		wallTile_01->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 150.f, -250.f, -250.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
		wallTile_01->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -250.f, -250.f, 250.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
		wallTile_01->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -250.f, -250.f, -250.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
		wallTile_01->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 0.f, -450.f, 250.f }), PI / 2.f, { 1.f, 0.f, 0.f }));
		wallTile_01->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 0.f, -450.f, -250.f }), PI / 2.f, { 1.f, 0.f, 0.f }));
	}

	m_Scene->AddObject(wallTile_01);

	auto wallTile_02{ new Mesh("Resources/objs/Walls/WallTile_02_5x5.obj") };
	wallTile_02->SetMaterial(wallMat);
	wallTile_02->SetInstanceable(true);

	{
		wallTile_02->AddInstance(glm::translate(glm::mat4{ 1.f }, { 450.f, -100.f, 950.f }));
		wallTile_02->AddInstance(glm::translate(glm::mat4{ 1.f }, { -50.f, -100.f, 950.f }));
		wallTile_02->AddInstance(glm::translate(glm::mat4{ 1.f }, { -550.f, -100.f, 950.f }));
		wallTile_02->AddInstance(glm::translate(glm::mat4{ 1.f }, { 450.f, 400.f, 950.f }));
		wallTile_02->AddInstance(glm::translate(glm::mat4{ 1.f }, { -50.f, 400.f, 950.f }));
		wallTile_02->AddInstance(glm::translate(glm::mat4{ 1.f }, { -550.f, 400.f, 950.f }));
	}

	m_Scene->AddObject(wallTile_02);

	// Pillars
	auto pillarMat{ m_Scene->CreateMaterial() };
	pillarMat->SetAlbedoString("Resources/texs/TrimTexture_01/TrimTexture_01_Albedo.png");
	pillarMat->SetRoughnessString("Resources/texs/TrimTexture_01/TrimTexture_01_Roughness.png");
	pillarMat->SetNormalString("Resources/texs/TrimTexture_01/TrimTexture_01_Normal.png");


	auto pillar_01{ new Mesh("Resources/objs/Pillars/Pillar_01.obj") };
	pillar_01->SetMaterial(pillarMat);
	pillar_01->SetPosition({-800.f, 0.f, -1000.f});
	pillar_01->SetRotation({0.f, PI / 2.f, 0.f});
	pillar_01->AddComponent(std::make_shared<CollisionComponent>(pillar_01, true, 0));

	auto pillar_02{ new Mesh("Resources/objs/Pillars/Pillar_01.obj") };
	pillar_02->SetMaterial(pillarMat);
	pillar_02->SetPosition({ -800.f, 0.f, -300.f });
	pillar_02->SetRotation({ 0.f, PI / 2.f, 0.f });
	pillar_02->AddComponent(std::make_shared<CollisionComponent>(pillar_02, true, 0));

	auto pillar_03{ new Mesh("Resources/objs/Pillars/Pillar_01.obj") };
	pillar_03->SetMaterial(pillarMat);
	pillar_03->SetPosition({ -800.f, 0.f, 300.f });
	pillar_03->SetRotation({ 0.f, PI / 2.f, 0.f });
	pillar_03->AddComponent(std::make_shared<CollisionComponent>(pillar_03, true, 0));

	auto pillar_04{ new Mesh("Resources/objs/Pillars/Pillar_01.obj") };
	pillar_04->SetMaterial(pillarMat);
	pillar_04->SetPosition({ -800.f, 0.f, 1000.f });
	pillar_04->SetRotation({ 0.f, PI / 2.f, 0.f });
	pillar_04->AddComponent(std::make_shared<CollisionComponent>(pillar_04, true, 0));

	m_Scene->AddObject(pillar_01);
	m_Scene->AddObject(pillar_02);
	m_Scene->AddObject(pillar_03);
	m_Scene->AddObject(pillar_04);

	// Side Ceiling
	auto ceilingMat{ m_Scene->CreateMaterial() };
	ceilingMat->SetAlbedoString("Resources/texs/TrimTexture_Detailed/TrimTexture_Detailed_Albedo.png");
	ceilingMat->SetMetallicString("Resources/texs/TrimTexture_Detailed/TrimTexture_Detailed_Metallic.png");
	ceilingMat->SetRoughnessString("Resources/texs/TrimTexture_Detailed/TrimTexture_Detailed_Roughness.png");
	ceilingMat->SetNormalString("Resources/texs/TrimTexture_Detailed/TrimTexture_Detailed_Normal.png");

	auto ceiling{ new Mesh("Resources/objs/Ceiling/Ceiling_Side.obj") };
	ceiling->SetMaterial(ceilingMat);
	ceiling->SetInstanceable(true);

	{
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -750.f, 475.f, 900.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f, {0.f, 0.f, -1.f}));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -750.f, 475.f, 700.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f, {0.f, 0.f, -1.f}));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -750.f, 475.f, 500.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f, {0.f, 0.f, -1.f}));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -750.f, 475.f, 300.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f, {0.f, 0.f, -1.f}));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -750.f, 475.f, 100.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f, {0.f, 0.f, -1.f}));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -750.f, 475.f, -100.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f,{0.f, 0.f, -1.f}));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -750.f, 475.f, -300.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f,{0.f, 0.f, -1.f}));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -750.f, 475.f, -500.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f,{0.f, 0.f, -1.f}));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -750.f, 475.f, -700.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f,{0.f, 0.f, -1.f}));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -750.f, 475.f, -900.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f,{0.f, 0.f, -1.f}));

		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -600.f, 625.f, 900.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f, { 0.f, 0.f, 1.f }));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -600.f, 625.f, 700.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f, { 0.f, 0.f, 1.f }));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -600.f, 625.f, 500.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f, { 0.f, 0.f, 1.f }));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -600.f, 625.f, 300.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f, { 0.f, 0.f, 1.f }));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -600.f, 625.f, 100.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f, { 0.f, 0.f, 1.f }));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -600.f, 625.f, -100.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f, { 0.f, 0.f, 1.f }));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -600.f, 625.f, -300.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f, { 0.f, 0.f, 1.f }));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -600.f, 625.f, -500.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f, { 0.f, 0.f, 1.f }));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -600.f, 625.f, -700.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f, { 0.f, 0.f, 1.f }));
		ceiling->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -600.f, 625.f, -900.f }), PI / 1.f, { 0.f, 1.f, 1.f }), PI / 2.f, { 0.f, 0.f, 1.f }));
	}
	auto col2{ std::make_shared<CollisionComponent>(ceiling, true, 0) };
	col2->SetAABBs({ AABB{{-600.f, 600.f, -1000.f}, {-500.f, 650.f, 1000.f}} });
	ceiling->AddComponent(col2);

	m_Scene->AddObject(ceiling);

	// Side Wall
	auto sideWallMat{ m_Scene->CreateMaterial() };
	sideWallMat->SetAlbedoString("Resources/texs/TrimTexture_Detailed/TrimTexture_Detailed_Albedo.png");
	sideWallMat->SetMetallicString("Resources/texs/TrimTexture_Detailed/TrimTexture_Detailed_Metallic.png");
	sideWallMat->SetRoughnessString("Resources/texs/TrimTexture_Detailed/TrimTexture_Detailed_Roughness.png");

	auto sideWall{ new Mesh("Resources/objs/Walls/Wall_Side.obj") };
	sideWall->SetMaterial(sideWallMat);
	sideWall->SetInstanceable(true);

	{
		sideWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 0.f, 850.f }) , PI / 2.f, { 0.f, 1.f, 0.f }));
		sideWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 0.f, 650.f }) , PI / 2.f, { 0.f, 1.f, 0.f }));
		sideWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 0.f, 450.f }) , PI / 2.f, { 0.f, 1.f, 0.f }));
		sideWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 0.f, 200.f }) , PI / 2.f, { 0.f, 1.f, 0.f }));
		sideWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 0.f, 0.f })   , PI / 2.f, { 0.f, 1.f, 0.f }));
		sideWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 0.f, -200.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
		sideWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 0.f, -450.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
		sideWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 0.f, -650.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
		sideWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 0.f, -850.f }), PI / 2.f, { 0.f, 1.f, 0.f }));

		sideWall->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 450.f, 850.f }) , PI / 2.f, { 0.f, -1.f, 0.f }), PI, {1.f, 0.f, 0.f}));
		sideWall->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 450.f, 650.f }) , PI / 2.f, { 0.f, -1.f, 0.f }), PI, {1.f, 0.f, 0.f}));
		sideWall->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 450.f, 450.f }) , PI / 2.f, { 0.f, -1.f, 0.f }), PI, {1.f, 0.f, 0.f}));
		sideWall->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 450.f, 200.f }) , PI / 2.f, { 0.f, -1.f, 0.f }), PI, {1.f, 0.f, 0.f}));
		sideWall->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 450.f, 0.f })   , PI / 2.f, { 0.f, -1.f, 0.f }), PI, {1.f, 0.f, 0.f}));
		sideWall->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 450.f, -200.f }), PI / 2.f, { 0.f, -1.f, 0.f }), PI, {1.f, 0.f, 0.f}));
		sideWall->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 450.f, -450.f }), PI / 2.f, { 0.f, -1.f, 0.f }), PI, {1.f, 0.f, 0.f}));
		sideWall->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 450.f, -650.f }), PI / 2.f, { 0.f, -1.f, 0.f }), PI, {1.f, 0.f, 0.f}));
		sideWall->AddInstance(glm::rotate(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -850.f, 450.f, -850.f }), PI / 2.f, { 0.f, -1.f, 0.f }), PI, {1.f, 0.f, 0.f}));
	}
	auto col3{ std::make_shared<CollisionComponent>(sideWall, true, 0) };
	col3->SetAABBs({ AABB{{-900.f, 0.f, -950.f}, {-800.f, 850.f, 950.f}} });
	sideWall->AddComponent(col3);

	m_Scene->AddObject(sideWall);

	// Wall
	auto concreteWallsMat{ m_Scene->CreateMaterial() };
	concreteWallsMat->SetAlbedoString("Resources/texs/TrimTexture_01/TrimTexture_01_Albedo.png");
	concreteWallsMat->SetRoughnessString("Resources/texs/TrimTexture_01/TrimTexture_01_Roughness.png");

	auto concreteWall{ new Mesh("Resources/objs/Walls/Wall_02.obj") };
	concreteWall->SetMaterial(concreteWallsMat);
	concreteWall->SetInstanceable(true);

	{
		concreteWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -905.f, 100.f, 950.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
		concreteWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -905.f, 100.f, 800.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
		concreteWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -905.f, 100.f, 650.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
		concreteWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -905.f, 100.f, 500.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
		concreteWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -905.f, 100.f, 350.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
		
		concreteWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -905.f, 100.f, 300.f }) , PI / 2.f, { 0.f, 1.f, 0.f }));
		concreteWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -905.f, 100.f, 150.f }) , PI / 2.f, { 0.f, 1.f, 0.f }));
		concreteWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -905.f, 100.f, 0.f })   , PI / 2.f, { 0.f, 1.f, 0.f }));
		concreteWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -905.f, 100.f, -150.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
		concreteWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -905.f, 100.f, -300.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
	
		concreteWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -905.f, 100.f, -350.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
		concreteWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -905.f, 100.f, -500.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
		concreteWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -905.f, 100.f, -650.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
		concreteWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -905.f, 100.f, -800.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
		concreteWall->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -905.f, 100.f, -950.f }), PI / 2.f, { 0.f, 1.f, 0.f }));
	}

	m_Scene->AddObject(concreteWall);

	// Slanted Ceiling
	auto slantedMat{ m_Scene->CreateMaterial() };
	slantedMat->SetAlbedoString("Resources/texs/TrimTexture_01/TrimTexture_01_Albedo.png");
	slantedMat->SetRoughnessString("Resources/texs/TrimTexture_01/TrimTexture_01_Roughness.png");
	slantedMat->SetNormalString("Resources/texs/TrimTexture_01/TrimTexture_01_Normal.png");

	auto slantedCeiling{ new Mesh("Resources/objs/Ceiling/Ceiling_SlantedSides.obj") };
	slantedCeiling->SetMaterial(slantedMat);
	slantedCeiling->SetInstanceable(true);

	{
		slantedCeiling->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -680.f, 487.f, 900.f }),  PI / 2.f, { 0.f, -1.f, 0.f }));
		slantedCeiling->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -680.f, 487.f, 700.f }),  PI / 2.f, { 0.f, -1.f, 0.f }));
		slantedCeiling->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -680.f, 487.f, 500.f }),  PI / 2.f, { 0.f, -1.f, 0.f }));
		slantedCeiling->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -680.f, 487.f, 300.f }),  PI / 2.f, { 0.f, -1.f, 0.f }));
		slantedCeiling->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -680.f, 487.f, 100.f }),  PI / 2.f, { 0.f, -1.f, 0.f }));
		slantedCeiling->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -680.f, 487.f, -100.f }), PI / 2.f, { 0.f, -1.f, 0.f }));
		slantedCeiling->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -680.f, 487.f, -300.f }), PI / 2.f, { 0.f, -1.f, 0.f }));
		slantedCeiling->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -680.f, 487.f, -500.f }), PI / 2.f, { 0.f, -1.f, 0.f }));
		slantedCeiling->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -680.f, 487.f, -700.f }), PI / 2.f, { 0.f, -1.f, 0.f }));
		slantedCeiling->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -680.f, 487.f, -900.f }), PI / 2.f, { 0.f, -1.f, 0.f }));
	}
	m_Scene->AddObject(slantedCeiling);

	// Desks

	// Desk Tables
	auto tableMat{ m_Scene->CreateMaterial() };
	tableMat->SetAlbedoString("Resources/texs/Table/Table_Albedo.png");
	tableMat->SetMetallicString("Resources/texs/Table/Table_Metallic.png");
	tableMat->SetRoughnessString("Resources/texs/Table/Table_Roughness.png");
	tableMat->SetNormalString("Resources/texs/Table/Table_Normal.png");


	auto deskTable_01{ new Mesh("Resources/objs/Tables/Table_Top_Big.obj") };
	deskTable_01->SetMaterial(tableMat);
	deskTable_01->SetPosition({ 250.f, 90.f, 0.f });
	deskTable_01->SetRotation({ 0.f, PI / 2.f, 0.f });
	deskTable_01->AddComponent(std::make_shared<CollisionComponent>(deskTable_01, true, 0));

	auto deskTable_02{ new Mesh("Resources/objs/Tables/Table_Top_Small.obj") };
	deskTable_02->SetMaterial(tableMat);
	deskTable_02->SetPosition({ 0.f, 90.f, -566.f });
	deskTable_02->SetRotation({ 0.f, PI, 0.f });
	deskTable_02->AddComponent(std::make_shared<CollisionComponent>(deskTable_02, true, 0));

	auto deskTable_03{ new Mesh("Resources/objs/Tables/Table_Top_Small.obj") };
	deskTable_03->SetMaterial(tableMat);
	deskTable_03->SetPosition({ -266.f, 90.f, -257.f });
	deskTable_03->SetRotation({ 0.f, -PI / 2.f, 0.f });
	deskTable_03->AddComponent(std::make_shared<CollisionComponent>(deskTable_03, true, 0));

	auto deskTable_04{ new Mesh("Resources/objs/Tables/Table_Top_Small.obj") };
	deskTable_04->SetMaterial(tableMat);
	deskTable_04->SetPosition({ -266.f, 90.f, 257.f });
	deskTable_04->SetRotation({ 0.f, -PI / 2.f, 0.f });
	deskTable_04->AddComponent(std::make_shared<CollisionComponent>(deskTable_04, true, 0));

	auto deskTable_05{ new Mesh("Resources/objs/Tables/Table_Top_Small.obj") };
	deskTable_05->SetMaterial(tableMat);
	deskTable_05->SetPosition({ 0.f, 90.f, 567.f });
	deskTable_05->SetRotation({ 0.f, 0.f, 0.f });
	deskTable_05->AddComponent(std::make_shared<CollisionComponent>(deskTable_05, true, 0));


	m_Scene->AddObject(deskTable_01);
	m_Scene->AddObject(deskTable_02);
	m_Scene->AddObject(deskTable_03);
	m_Scene->AddObject(deskTable_04);
	m_Scene->AddObject(deskTable_05);

	// Desk Feet
	auto deskFoot_01{ new Mesh("Resources/objs/Tables/Table_Foot.obj") };
	deskFoot_01->SetMaterial(ceilingMat);
	deskFoot_01->SetPosition({ 250.f, 0.f, 197.f });
	deskFoot_01->SetRotation({ 0.f, PI / 2.f, 0.f });
	deskFoot_01->AddComponent(std::make_shared<CollisionComponent>(deskFoot_01, true, 0));

	auto deskFoot_02{ new Mesh("Resources/objs/Tables/Table_Foot.obj") };
	deskFoot_02->SetMaterial(ceilingMat);
	deskFoot_02->SetPosition({ 250.f, 0.f, -188.f });
	deskFoot_02->SetRotation({ 0.f, PI / 2.f, 0.f });
	deskFoot_02->AddComponent(std::make_shared<CollisionComponent>(deskFoot_02, true, 0));

	auto deskFoot_03{ new Mesh("Resources/objs/Tables/Table_Foot.obj") };
	deskFoot_03->SetMaterial(ceilingMat);
	deskFoot_03->SetPosition({ 135.f, 0.f, -550.f });
	deskFoot_03->SetRotation({ 0.f, PI, 0.f });
	deskFoot_03->AddComponent(std::make_shared<CollisionComponent>(deskFoot_03, true, 0));

	auto deskFoot_04{ new Mesh("Resources/objs/Tables/Table_Foot.obj") };
	deskFoot_04->SetMaterial(ceilingMat);
	deskFoot_04->SetPosition({ -135.f, 0.f, -550.f });
	deskFoot_04->SetRotation({ 0.f, PI, 0.f });
	deskFoot_04->AddComponent(std::make_shared<CollisionComponent>(deskFoot_04, true, 0));

	auto deskFoot_05{ new Mesh("Resources/objs/Tables/Table_Foot.obj") };
	deskFoot_05->SetMaterial(ceilingMat);
	deskFoot_05->SetPosition({ -250.f, 0.f, -392.f });
	deskFoot_05->SetRotation({ 0.f, -PI / 2.f, 0.f });
	deskFoot_05->AddComponent(std::make_shared<CollisionComponent>(deskFoot_05, true, 0));

	auto deskFoot_06{ new Mesh("Resources/objs/Tables/Table_Foot.obj") };
	deskFoot_06->SetMaterial(ceilingMat);
	deskFoot_06->SetPosition({ -250.f, 0.f, -122.f });
	deskFoot_06->SetRotation({ 0.f, -PI / 2.f, 0.f });
	deskFoot_06->AddComponent(std::make_shared<CollisionComponent>(deskFoot_06, true, 0));

	auto deskFoot_07{ new Mesh("Resources/objs/Tables/Table_Foot.obj") };
	deskFoot_07->SetMaterial(ceilingMat);
	deskFoot_07->SetPosition({ -250.f, 0.f, 122.f });
	deskFoot_07->SetRotation({ 0.f, -PI / 2.f, 0.f });
	deskFoot_07->AddComponent(std::make_shared<CollisionComponent>(deskFoot_07, true, 0));

	auto deskFoot_08{ new Mesh("Resources/objs/Tables/Table_Foot.obj") };
	deskFoot_08->SetMaterial(ceilingMat);
	deskFoot_08->SetPosition({ -250.f, 0.f, 392.f });
	deskFoot_08->SetRotation({ 0.f, -PI / 2.f, 0.f });
	deskFoot_08->AddComponent(std::make_shared<CollisionComponent>(deskFoot_08, true, 0));

	auto deskFoot_09{ new Mesh("Resources/objs/Tables/Table_Foot.obj") };
	deskFoot_09->SetMaterial(ceilingMat);
	deskFoot_09->SetPosition({ -135.f, 0.f, 551.f });
	deskFoot_09->SetRotation({ 0.f, 0.f, 0.f });
	deskFoot_09->AddComponent(std::make_shared<CollisionComponent>(deskFoot_09, true, 0));

	auto deskFoot_10{ new Mesh("Resources/objs/Tables/Table_Foot.obj") };
	deskFoot_10->SetMaterial(ceilingMat);
	deskFoot_10->SetPosition({ 135.f, 0.f, 551.f });
	deskFoot_10->SetRotation({ 0.f, 0.f, 0.f });
	deskFoot_10->AddComponent(std::make_shared<CollisionComponent>(deskFoot_10, true, 0));



	m_Scene->AddObject(deskFoot_01);
	m_Scene->AddObject(deskFoot_02);
	m_Scene->AddObject(deskFoot_03);
	m_Scene->AddObject(deskFoot_04);
	m_Scene->AddObject(deskFoot_05);
	m_Scene->AddObject(deskFoot_06);
	m_Scene->AddObject(deskFoot_07);
	m_Scene->AddObject(deskFoot_08);
	m_Scene->AddObject(deskFoot_09);
	m_Scene->AddObject(deskFoot_10);

	// Desk Screens
	auto deskScreen_01{ new Mesh("Resources/objs/Tables/Table_Screen.obj") };
	deskScreen_01->SetMaterial(tableMat);
	deskScreen_01->SetPosition({ 250.f, 90.5f, 96.f });
	deskScreen_01->SetRotation({ 0.f, PI / 2.f, 0.f });
	deskScreen_01->AddComponent(std::make_shared<CollisionComponent>(deskScreen_01, true, 0));

	auto deskScreen_02{ new Mesh("Resources/objs/Tables/Table_Screen.obj") };
	deskScreen_02->SetMaterial(tableMat);
	deskScreen_02->SetPosition({ 250.f, 90.5f, -85.f });
	deskScreen_02->SetRotation({ 0.f, PI / 2.f, 0.f });
	deskScreen_02->AddComponent(std::make_shared<CollisionComponent>(deskScreen_02, true, 0));

	auto deskScreen_03{ new Mesh("Resources/objs/Tables/Table_Screen.obj") };
	deskScreen_03->SetMaterial(tableMat);
	deskScreen_03->SetPosition({ 0.f, 90.5f, -566.f });
	deskScreen_03->SetRotation({ 0.f, PI, 0.f });
	deskScreen_03->AddComponent(std::make_shared<CollisionComponent>(deskScreen_03, true, 0));

	auto deskScreen_04{ new Mesh("Resources/objs/Tables/Table_Screen.obj") };
	deskScreen_04->SetMaterial(tableMat);
	deskScreen_04->SetPosition({ -266.f, 90.5f, -259.f });
	deskScreen_04->SetRotation({ 0.f, -PI / 2.f, 0.f });
	deskScreen_04->AddComponent(std::make_shared<CollisionComponent>(deskScreen_04, true, 0));

	auto deskScreen_05{ new Mesh("Resources/objs/Tables/Table_Screen.obj") };
	deskScreen_05->SetMaterial(tableMat);
	deskScreen_05->SetPosition({ -266.f, 90.5f, 254.f });
	deskScreen_05->SetRotation({ 0.f, -PI / 2.f, 0.f });
	deskScreen_05->AddComponent(std::make_shared<CollisionComponent>(deskScreen_05, true, 0));

	auto deskScreen_06{ new Mesh("Resources/objs/Tables/Table_Screen.obj") };
	deskScreen_06->SetMaterial(tableMat);
	deskScreen_06->SetPosition({ 0.f, 90.5f, 567.f });
	deskScreen_06->SetRotation({ 0.f, 0.f, 0.f });
	deskScreen_06->AddComponent(std::make_shared<CollisionComponent>(deskScreen_06, true, 0));


	m_Scene->AddObject(deskScreen_01);
	m_Scene->AddObject(deskScreen_02);
	m_Scene->AddObject(deskScreen_03);
	m_Scene->AddObject(deskScreen_04);
	m_Scene->AddObject(deskScreen_05);
	m_Scene->AddObject(deskScreen_06);

	// Loot Boxes
	auto lootBoxMat{ m_Scene->CreateMaterial() };
	lootBoxMat->SetAlbedoString("Resources/texs/LootItems/LootItems_Albedo.png");
	lootBoxMat->SetMetallicString("Resources/texs/LootItems/LootItems_Metallic.png");
	lootBoxMat->SetRoughnessString("Resources/texs/LootItems/LootItems_Roughness.png");
	lootBoxMat->SetNormalString("Resources/texs/LootItems/LootItems_Normal.png");

	auto lootBox_04{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_04->SetPosition({ -272.f, 0.f, 526.f });
	lootBox_04->SetRotation({ 0, glm::radians(20.f), 0 });
	lootBox_04->SetMaterial(lootBoxMat);
	lootBox_04->AddComponent(std::make_shared<CollisionComponent>(lootBox_04, true, 0));

	auto lootBox_05{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_05->SetPosition({ 281.f, 0.f, -323.f });
	lootBox_05->SetRotation({ 0, glm::radians(-110.f), 0 });
	lootBox_05->SetMaterial(lootBoxMat);
	lootBox_05->AddComponent(std::make_shared<CollisionComponent>(lootBox_05, true, 0));

	auto lootBox_06{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_06->SetPosition({ 420.f, 0.f, -755.f });
	lootBox_06->SetRotation({ 0, glm::radians(-210.f), 0 });
	lootBox_06->SetMaterial(lootBoxMat);
	lootBox_06->AddComponent(std::make_shared<CollisionComponent>(lootBox_06, true, 0));
	lootBox_06->AddComponent(std::make_shared<MovingObjectComponent>(lootBox_06, 19.f, glm::vec3{ 0.f, -100.f, 0.f }, navMesh));

	auto lootBox_07{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_07->SetPosition({ 481.f, 0.f, -823.f });
	lootBox_07->SetRotation({ 0, glm::radians(-145.f), 0 });
	lootBox_07->SetMaterial(lootBoxMat);
	lootBox_07->AddComponent(std::make_shared<CollisionComponent>(lootBox_07, true, 0));
	lootBox_07->AddComponent(std::make_shared<MovingObjectComponent>(lootBox_07, 19.f, glm::vec3{ 0.f, -100.f, 0.f }, navMesh));

	auto lootBox_08{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_08->SetPosition({ 478.f, 0.f, 776.f });
	lootBox_08->SetRotation({ 0, glm::radians(20.f), 0 });
	lootBox_08->SetMaterial(lootBoxMat);
	lootBox_08->AddComponent(std::make_shared<CollisionComponent>(lootBox_08, true, 0));
	lootBox_08->AddComponent(std::make_shared<MovingObjectComponent>(lootBox_08, 32.f, glm::vec3{ 0.f, -100.f, 0.f }, navMesh));

	auto lootBox_01{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_01->SetPosition({ -679.f, 0.f, 859.f });
	lootBox_01->SetRotation({ 0, glm::radians(-80.f), 0 });
	lootBox_01->SetMaterial(lootBoxMat);
	lootBox_01->AddComponent(std::make_shared<CollisionComponent>(lootBox_01, true, 0));
	lootBox_01->AddComponent(std::make_shared<MovingObjectComponent>(lootBox_01, 40.5f, glm::vec3{ 0.f, -100.f, 0.f }, navMesh));

	auto lootBox_02{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_02->SetPosition({ -628.f, 0.f, 937.f });
	lootBox_02->SetRotation({ 0, glm::radians(-100.f), 0 });
	lootBox_02->SetMaterial(lootBoxMat);
	lootBox_02->AddComponent(std::make_shared<CollisionComponent>(lootBox_02, true, 0));
	lootBox_02->AddComponent(std::make_shared<MovingObjectComponent>(lootBox_02, 40.5f, glm::vec3{ 0.f, -100.f, 0.f }, navMesh));

	auto lootBox_03{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_03->SetPosition({ -664.f, 95.f, 911.f });
	lootBox_03->SetRotation({ 0, glm::radians(-115.f), 0 });
	lootBox_03->SetMaterial(lootBoxMat);
	lootBox_03->AddComponent(std::make_shared<CollisionComponent>(lootBox_03, true, 0));
	lootBox_03->AddComponent(std::make_shared<MovingObjectComponent>(lootBox_03, 40.5f, glm::vec3{ 0.f, -100.f, 0.f }, navMesh));


	m_Scene->AddObject(lootBox_01);
	m_Scene->AddObject(lootBox_02);
	m_Scene->AddObject(lootBox_03);
	m_Scene->AddObject(lootBox_04);
	m_Scene->AddObject(lootBox_05);
	m_Scene->AddObject(lootBox_06);
	m_Scene->AddObject(lootBox_07);
	m_Scene->AddObject(lootBox_08);


	auto lootBox_10{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_10->SetPosition({ -369.f, -100.f, -773.f });
	lootBox_10->SetRotation({ 0, glm::radians(-190.f), 0 });
	lootBox_10->SetMaterial(lootBoxMat);
	lootBox_10->AddComponent(std::make_shared<CollisionComponent>(lootBox_10, true, 0));
	lootBox_10->AddComponent(std::make_shared<MovingObjectComponent>(lootBox_10, 15.f, glm::vec3{ 0.f, 100.f, 0.f }, navMesh));

	auto lootBox_11{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_11->SetPosition({ -334.f, -100.f, -848.f });
	lootBox_11->SetRotation({ 0, glm::radians(-200.f), 0 });
	lootBox_11->SetMaterial(lootBoxMat);
	lootBox_11->AddComponent(std::make_shared<CollisionComponent>(lootBox_11, true, 0));
	lootBox_11->AddComponent(std::make_shared<MovingObjectComponent>(lootBox_11, 15.f, glm::vec3{ 0.f, 100.f, 0.f }, navMesh));

	auto lootBox_12{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_12->SetPosition({ -349.f, 0.f, -808.f });
	lootBox_12->SetRotation({ 0, glm::radians(-215.f), 0 });
	lootBox_12->SetMaterial(lootBoxMat);
	lootBox_12->AddComponent(std::make_shared<CollisionComponent>(lootBox_12, true, 0));
	lootBox_12->AddComponent(std::make_shared<MovingObjectComponent>(lootBox_12, 15.f, glm::vec3{ 0.f, 95.f, 0.f }, navMesh));

	auto lootBox_13{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_13->SetPosition({ 331.f, -100.f, -938.f });
	lootBox_13->SetRotation({ 0, glm::radians(-200.f), 0 });
	lootBox_13->SetMaterial(lootBoxMat);
	lootBox_13->AddComponent(std::make_shared<CollisionComponent>(lootBox_13, true, 0));
	lootBox_13->AddComponent(std::make_shared<MovingObjectComponent>(lootBox_13, 17.5f, glm::vec3{ 0.f, 100.f, 0.f }, navMesh));

	auto lootBox_14{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_14->SetPosition({ 638.f, -100.f, 66.f });
	lootBox_14->SetRotation({ 0, glm::radians(20.f), 0 });
	lootBox_14->SetMaterial(lootBoxMat);
	lootBox_14->AddComponent(std::make_shared<CollisionComponent>(lootBox_14, true, 0));
	lootBox_14->AddComponent(std::make_shared<MovingObjectComponent>(lootBox_14, 26.3f, glm::vec3{ 0.f, 100.f, 0.f }, navMesh));

	auto lootBox_15{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_15->SetPosition({ 548.f, -100.f, 76.f });
	lootBox_15->SetRotation({ 0, glm::radians(10.f), 0 });
	lootBox_15->SetMaterial(lootBoxMat);
	lootBox_15->AddComponent(std::make_shared<CollisionComponent>(lootBox_15, true, 0));
	lootBox_15->AddComponent(std::make_shared<MovingObjectComponent>(lootBox_15, 26.3f, glm::vec3{ 0.f, 100.f, 0.f }, navMesh));

	auto lootBox_16{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_16->SetPosition({ 463.f, -100.f, 76.f });
	lootBox_16->SetRotation({ 0, glm::radians(-10.f), 0 });
	lootBox_16->SetMaterial(lootBoxMat);
	lootBox_16->AddComponent(std::make_shared<CollisionComponent>(lootBox_16, true, 0));
	lootBox_16->AddComponent(std::make_shared<MovingObjectComponent>(lootBox_16, 26.3f, glm::vec3{ 0.f, 100.f, 0.f }, navMesh));

	auto lootBox_09{ new Mesh("Resources/objs/Misc/LootBox.obj") };
	lootBox_09->SetPosition({ -512.f, -100.f, 756.f });
	lootBox_09->SetRotation({ 0, glm::radians(-45.f), 0 });
	lootBox_09->SetMaterial(lootBoxMat);
	lootBox_09->AddComponent(std::make_shared<CollisionComponent>(lootBox_09, true, 0));
	lootBox_09->AddComponent(std::make_shared<MovingObjectComponent>(lootBox_09, 40.5f, glm::vec3{ 0.f, 100.f, 0.f }, navMesh));

	m_Scene->AddObject(lootBox_09);
	m_Scene->AddObject(lootBox_10);
	m_Scene->AddObject(lootBox_11);
	m_Scene->AddObject(lootBox_12);
	m_Scene->AddObject(lootBox_13);
	m_Scene->AddObject(lootBox_14);
	m_Scene->AddObject(lootBox_15);
	m_Scene->AddObject(lootBox_16);

	// Loot Cylinders

	
	// Batch 3
	auto CylindersBatch_03{ new Mesh("Resources/objs/Misc/LootCylinder.obj") };
	CylindersBatch_03->SetMaterial(lootBoxMat);
	CylindersBatch_03->SetInstanceable(true);

	{
		CylindersBatch_03->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -249.f, 0.f, -445.f }), glm::radians(0.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_03->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -283.f, 0.f, -437.f }), glm::radians(-20.f), {0.f, 1.f, 0.f}));
	}
	CylindersBatch_03->AddComponent(std::make_shared<CollisionComponent>(CylindersBatch_03, true, 0));

	// Batch 4
	auto CylindersBatch_04{ new Mesh("Resources/objs/Misc/LootCylinder.obj") };
	CylindersBatch_04->SetMaterial(lootBoxMat);
	CylindersBatch_04->SetInstanceable(true);

	{
		CylindersBatch_04->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 247.f, 0.f, -422.f }), glm::radians(-30.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_04->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 274.f, 0.f, -457.f }), glm::radians(15.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_04->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 240.f, 0.f, -470.f }), glm::radians(40.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_04->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 279.f, 0.f, -495.f }), glm::radians(10.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_04->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 247.f, 0.f, -513.f }), glm::radians(-15.f), { 0.f, 1.f, 0.f }));
	}
	CylindersBatch_04->AddComponent(std::make_shared<CollisionComponent>(CylindersBatch_04, true, 0));

	// Batch 5
	auto CylindersBatch_05{ new Mesh("Resources/objs/Misc/LootCylinder.obj") };
	CylindersBatch_05->SetMaterial(lootBoxMat);
	CylindersBatch_05->SetInstanceable(true);

	{
		CylindersBatch_05->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 246.f, 0.f, 259.f }), glm::radians(10.f), { 0.f, 1.f, 0.f }));
	}
	CylindersBatch_05->AddComponent(std::make_shared<CollisionComponent>(CylindersBatch_05, true, 0));

	// Batch 8
	auto CylindersBatch_08{ new Mesh("Resources/objs/Misc/LootCylinder.obj") };
	CylindersBatch_08->SetMaterial(lootBoxMat);
	CylindersBatch_08->SetInstanceable(true);

	{
		CylindersBatch_08->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -471.f, 0.f, 755.f }), glm::radians(20.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_08->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -433.f, 0.f, 769.f }), glm::radians(-35.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_08->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -462.f, 0.f, 795.f }), glm::radians(-15.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_08->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -514.f, 0.f, 775.f }), glm::radians(-55.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_08->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -508.f, 0.f, 736.f }), glm::radians(-75.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_08->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -546.f, 0.f, 750.f }), glm::radians(-20.f), { 0.f, 1.f, 0.f }));
	}
	CylindersBatch_08->AddComponent(std::make_shared<CollisionComponent>(CylindersBatch_08, true, 0));
	CylindersBatch_08->AddComponent(std::make_shared<MovingObjectComponent>(CylindersBatch_08, 15.f, glm::vec3{ 0.f, -100.f, 0.f }, navMesh));

	// Batch 6
	auto CylindersBatch_06{ new Mesh("Resources/objs/Misc/LootCylinder.obj") };
	CylindersBatch_06->SetMaterial(lootBoxMat);
	CylindersBatch_06->SetInstanceable(true);

	{
		CylindersBatch_06->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 520.f, 0.f, 778.f }), glm::radians(-30.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_06->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 485.f, 0.f, 749.f }), glm::radians(-5.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_06->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 466.f, 0.f, 710.f }), glm::radians(10.f), { 0.f, 1.f, 0.f }));
	}
	CylindersBatch_06->AddComponent(std::make_shared<CollisionComponent>(CylindersBatch_06, true, 0));
	CylindersBatch_06->AddComponent(std::make_shared<MovingObjectComponent>(CylindersBatch_06, 20.f, glm::vec3{ 0.f, -100.f, 0.f }, navMesh));

	// Batch 7
	auto CylindersBatch_07{ new Mesh("Resources/objs/Misc/LootCylinder.obj") };
	CylindersBatch_07->SetMaterial(lootBoxMat);
	CylindersBatch_07->SetInstanceable(true);

	{
		CylindersBatch_07->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -248.f, 0.f, 506.f }), glm::radians(-15.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_07->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -279.f, 0.f, 480.f }), glm::radians(40.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_07->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -284.f, 0.f, 520.f }), glm::radians(5.f), { 0.f, 1.f, 0.f }));
	}
	CylindersBatch_07->AddComponent(std::make_shared<CollisionComponent>(CylindersBatch_07, true, 0));

	// Batch 1
	auto CylindersBatch_01{ new Mesh("Resources/objs/Misc/LootCylinder.obj") };
	CylindersBatch_01->SetMaterial(lootBoxMat);
	CylindersBatch_01->SetInstanceable(true);

	{
		CylindersBatch_01->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -564.f, 0.f, -916.f }), glm::radians(15.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_01->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -559.f, 0.f, -959.f }), glm::radians(-25.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_01->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -519.f, 0.f, -969.f }), glm::radians(0.f), { 0.f, 1.f, 0.f }));
	}
	CylindersBatch_01->AddComponent(std::make_shared<CollisionComponent>(CylindersBatch_01, true, 0));
	CylindersBatch_01->AddComponent(std::make_shared<MovingObjectComponent>(CylindersBatch_01, 40.5f, glm::vec3{ 0.f, -100.f, 0.f }, navMesh));

	// Batch 2
	auto CylindersBatch_02{ new Mesh("Resources/objs/Misc/LootCylinder.obj") };
	CylindersBatch_02->SetMaterial(lootBoxMat);
	CylindersBatch_02->SetInstanceable(true);

	{
		CylindersBatch_02->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -638.f, 0.f, -798.f }), glm::radians(-30.f), { 0.f, 1.f, 0.f }));
	}
	CylindersBatch_02->AddComponent(std::make_shared<CollisionComponent>(CylindersBatch_02, true, 0));
	CylindersBatch_02->AddComponent(std::make_shared<MovingObjectComponent>(CylindersBatch_02, 40.5f, glm::vec3{ 0.f, -100.f, 0.f }, navMesh));


	m_Scene->AddObject(CylindersBatch_01);
	m_Scene->AddObject(CylindersBatch_02);
	m_Scene->AddObject(CylindersBatch_03);
	m_Scene->AddObject(CylindersBatch_04);
	m_Scene->AddObject(CylindersBatch_05);
	m_Scene->AddObject(CylindersBatch_06);
	m_Scene->AddObject(CylindersBatch_07);
	m_Scene->AddObject(CylindersBatch_08);


	// Batch 10
	auto CylindersBatch_10{ new Mesh("Resources/objs/Misc/LootCylinder.obj") };
	CylindersBatch_10->SetMaterial(lootBoxMat);
	CylindersBatch_10->SetInstanceable(true);

	{
		CylindersBatch_10->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -593.f, -100.f, 216.f }), glm::radians(-30.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_10->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -624.f, -100.f, 185.f }), glm::radians(55.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_10->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -628.f, -100.f, 226.f }), glm::radians(-15.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_10->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -659.f, -100.f, 200.f }), glm::radians(40.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_10->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -664.f, -100.f, 240.f }), glm::radians(5.f), { 0.f, 1.f, 0.f }));
	}
	CylindersBatch_10->AddComponent(std::make_shared<CollisionComponent>(CylindersBatch_10, true, 0));
	CylindersBatch_10->AddComponent(std::make_shared<MovingObjectComponent>(CylindersBatch_10, 6.5f, glm::vec3{ 0.f, 100.f, 0.f }, navMesh));

	// Batch 11
	auto CylindersBatch_11{ new Mesh("Resources/objs/Misc/LootCylinder.obj") };
	CylindersBatch_11->SetMaterial(lootBoxMat);
	CylindersBatch_11->SetInstanceable(true);

	{
		CylindersBatch_11->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 315.f, -100.f, 839.f }), glm::radians(-30.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_11->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 350.f, -100.f, 854.f }), glm::radians(40.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_11->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 320.f, -100.f, 879.f }), glm::radians(20.f), { 0.f, 1.f, 0.f }));
	}
	CylindersBatch_11->AddComponent(std::make_shared<CollisionComponent>(CylindersBatch_11, true, 0));
	CylindersBatch_11->AddComponent(std::make_shared<MovingObjectComponent>(CylindersBatch_11, 17.5f, glm::vec3{ 0.f, 100.f, 0.f }, navMesh));

	// Batch 12
	auto CylindersBatch_12{ new Mesh("Resources/objs/Misc/LootCylinder.obj") };
	CylindersBatch_12->SetMaterial(lootBoxMat);
	CylindersBatch_12->SetInstanceable(true);

	{
		CylindersBatch_12->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 526.f, -100.f, 515.f }), glm::radians(-45.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_12->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 546.f, -100.f, 485.f }), glm::radians(-85.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_12->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 561.f, -100.f, 525.f }), glm::radians(15.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_12->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 591.f, -100.f, 490.f }), glm::radians(-95.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_12->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { 601.f, -100.f, 525.f }), glm::radians(-20.f), { 0.f, 1.f, 0.f }));
	}
	CylindersBatch_12->AddComponent(std::make_shared<CollisionComponent>(CylindersBatch_12, true, 0));
	CylindersBatch_12->AddComponent(std::make_shared<MovingObjectComponent>(CylindersBatch_12, 20.5f, glm::vec3{ 0.f, 100.f, 0.f }, navMesh));

	// Batch 13
	auto CylindersBatch_13{ new Mesh("Resources/objs/Misc/LootCylinder.obj") };
	CylindersBatch_13->SetMaterial(lootBoxMat);
	CylindersBatch_13->SetInstanceable(true);

	{
		CylindersBatch_13->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -22.f, -100.f, -944.f }), glm::radians(-190.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_13->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -32.f, -100.f, -896.f }), glm::radians(-120.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_13->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -59.f, -100.f, -920.f }), glm::radians(-145.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_13->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -77.f, -100.f, -886.f }), glm::radians(-150.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_13->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -53.f, -100.f, -858.f }), glm::radians(-175.f), { 0.f, 1.f, 0.f }));
	}
	CylindersBatch_13->AddComponent(std::make_shared<CollisionComponent>(CylindersBatch_13, true, 0));
	CylindersBatch_13->AddComponent(std::make_shared<MovingObjectComponent>(CylindersBatch_13, 37.f, glm::vec3{ 0.f, 100.f, 0.f }, navMesh));

	// Batch 9
	auto CylindersBatch_09{ new Mesh("Resources/objs/Misc/LootCylinder.obj") };
	CylindersBatch_09->SetMaterial(lootBoxMat);
	CylindersBatch_09->SetInstanceable(true);

	{
		CylindersBatch_09->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -484.f, -100.f, -816.f }), glm::radians(15.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_09->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -504.f, -100.f, -856.f }), glm::radians(30.f), { 0.f, 1.f, 0.f }));
		CylindersBatch_09->AddInstance(glm::rotate(glm::translate(glm::mat4{ 1.f }, { -528.f, -100.f, -823.f }), glm::radians(-25.f), { 0.f, 1.f, 0.f }));
	}
	CylindersBatch_09->AddComponent(std::make_shared<CollisionComponent>(CylindersBatch_09, true, 0));
	CylindersBatch_09->AddComponent(std::make_shared<MovingObjectComponent>(CylindersBatch_09, 40.5f, glm::vec3{ 0.f, 100.f, 0.f }, navMesh));

	m_Scene->AddObject(CylindersBatch_09);
	m_Scene->AddObject(CylindersBatch_10);
	m_Scene->AddObject(CylindersBatch_11);
	m_Scene->AddObject(CylindersBatch_12);
	m_Scene->AddObject(CylindersBatch_13);

	// Hole Cover
	auto holeCoverMat{ m_Scene->CreateMaterial() };
	holeCoverMat->SetAlbedoString("Resources/texs/TrimTexture_02/TrimTexture_02_Albedo.png");
	holeCoverMat->SetRoughnessString("Resources/texs/TrimTexture_02/TrimTexture_02_Roughness.png");
	holeCoverMat->SetNormalString("Resources/texs/TrimTexture_02/TrimTexture_02_Normal.png");

	auto holeCover{ new Mesh("Resources/objs/Covers/Cover_02.obj") };
	holeCover->SetRotation({ 0, -PI / 2.f, 0 });
	holeCover->SetMaterial(holeCoverMat);
	holeCover->AddComponent(std::make_shared<CollisionComponent>(holeCover, true, 0));

	m_Scene->AddObject(holeCover);

	
	
	// Add Navmesh to scene

	m_Scene->AddObject(navMeshGenerator);
	m_Scene->AddObject(pathFinder);
	m_Scene->AddObject(navMesh);
	
	m_NavMesh = navMesh;
	m_NavMesh->GenerateNavMesh();
	

	// AI guy
	auto ai{ new Mesh("Resources/objs/Wall_e.obj") };
	ai->SetPosition({ 0.f, 0.f, 950.f });
	ai->SetScale({ 0.4f, 0.4f, 0.4f });

	ai->SetMaterial(m_Scene->CreateMaterial());
	
	auto aiCollision{ std::make_shared<CollisionComponent>(ai, false, 0, false) };
	aiCollision->SetAABBs({ AABB{{-25.f, 0.f, -25.f}, {25.f, 175.f, 25.f}} }, true);
	ai->AddComponent(aiCollision);
	
	auto aiMovementComp{ std::make_shared<AIMovementComponent>(ai, navMesh) };
	navMesh->AddObserver(new Observer(GameEvents::NavMeshChanged, [aiMovementComp]() {aiMovementComp->RecalculateCurrentPath(); }));
	
	std::vector<glm::vec3> path{ {-690.f, 0.f, -740.f}, {-570.f, 0.f, 800.f}, {650.f, 0.f, 800.f}, {650.f, 0.f, -800.f}, {-650.f, 0.f, -700.f} };
	aiMovementComp->SetFollowPath(path);
	
	ai->AddComponent(aiMovementComp);
	
	m_Scene->AddObject(ai);
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
