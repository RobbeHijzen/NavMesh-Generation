#pragma once

#include <string>

class Material
{
public:

	std::string GetAlbedoString() const { return m_AlbedoString; }
	std::string GetMetallicString() const { return m_MetallicString; }
	std::string GetRoughnessString() const { return m_RoughnessString; }
	std::string GetOpacityString() const { return m_OpacityString; }
	std::string GetNormalString() const { return m_NormalString; }

	bool UseNormalMap() const { return m_UseNormalMap; }

	void SetAlbedoString(std::string path) { m_AlbedoString = path; }
	void SetMetallicString(std::string path) { m_MetallicString = path; }
	void SetRoughnessString(std::string path) { m_RoughnessString = path; }
	void SetOpacityString(std::string path) { m_OpacityString = path; }
	void SetNormalString(std::string path) { m_NormalString = path; m_UseNormalMap = true; }

	uint32_t GetMaterialID() const { return m_MaterialID; }
	void SetMaterialID(uint32_t materialID) { m_MaterialID = materialID; }

private:

	std::string m_AlbedoString{ "Resources/texs/white.png" };
	std::string m_MetallicString{ "Resources/texs/black.png" };
	std::string m_RoughnessString{ "Resources/texs/white.png" };
	std::string m_OpacityString{ "Resources/texs/white.png" };
	std::string m_NormalString{ "Resources/texs/black.png" };

	bool m_UseNormalMap{ false };

	uint32_t m_MaterialID{};
};