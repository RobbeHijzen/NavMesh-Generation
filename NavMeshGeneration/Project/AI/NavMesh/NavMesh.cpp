#include "NavMesh.h"

NavMesh::NavMesh(NavMeshGenerator* navMeshGenerator, PathFinder* pathFinder)
	: m_NavMeshGenerator{navMeshGenerator}
	, m_PathFinder{pathFinder}
{
	m_VoxelNodes = navMeshGenerator->GenerateNavMesh();

	GenerateRandomPath();
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
