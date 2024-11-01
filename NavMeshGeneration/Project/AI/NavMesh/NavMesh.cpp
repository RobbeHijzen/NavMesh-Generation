#include "NavMesh.h"
#include <chrono>
#include <numeric>

NavMesh::NavMesh(NavMeshGenerator* navMeshGenerator, PathFinder* pathFinder)
	: m_NavMeshGenerator{navMeshGenerator}
	, m_PathFinder{pathFinder}
{
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
}
