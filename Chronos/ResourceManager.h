#pragma once
#include "Audio.h"
#include "Singleton.h"

class Texture2D;
class Font;

class ResourceManager final : public Singleton<ResourceManager>
{
public:
	void Init(const std::string& data);
	std::shared_ptr<Texture2D> LoadEmptyTexture() const;
	std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;        
	std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
	WAV LoadWAV(const std::string& file) const;
private:
	friend class Singleton<ResourceManager>;
	ResourceManager() = default;
	std::string m_DataPath;
	std::string m_DefaultImage = "Default.png";
};