#include "NavMesh.h"
#include <chrono>
#include <numeric>

using namespace NavMeshStructs;

NavMesh::NavMesh(NavMeshGenerator* navMeshGenerator, PathFinder* pathFinder)
	: m_NavMeshGenerator{navMeshGenerator}
	, m_PathFinder{pathFinder}
{
}

void NavMesh::Update(GLFWwindow* window)
{
	if (m_IsNavMeshDirty)
	{
		m_IsNavMeshDirty = false;

		auto startTime{ std::chrono::high_resolution_clock::now() };

		if (m_DirtyAreas.empty())
		{
			GenerateNavMesh();
		}
		else
		{
			GenerateNavMeshLocally(m_DirtyAreas);
			m_DirtyAreas.clear();
		}

		float dt{ std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - startTime).count() };
		std::cout << "Time to Generate NavMesh: " << dt << "\n";
	}
}

std::vector<glm::vec3> NavMesh::GeneratePath(glm::vec3 startPoint, glm::vec3 endPoint)
{
	const Voxel* startVoxel{};
	const Voxel* endVoxel{};

	constexpr int maxIterations{ 15 };

	int currentIteration{};
	for (; currentIteration < maxIterations; ++currentIteration)
	{
		startVoxel = m_NavMeshGenerator->GetVoxelFromPosition(startPoint);
		if (!startVoxel) return {};

		if (startVoxel->type == NavMeshStructs::VoxelTypes::Walkable)
		{
			break;
		}

		if (startVoxel->type == NavMeshStructs::VoxelTypes::Solid)
		{
			startVoxel = nullptr;
			break;
		}

		startPoint.y -= m_NavMeshGenerator->GetVoxelSize().y;
	}
	if (currentIteration >= maxIterations) startVoxel = nullptr;

	currentIteration = 0;
	for (; currentIteration < maxIterations; ++currentIteration)
	{
		endVoxel = m_NavMeshGenerator->GetVoxelFromPosition(endPoint);
		if (!endVoxel) return {};

		if (endVoxel->type == NavMeshStructs::VoxelTypes::Walkable)
		{
			break;
		}

		if (endVoxel->type == NavMeshStructs::VoxelTypes::Solid)
		{
			endVoxel = nullptr;
			break;
		}

		endPoint.y -= m_NavMeshGenerator->GetVoxelSize().y;
	}
	if (currentIteration >= maxIterations) endVoxel = nullptr;
	
	//auto path{ m_PathFinder->GetPath(m_VoxelNodes, m_PathFinder->GetVoxelNodeFromVoxel(m_VoxelNodes, startVoxel), m_PathFinder->GetVoxelNodeFromVoxel(m_VoxelNodes, endVoxel))};
	auto path{ m_PathFinder->GetPath(m_NavMeshGenerator->GetVoxelNodes(), m_PathFinder->GetVoxelNodeFromVoxel(m_NavMeshGenerator->GetVoxelNodes(), startVoxel), m_PathFinder->GetVoxelNodeFromVoxel(m_NavMeshGenerator->GetVoxelNodes(), endVoxel))};
	FillVerticesAndIndices(path);

	std::vector<glm::vec3> vec3Path{};
	for (const auto& node : path)
	{
		vec3Path.emplace_back(node->bounds.GetMiddle());
	}

	return vec3Path;
}

void NavMesh::GenerateRandomPath()
{
	int randomStartIndex{ rand() % int(m_VoxelNodes.size()) };
	int randomEndIndex{ rand() % int(m_VoxelNodes.size()) };

	auto path{ m_PathFinder->GetPath(m_VoxelNodes, randomStartIndex, randomEndIndex) };

	if (path.size() == 0)
	{
		path.emplace_back(m_VoxelNodes[randomStartIndex].voxel);
		path.emplace_back(m_VoxelNodes[randomEndIndex].voxel);
	}

	FillVerticesAndIndices(path);
}
void NavMesh::GenerateRandomPathsTest(int amount)
{
	std::vector<float> times{};
	times.reserve(amount);

	for (int index{}; index < amount; ++index)
	{
		auto start = std::chrono::high_resolution_clock::now();

		GenerateRandomPath();

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration<float>(end - start).count();

		times.emplace_back(duration);
	}

	std::sort(times.begin(), times.end());
	times.erase(times.begin());
	times.pop_back();

	float total{ std::accumulate(times.begin(), times.end(), 0.f) };
	float average{ total / static_cast<float>(times.size()) };

	std::cout << "Average Time for Path generation: " << average << "\n";
}


void NavMesh::GenerateNavMesh()
{
	m_VoxelNodes = m_NavMeshGenerator->GenerateNavMesh();
	NotifyObservers(GameEvents::NavMeshChanged);
}

void NavMesh::GenerateNavMeshLocally(std::vector<AABB> areas)
{
	m_VoxelNodes = m_NavMeshGenerator->GenerateNavMeshLocally(m_DirtyAreas);
	NotifyObservers(GameEvents::NavMeshChanged);
}

void NavMesh::GenerateNavMeshesTest(int amount)
{
	std::vector<float> times{};
	times.reserve(amount);

	for (int index{}; index < amount; ++index)
	{
		auto start = std::chrono::high_resolution_clock::now();

		GenerateNavMesh();

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration<float>(end - start).count();

		times.emplace_back(duration);
	}

	std::sort(times.begin(), times.end());
	times.erase(times.begin());
	times.pop_back();

	float total{std::accumulate(times.begin(), times.end(), 0.f)};
	float average{ total / static_cast<float>(times.size()) };

	std::cout << "Average Time for NavMesh generation: " << average << "\n";
}

void NavMesh::SetNavMeshDirty(const AABB& area)
{
	m_IsNavMeshDirty = true;
	m_DirtyAreas.emplace_back(area);
}

void NavMesh::SetNavMeshDirty()
{
	m_IsNavMeshDirty = true;
}

void NavMesh::FillVerticesAndIndices(std::vector<const NavMeshStructs::Voxel*> path)
{
	m_Vertices.clear();
	m_Indices.clear();

	for (const auto& voxel : path)
	{
		size_t sizeBefore{ m_Vertices.size() };

		m_Vertices.emplace_back(Vertex{ {voxel->bounds.min.x, voxel->bounds.max.y + m_RenderHeightOffset, voxel->bounds.min.z} });
		m_Vertices.emplace_back(Vertex{ {voxel->bounds.min.x, voxel->bounds.max.y + m_RenderHeightOffset, voxel->bounds.max.z} });
		m_Vertices.emplace_back(Vertex{ {voxel->bounds.max.x, voxel->bounds.max.y + m_RenderHeightOffset, voxel->bounds.min.z} });
		m_Vertices.emplace_back(Vertex{ {voxel->bounds.max.x, voxel->bounds.max.y + m_RenderHeightOffset, voxel->bounds.max.z} });

		m_Indices.emplace_back(sizeBefore);
		m_Indices.emplace_back(sizeBefore + 1);
		m_Indices.emplace_back(sizeBefore + 2);

		m_Indices.emplace_back(sizeBefore + 1);
		m_Indices.emplace_back(sizeBefore + 2);
		m_Indices.emplace_back(sizeBefore + 3);
	}

	if (m_Vertices.size() == 0 || m_Indices.size() == 0)
	{
		m_Vertices = { {{0.f, 0.f, 0.f}} };
		m_Indices = { 0, 0, 0 };
	}
}