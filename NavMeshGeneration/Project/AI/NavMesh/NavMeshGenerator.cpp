#include "NavMeshGenerator.h"
#include "PhysicsGame/Components/DerivedComponents/CollisionComponent.h"

NavMeshGenerator::NavMeshGenerator(Scene* scene)
	: m_Scene{scene}
{
	GenerateNavMesh();
}

std::vector<Node> NavMeshGenerator::GenerateNavMesh()
{
	InitializeHeightMap();
	FillHeightMap();
	FillVerticesAndIndices();

	return std::vector<Node>();
}

void NavMeshGenerator::InitializeHeightMap()
{
	m_HeightMap.resize(m_VoxelsAmount * m_VoxelsAmount);

	glm::vec2 min{ m_Boundaries.min.x, m_Boundaries.min.z };
	glm::vec2 max{ m_Boundaries.max.x, m_Boundaries.max.z };
	glm::vec2 size{max - min};
	glm::vec2 sizePerVoxel{size.x / m_VoxelsAmount, size.y / m_VoxelsAmount};

	for (int index{}; index < m_HeightMap.size(); ++index)
	{
		AABB2D bounds{};
		bounds.min.x = min.x + sizePerVoxel.x * (index % m_VoxelsAmount);
		bounds.min.y = min.y + sizePerVoxel.y * (index / m_VoxelsAmount);

		bounds.max.x = bounds.min.x + sizePerVoxel.x;
		bounds.max.y = bounds.min.y + sizePerVoxel.y;


		m_HeightMap[index].bounds = bounds;
	}
}

void NavMeshGenerator::FillHeightMap()
{
	for (auto& voxel : m_HeightMap)
	{
		for (const auto& object : m_Scene->GetObjects())
		{
			if (auto collision = object->GetComponent<CollisionComponent>())
			{
				if (!collision->HasStaticCollision()) continue;
		
				for (const auto& aabb : collision->GetAABBs())
				{
					if (voxel.currentHighestPoint < aabb.max.y)
					{
						if (voxel.bounds.AreColliding(aabb))
						{
		
							voxel.currentHighestPoint = aabb.max.y;
							voxel.intersectedAABB = voxel.bounds.IntersectionRegion(aabb);
						}
					}
				}
			}
		}
	}
}

void NavMeshGenerator::FillVerticesAndIndices()
{
	for (auto& voxel : m_HeightMap)
	{
		if (voxel.currentHighestPoint == -FLT_MAX) continue;

		size_t sizeBefore{ m_Vertices.size()};

		m_Vertices.emplace_back(Vertex{ {voxel.intersectedAABB.min.x, voxel.currentHighestPoint + m_RenderHeightOffset, voxel.intersectedAABB.min.y} });
		m_Vertices.emplace_back(Vertex{ {voxel.intersectedAABB.min.x, voxel.currentHighestPoint + m_RenderHeightOffset, voxel.intersectedAABB.max.y} });
		m_Vertices.emplace_back(Vertex{ {voxel.intersectedAABB.max.x, voxel.currentHighestPoint + m_RenderHeightOffset, voxel.intersectedAABB.min.y} });
		m_Vertices.emplace_back(Vertex{ {voxel.intersectedAABB.max.x, voxel.currentHighestPoint + m_RenderHeightOffset, voxel.intersectedAABB.max.y} });

		m_Indices.emplace_back(sizeBefore);
		m_Indices.emplace_back(sizeBefore + 1);
		m_Indices.emplace_back(sizeBefore + 2);

		m_Indices.emplace_back(sizeBefore + 1);
		m_Indices.emplace_back(sizeBefore + 2);
		m_Indices.emplace_back(sizeBefore + 3);
	}
}
