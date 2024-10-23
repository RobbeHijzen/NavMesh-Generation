#include "NavMesh.h"

NavMesh::NavMesh(NavMeshGenerator* navMeshGenerator, PathFinder* pathFinder)
	: m_NavMeshGenerator{navMeshGenerator}
	, m_PathFinder{pathFinder}
{
	m_VoxelNodes = navMeshGenerator->GenerateNavMesh();

	int randomStartIndex{rand() % int(m_VoxelNodes.size())};
	int randomEndIndex{rand() % int(m_VoxelNodes.size())};

	//FillVerticesAndIndices(m_PathFinder->GetPath(m_VoxelNodes, randomStartIndex, randomEndIndex));
	FillVerticesAndIndices(m_PathFinder->GetPath(m_VoxelNodes, 285, 6227));
}

void NavMesh::FillVerticesAndIndices(std::vector<const NavMeshStructs::Voxel*> path)
{
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
