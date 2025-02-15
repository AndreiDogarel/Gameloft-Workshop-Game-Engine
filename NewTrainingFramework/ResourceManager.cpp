#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance = NULL;

ResourceManager* ResourceManager::getInstance() {
    if (!instance)
        instance = new ResourceManager();
    return instance;
}

GLenum ResourceManager::mapStringToGLenum(const std::string& value) {
    if (value == "NEAREST") return GL_NEAREST;
    if (value == "LINEAR") return GL_LINEAR;
    if (value == "CLAMP_TO_EDGE") return GL_CLAMP_TO_EDGE;
    if (value == "MIRRORED_REPEAT") return GL_MIRRORED_REPEAT;
    if (value == "REPEAT") return GL_REPEAT;

    throw std::runtime_error("Unknown OpenGL constant: " + value);
}

void ResourceManager::parseXML(const std::string& filePath) {
    rapidxml::file<> xmlFile(filePath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    auto* root = doc.first_node("resourceManager");

    // Parse models
    for (auto* modelFolder = root->first_node("models")->first_node("folder");
        modelFolder; modelFolder = modelFolder->next_sibling("folder")) {
        for (auto* modelNode = modelFolder->first_node("model");
            modelNode; modelNode = modelNode->next_sibling("model")) {

            auto* idAttr = modelNode->first_attribute("id");
            auto* fileNode = modelNode->first_node("file");

            if (idAttr && fileNode) {
                ModelResource* model = new ModelResource();
                model->id = std::stoi(idAttr->value());
                model->fileName = fileNode->value();
                model->filePath = modelFolder->first_attribute()->value();
                modelResources[model->id] = model;
            }
        }
    }

    // Parse shaders
    for (auto* shaderFolder = root->first_node("shaders")->first_node("folder");
        shaderFolder; shaderFolder = shaderFolder->next_sibling("folder")) {
        for (auto* shaderNode = shaderFolder->first_node("shader");
            shaderNode; shaderNode = shaderNode->next_sibling("shader")) {

            auto* idAttr = shaderNode->first_attribute("id");
            auto* vsNode = shaderNode->first_node("vs");
            auto* fsNode = shaderNode->first_node("fs");

            if (idAttr && vsNode && fsNode) {
                ShaderResource* shader = new ShaderResource();
                shader->id = std::stoi(idAttr->value());
                shader->vertexShader = vsNode->value();
                shader->fragmentShader = fsNode->value();
                shader->filePath = shaderFolder->first_attribute()->value();
                shaderResources[shader->id] = shader;
            }
        }
    }

    // Parse textures
    for (auto* textureFolder = root->first_node("textures")->first_node("folder");
        textureFolder; textureFolder = textureFolder->next_sibling("folder")) {
        for (auto* textureNode = textureFolder->first_node("texture");
            textureNode; textureNode = textureNode->next_sibling("texture")) {

            auto* idAttr = textureNode->first_attribute("id");
            auto* typeAttr = textureNode->first_attribute("type");
            auto* fileNode = textureNode->first_node("file");
            auto* minFilterNode = textureNode->first_node("min_filter");
            auto* magFilterNode = textureNode->first_node("mag_filter");
            auto* wrapSNode = textureNode->first_node("wrap_s");
            auto* wrapTNode = textureNode->first_node("wrap_t");

            if (idAttr && fileNode && minFilterNode && magFilterNode && wrapSNode && wrapTNode) {
                TextureResource* texture = new TextureResource();
                texture->id = std::stoi(idAttr->value());
                texture->type = typeAttr->value();
                texture->fileName = fileNode->value();
                texture->filePath = textureFolder->first_attribute()->value();
                texture->min_filter = mapStringToGLenum(minFilterNode->value());
                texture->mag_filter = mapStringToGLenum(magFilterNode->value());
                texture->wrap_s = mapStringToGLenum(wrapSNode->value());
                texture->wrap_t = mapStringToGLenum(wrapTNode->value());
                textureResources[texture->id] = texture;
            }
        }
    }
}

void ResourceManager::initialize(const std::string& xmlPath) {
    parseXML(xmlPath);
}

Model* ResourceManager::loadModel(ModelResource* _model) {
    if (modelResources.find((*_model).id) != modelResources.end()) {
        Model* model = new Model(_model);
		model->Load();
        return model;
    }
    Model* model = new Model(_model);
    model->Load();
    modelResources[(*_model).id] = _model;
    return model;
}

Shader* ResourceManager::loadShader(ShaderResource* _shader) {
    if (shaderResources.find((*_shader).id) != shaderResources.end()) {
        Shader* shader = new Shader(_shader);
        shader->Load();
        return shader;
    }
    Shader* shader = new Shader(_shader);
    shader->Load();
    shaderResources[(*_shader).id] = _shader;
    return shader;
}

Texture* ResourceManager::loadTexture(TextureResource* _texture) {
    if (textureResources.find((*_texture).id) != textureResources.end()) {
        Texture* texture = new Texture(_texture);
        texture->Load();
		return texture;
    }
    Texture* texture = new Texture(_texture);
    texture->Load();
    textureResources[(*_texture).id] = _texture;
    return texture;
}
