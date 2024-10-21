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
	FillHeightMap();

	FillVerticesAndIndices();
	//FillModelMatrices();

	return std::vector<Node>();
}

void NavMeshGenerator::InitializeVoxels()
{
	m_Voxels.resize(m_VoxelsAmountX * m_VoxelsAmountY * m_VoxelsAmountZ);

	glm::vec3 min{ m_Boundaries.min.x, m_Boundaries.min.y, m_Boundaries.min.z };
	glm::vec3 max{ m_Boundaries.max.x, m_Boundaries.max.y, m_Boundaries.max.z };
	glm::vec3 size{max - min};
	glm::vec3 sizePerVoxel{size.x / m_VoxelsAmountX, size.y / m_VoxelsAmountY, size.z / m_VoxelsAmountZ };

	for (int index{}; index < m_Voxels.size(); ++index)
	{
		Voxel result{};

		result.bounds.min.y = min.y + sizePerVoxel.y * (index % m_VoxelsAmountY);
		result.bounds.min.z = min.z + sizePerVoxel.z * ((index % (m_VoxelsAmountY * m_VoxelsAmountZ)) / m_VoxelsAmountY);
		result.bounds.min.x = min.x + sizePerVoxel.x * (index / (m_VoxelsAmountY * m_VoxelsAmountZ));

		result.bounds.max.y = result.bounds.min.y + sizePerVoxel.y;
		result.bounds.max.x = result.bounds.min.x + sizePerVoxel.x;
		result.bounds.max.z = result.bounds.min.z + sizePerVoxel.z;

		m_Voxels[index] = result;
	}
}

void NavMeshGenerator::CheckForVoxelCollisions()
{
	
	for (const auto& object : m_Scene->GetObjects())
	{
		if (auto collision = object->GetComponent<CollisionComponent>())
		{
			if (!collision->HasStaticCollision()) continue;

			for (const auto& aabb : collision->GetAABBs())
			{
				for (auto& voxel : m_Voxels)
				{
					if (voxel.type == VoxelTypes::Solid) continue;

					if (voxel.bounds.AreColliding(aabb))
					{
						voxel.type = VoxelTypes::Solid;
					}
				}
			}
		}
	}
}

void NavMeshGenerator::FillHeightMap()
{
	m_HeightMap.reserve(m_VoxelsAmountX * m_VoxelsAmountZ);

	for (int index{}; index < m_VoxelsAmountX * m_VoxelsAmountZ; ++index)
	{
		HeightMapPixel hmp{ m_Voxels, index * m_VoxelsAmountY, m_VoxelsAmountY };
		hmp.SetAgentHeight(2);

		m_HeightMap.emplace_back(hmp);
	}
}

void NavMeshGenerator::FillVerticesAndIndices()
{
	for (const auto& heightMapPixel : m_HeightMap)
	{
		for (const auto& idx : heightMapPixel.GetWalkableIndices())
		{
			size_t sizeBefore{ m_Vertices.size() };
			const auto& voxel{ m_Voxels[idx]};

			m_Vertices.emplace_back(Vertex{ {voxel.bounds.min.x, voxel.bounds.max.y + m_RenderHeightOffset, voxel.bounds.min.z} });
			m_Vertices.emplace_back(Vertex{ {voxel.bounds.min.x, voxel.bounds.max.y + m_RenderHeightOffset, voxel.bounds.max.z} });
			m_Vertices.emplace_back(Vertex{ {voxel.bounds.max.x, voxel.bounds.max.y + m_RenderHeightOffset, voxel.bounds.min.z} });
			m_Vertices.emplace_back(Vertex{ {voxel.bounds.max.x, voxel.bounds.max.y + m_RenderHeightOffset, voxel.bounds.max.z} });

			m_Indices.emplace_back(sizeBefore);
			m_Indices.emplace_back(sizeBefore + 1);
			m_Indices.emplace_back(sizeBefore + 2);

			m_Indices.emplace_back(sizeBefore + 1);
			m_Indices.emplace_back(sizeBefore + 2);
			m_Indices.emplace_back(sizeBefore + 3);
		}
	}

}

void NavMeshGenerator::FillModelMatrices()
{
	m_ModelMatrices.reserve(m_Voxels.size());

	for (const auto& heightMapPixel : m_HeightMap)
	{
		for (const auto& idx : heightMapPixel.GetWalkableIndices())
		{
			const auto& voxel{ m_Voxels[idx] };

			glm::vec3 scale{ voxel.bounds.max - voxel.bounds.min };
			glm::mat4 scaleMat{ glm::scale(glm::mat4{ 1.f }, scale) };

			glm::vec3 translation{ (voxel.bounds.max + voxel.bounds.min) / 2.f };
			glm::mat4 translationMat{ glm::translate(glm::mat4{1.f}, translation) };

			m_ModelMatrices.emplace_back(translationMat * scaleMat);
		}
	}
}

std::vector<Vertex> NavMeshGenerator::m_Vertices{ glm::vec3{ -0.5f, -0.5f, -0.5f },
													glm::vec3{ -0.5f, -0.5f,  0.5f },
													glm::vec3{ -0.5f,  0.5f, -0.5f },
													glm::vec3{ -0.5f,  0.5f,  0.5f },
													glm::vec3{  0.5f, -0.5f, -0.5f },
													glm::vec3{  0.5f, -0.5f,  0.5f },
													glm::vec3{  0.5f,  0.5f, -0.5f },
													glm::vec3{  0.5f,  0.5f,  0.5f } };

std::vector<uint32_t> NavMeshGenerator::m_Indices{ 0, 1, 2,  1, 2, 3,  0, 4, 6,  6, 0, 2,  1, 5, 7,  7, 1, 3,  4, 5, 6,  6, 7, 2 };