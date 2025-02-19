#pragma once

#include <vector>
#include <memory>

#include "PhysicsGame/Meshes/Mesh.h"
#include "VulkanBase/HelperStructs/IRenderable.h"
#include "VulkanBase/Materials/Material.h"
#include "Object.h"
#include "Singleton.h"

class Scene : public Singleton<Scene>
{
public:
	Scene() = default;

    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;
	Scene(Scene&& other) noexcept = delete;
	Scene& operator=(Scene&& other) noexcept = delete;

	void GameStart()
	{
		for (const auto& object : m_Objects)
		{
			object->GameStart();
		}
	}
	void Update(GLFWwindow* window)
	{
		for (const auto& object : m_Objects)
		{
			object->Update(window);
		}
	}
	void LateUpdate()
	{
		for (const auto& object : m_Objects)
		{
			object->LateUpdate();
		}
	}


	void AddObject(Object* object)
	{
		m_Objects.emplace_back(object);

		AssignToRenderables(object);
		
		for (const auto& component : object->GetAllComponents())
		{
			AssignToRenderables(component);
		}
	}

	std::vector<Object*> GetObjects()
	{
		std::vector<Object*> meshes{};
		for (const auto& mesh : m_Objects)
		{
			meshes.emplace_back(mesh.get());
		}
		return meshes;
	}

	Material* CreateMaterial()
	{
		Material* mat{ m_Materials.emplace_back(std::make_unique<Material>()).get() };
		mat->SetMaterialID((uint32_t)(m_Materials.size() - 1));
		return mat;
	}


	auto GetObjectsAmount() const { return m_Objects.size(); }

	auto GetRenderables() const { return m_Renderables; }
	auto GetRenderablesAmount() const { return m_Renderables.size(); }

	auto GetMaterials() const 
	{ 
		std::vector<Material*> mats{};
		for (const auto& mat : m_Materials)
			mats.emplace_back(mat.get());

		return mats;
	}
	auto GetMaterialsAmount() const { return m_Materials.size(); }

private:

	void AssignToRenderables(auto item)
	{
		if (auto renderable = dynamic_cast<IRenderable*>(item))
		{
			m_Renderables.emplace_back(renderable);
			renderable->SetRenderID(static_cast<uint32_t>(m_Renderables.size() - 1));
		}
	}

	std::vector<std::unique_ptr<Object>> m_Objects{};
	std::vector<IRenderable*> m_Renderables{};

	std::vector<std::unique_ptr<Material>> m_Materials{};
};