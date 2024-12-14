#pragma once
#include "stdafx.h"
#include "../Include/RapidXML/rapidxml.hpp"
#include "../Include/RapidXML/rapidxml_utils.hpp"
#include <map>
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include <stdexcept>
#include "../Utilities/utilities.h"


class ResourceManager
{
private:
	static ResourceManager* instance;
	std::map<int, Model*> modelResources;
	std::map<int, Shader*> shaderResources;
	std::map<int, Texture*> textureResources;

	ResourceManager() = default;

	GLenum mapStringToGLenum(const std::string& value);
	void parseXML(const std::string& filePath);

public:
	static ResourceManager* getInstance();
	void initialize(const std::string& xmlPath);
	Model* loadModel(ModelResource* _model);
	Shader* loadShader(ShaderResource* _shader);
	Texture* loadTexture(TextureResource* _texture);
};

