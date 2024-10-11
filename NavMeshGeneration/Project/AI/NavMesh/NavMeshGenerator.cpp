#include "NavMeshGenerator.h"
#include "PhysicsGame/Components/DerivedComponents/CollisionComponent.h"

NavMeshGenerator::NavMeshGenerator(Scene* scene)
	: m_Scene{scene}
{
	GenerateNavMesh();
}

std::vector<Node> NavMeshGenerator::GenerateNavMesh()
{
	InitializeVoxels();
	CheckForVoxelCollisions();
	FillVerticesAndIndices();

	return std::vector<Node>();
}

void NavMeshGenerator::InitializeVoxels()
{
	m_Voxels.resize(m_VoxelsAmountX);

	glm::vec3 min{ m_Boundaries.min.x, m_Boundaries.min.y, m_Boundaries.min.z };
	glm::vec3 max{ m_Boundaries.max.x, m_Boundaries.max.y, m_Boundaries.max.z };
	glm::vec3 size{max - min};
	glm::vec3 sizePerVoxel{size.x / m_VoxelsAmountX, size.y / m_VoxelsAmountY, size.z / m_VoxelsAmountZ };

	for (int x{}; x < m_Voxels.size(); ++x)
	{
		m_Voxels[x].resize(m_VoxelsAmountY);
		for (int y{}; y < m_Voxels[x].size(); ++y)
		{
			m_Voxels[x][y].resize(m_VoxelsAmountZ);
			for (int z{}; z < m_Voxels[x][y].size(); ++z)
			{
				Voxel result{};

				result.bounds.min.x = min.x + sizePerVoxel.x * x;
				result.bounds.min.y = min.y + sizePerVoxel.y * y;
				result.bounds.min.z = min.z + sizePerVoxel.z * z;

				result.bounds.max.x = result.bounds.min.x + sizePerVoxel.x;
				result.bounds.max.y = result.bounds.min.y + sizePerVoxel.y;
				result.bounds.max.z = result.bounds.min.z + sizePerVoxel.z;

				m_Voxels[x][y][z] = result;
			}
		}
	}


	//for (int index{}; index < m_HeightMap.size(); ++index)
	//{
	//	AABB2D bounds{};
	//	bounds.min.x = min.x + sizePerVoxel.x * (index % m_VoxelsAmount);
	//	bounds.min.y = min.y + sizePerVoxel.y * (index / m_VoxelsAmount);
	//
	//	bounds.max.x = bounds.min.x + sizePerVoxel.x;
	//	bounds.max.y = bounds.min.y + sizePerVoxel.y;
	//
	//
	//	m_HeightMap[index].bounds = bounds;
	//}
}

void NavMeshGenerator::CheckForVoxelCollisions()
{
	for (auto& xAxis : m_Voxels)
	{
		for (auto& yAxis : xAxis)
		{
			for (auto& voxel : yAxis)
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
									voxel.isSolid = true;
								}
							}
						}
					}
				}

			}
		}

	}
}

void NavMeshGenerator::FillVerticesAndIndices()
{
	for (const auto& xAxis : m_Voxels)
	{
		for (const auto& yAxis : xAxis)
		{
			for (const auto& voxel : yAxis)
			{
				if (voxel.isSolid)
				{
					size_t sizeBefore{ m_Vertices.size() };

					//m_Vertices.emplace_back(Vertex{ {voxel.intersectedAABB.min.x, voxel.currentHighestPoint + m_RenderHeightOffset, voxel.intersectedAABB.min.y} });
					//m_Vertices.emplace_back(Vertex{ {voxel.intersectedAABB.min.x, voxel.currentHighestPoint + m_RenderHeightOffset, voxel.intersectedAABB.max.y} });
					//m_Vertices.emplace_back(Vertex{ {voxel.intersectedAABB.max.x, voxel.currentHighestPoint + m_RenderHeightOffset, voxel.intersectedAABB.min.y} });
					//m_Vertices.emplace_back(Vertex{ {voxel.intersectedAABB.max.x, voxel.currentHighestPoint + m_RenderHeightOffset, voxel.intersectedAABB.max.y} });

					m_Vertices.emplace_back(Vertex{ {voxel.bounds.min.x, voxel.currentHighestPoint + m_RenderHeightOffset, voxel.bounds.min.z} });
					m_Vertices.emplace_back(Vertex{ {voxel.bounds.min.x, voxel.currentHighestPoint + m_RenderHeightOffset, voxel.bounds.max.z} });
					m_Vertices.emplace_back(Vertex{ {voxel.bounds.max.x, voxel.currentHighestPoint + m_RenderHeightOffset, voxel.bounds.min.z} });
					m_Vertices.emplace_back(Vertex{ {voxel.bounds.max.x, voxel.currentHighestPoint + m_RenderHeightOffset, voxel.bounds.max.z} });

					m_Indices.emplace_back(sizeBefore);
					m_Indices.emplace_back(sizeBefore + 1);
					m_Indices.emplace_back(sizeBefore + 2);

					m_Indices.emplace_back(sizeBefore + 1);
					m_Indices.emplace_back(sizeBefore + 2);
					m_Indices.emplace_back(sizeBefore + 3);
				}
			}
		}
		
	}
}
