#include "NavMeshGenerator.h"
#include "PhysicsGame/Components/DerivedComponents/CollisionComponent.h"

using namespace NavMeshStructs;

NavMeshGenerator::NavMeshGenerator(Scene* scene)
	: m_Scene{scene}
{
}

std::vector<VoxelNode> NavMeshGenerator::GenerateNavMesh()
{
	m_Voxels.clear();
	m_WalkableVoxelsIndices.clear();
	m_VoxelNodes.clear();
	m_HeightMap.clear();

	InitializeVoxels();
	CheckForVoxelCollisions();
	FillHeightMap();
	FillWalkableVoxels();
	CreateVoxelNodes();

	FillVerticesAndIndices();

	return m_VoxelNodes;
}

std::vector<NavMeshStructs::VoxelNode> NavMeshGenerator::GenerateNavMeshLocally(std::vector<AABB> areas)
{
	for (const auto& area : areas)
	{
		CheckForVoxelCollisions(area);
	}

	FillHeightMap();
	FillWalkableVoxels();
	CreateVoxelNodes();

	FillVerticesAndIndices();

	return m_VoxelNodes;
}

const NavMeshStructs::Voxel* NavMeshGenerator::GetVoxelFromPosition(glm::vec3 position) const
{
	if (!m_Boundaries.Contains(position)) return nullptr;

	position -= m_Boundaries.min;
	position /= (m_Boundaries.max - m_Boundaries.min);

	return &m_Voxels[GetIndexFromXYZ(int(position.x * m_VoxelsAmountX), int(position.y * m_VoxelsAmountY), int(position.z * m_VoxelsAmountZ))];
}

glm::vec3 NavMeshGenerator::GetVoxelSize() const
{
	return (m_Boundaries.max - m_Boundaries.min) / glm::vec3{ m_VoxelsAmountX, m_VoxelsAmountY, m_VoxelsAmountZ };
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
		
		auto xyz{GetXYZFromIndex(index)};

		result.bounds.min.y = min.y + sizePerVoxel.y * xyz.y;
		result.bounds.min.z = min.z + sizePerVoxel.z * xyz.z;
		result.bounds.min.x = min.x + sizePerVoxel.x * xyz.x;

		result.bounds.max.x = result.bounds.min.x + sizePerVoxel.x;
		result.bounds.max.y = result.bounds.min.y + sizePerVoxel.y;
		result.bounds.max.z = result.bounds.min.z + sizePerVoxel.z;

		m_Voxels[index] = result;
	}
}

void NavMeshGenerator::CheckForVoxelCollisions()
{
	CheckForVoxelCollisions(m_Boundaries);
}

void NavMeshGenerator::CheckForVoxelCollisions(const AABB& area)
{
	auto voxels{ GetVoxelsFromArea(area) };
	for (auto voxel : voxels)
		voxel->type = VoxelTypes::Empty;

	for (const auto& object : m_Scene->GetObjects())
	{
		if (auto collision = object->GetComponent<CollisionComponent>())
		{
			if (!collision->HasStaticCollision()) continue;

			for (const auto& aabb : collision->GetAABBs())
			{
				if (area.AreColliding(aabb))
				{
					for (auto voxel : voxels)
					{
						if (voxel->type == VoxelTypes::Solid) continue;

						if (voxel->bounds.AreColliding(aabb))
						{
							voxel->type = VoxelTypes::Solid;
						}
					}
				}
			}
		}
	}
}

void NavMeshGenerator::FillHeightMap()
{
	m_HeightMap.clear();
	m_HeightMap.reserve(m_VoxelsAmountX * m_VoxelsAmountZ);

	for (int index{}; index < m_VoxelsAmountX * m_VoxelsAmountZ; ++index)
	{
		HeightMapPixel hmp{ m_Voxels, index * m_VoxelsAmountY, m_VoxelsAmountY };
		hmp.SetAgentHeight(6);

		m_HeightMap.emplace_back(hmp);
	}
}

void NavMeshGenerator::FillWalkableVoxels()
{
	m_WalkableVoxelsIndices.clear();

	for (const auto& heightMapPixel : m_HeightMap)
	{
		for (const auto& idx : heightMapPixel.GetWalkableIndices())
		{
			m_Voxels[idx].type = VoxelTypes::Walkable;
			m_WalkableVoxelsIndices.emplace_back(idx);
		}
	}
}

void NavMeshGenerator::CreateVoxelNodes()
{
	m_VoxelNodes.clear();
	m_VoxelNodes.reserve(m_Voxels.size());

	for (const auto& walkableVoxelIndex : m_WalkableVoxelsIndices)
	{
		VoxelNode voxelNode{};
		voxelNode.voxel = &m_Voxels[walkableVoxelIndex];
		voxelNode.neighbors = GetNeighborsFromVoxelIndex(walkableVoxelIndex);

		m_VoxelNodes.emplace_back(voxelNode);
	}
}

std::vector<const Voxel*> NavMeshGenerator::GetNeighborsFromVoxelIndex(int index)
{
	std::vector<const Voxel*> neighbors{};

	auto xyz{ GetXYZFromIndex(index) };

	// Negative X
	if (xyz.x > 0)
	{
		Voxel* voxel{ &m_Voxels[GetIndexFromXYZ(xyz.x - 1, xyz.y, xyz.z)] };
		//if (voxel->type == VoxelTypes::Walkable)
		{
			neighbors.emplace_back(voxel);
		}
	}

	// Positive X
	if (xyz.x < m_VoxelsAmountX - 1)
	{
		Voxel* voxel{ &m_Voxels[GetIndexFromXYZ(xyz.x + 1, xyz.y, xyz.z)] };
		//if (voxel->type == VoxelTypes::Walkable)
		{
			neighbors.emplace_back(voxel);
		}
	}

	// Negative Z
	if (xyz.z > 0)
	{
		Voxel* voxel{ &m_Voxels[GetIndexFromXYZ(xyz.x, xyz.y, xyz.z - 1)] };
		//if (voxel->type == VoxelTypes::Walkable)
		{
			neighbors.emplace_back(voxel);
		}
	}

	// Positive Z
	if (xyz.z < m_VoxelsAmountZ - 1)
	{
		Voxel* voxel{ &m_Voxels[GetIndexFromXYZ(xyz.x, xyz.y, xyz.z + 1)] };
		//if (voxel->type == VoxelTypes::Walkable)
		{
			neighbors.emplace_back(voxel);
		}
	}

	// Negative X Negative Z
	if (xyz.x > 0 && xyz.z > 0)
	{
		Voxel* voxel{ &m_Voxels[GetIndexFromXYZ(xyz.x - 1, xyz.y, xyz.z - 1)] };
		//if (voxel->type == VoxelTypes::Walkable)
		{
			neighbors.emplace_back(voxel);
		}
	}

	// Negative X Postive Z
	if (xyz.x > 0 && xyz.z < m_VoxelsAmountZ - 1)
	{
		Voxel* voxel{ &m_Voxels[GetIndexFromXYZ(xyz.x - 1, xyz.y, xyz.z + 1)] };
		//if (voxel->type == VoxelTypes::Walkable)
		{
			neighbors.emplace_back(voxel);
		}
	}

	// Positive X Negative Z
	if (xyz.x < m_VoxelsAmountX - 1 && xyz.z > 0)
	{
		Voxel* voxel{ &m_Voxels[GetIndexFromXYZ(xyz.x + 1, xyz.y, xyz.z - 1)] };
		//if (voxel->type == VoxelTypes::Walkable)
		{
			neighbors.emplace_back(voxel);
		}
	}

	// Positive X Positive Z
	if (xyz.x < m_VoxelsAmountX - 1 && xyz.z < m_VoxelsAmountZ - 1)
	{
		Voxel* voxel{ &m_Voxels[GetIndexFromXYZ(xyz.x + 1, xyz.y, xyz.z + 1)] };
		//if (voxel->type == VoxelTypes::Walkable)
		{
			neighbors.emplace_back(voxel);
		}
	}
	
	return neighbors;
}

std::vector<NavMeshStructs::Voxel*> NavMeshGenerator::GetVoxelsFromArea(const AABB& area)
{
	std::vector<Voxel*> result{};

	auto min{ GetVoxelXYZFromPosition(area.min) };
	auto max{ GetVoxelXYZFromPosition(area.max) };

	for (int x{ min.x }; x <= max.x; ++x)
	{
		for (int y{ min.y }; y <= max.y; ++y)
		{
			for (int z{ min.z }; z <= max.z; ++z)
			{
				result.emplace_back(&m_Voxels[GetIndexFromXYZ(x, y, z)]);
			}
		}
	}

	return result;
}

glm::i32vec3 NavMeshGenerator::GetVoxelXYZFromPosition(glm::vec3 position) const
{
	position -= m_Boundaries.min;
	position /= (m_Boundaries.max - m_Boundaries.min);

	glm::i32vec3 result{ std::clamp(int(position.x * m_VoxelsAmountX), 0, m_VoxelsAmountX - 1), std::clamp(int(position.y * m_VoxelsAmountY), 0, m_VoxelsAmountY - 1), std::clamp(int(position.z * m_VoxelsAmountZ), 0, m_VoxelsAmountZ - 1) };
	return result;
}

glm::i32vec3 NavMeshGenerator::GetXYZFromIndex(int index) const
{
	glm::i32vec3 result{};

	result.x = index / (m_VoxelsAmountY * m_VoxelsAmountZ);
	result.y = index % m_VoxelsAmountY;
	result.z = (index % (m_VoxelsAmountY * m_VoxelsAmountZ)) / m_VoxelsAmountY;

	return result;
}

int NavMeshGenerator::GetIndexFromXYZ(int x, int y, int z) const
{
	int index{};

	index += x * m_VoxelsAmountY * m_VoxelsAmountZ;
	index += y;
	index += z * m_VoxelsAmountY;

	return index;
}


void NavMeshGenerator::FillVerticesAndIndices()
{
	m_Vertices.clear();
	m_Indices.clear();

	for(const auto& walkableVoxelIndex : m_WalkableVoxelsIndices)
	{
		if (m_Voxels[walkableVoxelIndex].bounds.min.y > 6.f) continue;
		size_t sizeBefore{ m_Vertices.size() };

		m_Vertices.emplace_back(Vertex{ {m_Voxels[walkableVoxelIndex].bounds.min.x, m_Voxels[walkableVoxelIndex].bounds.max.y + m_RenderHeightOffset, m_Voxels[walkableVoxelIndex].bounds.min.z}});
		m_Vertices.emplace_back(Vertex{ {m_Voxels[walkableVoxelIndex].bounds.min.x, m_Voxels[walkableVoxelIndex].bounds.max.y + m_RenderHeightOffset, m_Voxels[walkableVoxelIndex].bounds.max.z} });
		m_Vertices.emplace_back(Vertex{ {m_Voxels[walkableVoxelIndex].bounds.max.x, m_Voxels[walkableVoxelIndex].bounds.max.y + m_RenderHeightOffset, m_Voxels[walkableVoxelIndex].bounds.min.z} });
		m_Vertices.emplace_back(Vertex{ {m_Voxels[walkableVoxelIndex].bounds.max.x, m_Voxels[walkableVoxelIndex].bounds.max.y + m_RenderHeightOffset, m_Voxels[walkableVoxelIndex].bounds.max.z} });

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
