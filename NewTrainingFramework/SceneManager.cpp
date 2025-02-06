#include "stdafx.h"
#include <../RapidXML/rapidxml.hpp>
#include <../RapidXML/rapidxml_utils.hpp>
#include "SceneManager.h"
#include "ResourceManager.h"
#include <iostream>

SceneManager* SceneManager::instance = nullptr;

SceneManager* SceneManager::getInstance() {
    if (!instance) {
        instance = new SceneManager();
    }
    return instance;
}

void SceneManager::InitWindow(const char* configFilePath) {
    rapidxml::file<> xmlFile(configFilePath);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    auto* root = doc.first_node("sceneManager");
    if (!root) {
        std::cerr << "Error: No root node found in XML file." << std::endl;
        return;
    }

    auto* windowElement = root->first_node("defaultScreenSize");
    if (windowElement) {
        float width = std::stof(windowElement->first_node("width")->value());
        float height = std::stof(windowElement->first_node("height")->value());
        // Set window settings
    }

    auto* bgColorElement = root->first_node("backgroundColor");
    if (bgColorElement) {
        float bgColor[3];
        bgColor[0] = std::stof(bgColorElement->first_node("r")->value());
        bgColor[1] = std::stof(bgColorElement->first_node("g")->value());
        bgColor[2] = std::stof(bgColorElement->first_node("b")->value());
        // Set background color
    }
}

void SceneManager::Init(const char* configFilePath) {
    ResourceManager::getInstance()->initialize(configFilePath);

    rapidxml::file<> xmlFile(configFilePath);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    auto* root = doc.first_node("sceneManager");
    if (!root) {
        std::cerr << "Error: No root node found in XML file." << std::endl;
        return;
    }

    // Initialize cameras
    auto* camerasElement = root->first_node("cameras");
    if (camerasElement) {
        for (auto* cameraElement = camerasElement->first_node("camera"); cameraElement; cameraElement = cameraElement->next_sibling("camera")) {
            int id = std::stoi(cameraElement->first_attribute("id")->value());
            Vector3 position(
                std::stof(cameraElement->first_node("position")->first_node("x")->value()),
                std::stof(cameraElement->first_node("position")->first_node("y")->value()),
                std::stof(cameraElement->first_node("position")->first_node("z")->value())
            );
            Vector3 target(
                std::stof(cameraElement->first_node("target")->first_node("x")->value()),
                std::stof(cameraElement->first_node("target")->first_node("y")->value()),
                std::stof(cameraElement->first_node("target")->first_node("z")->value())
            );
            Vector3 up(
                std::stof(cameraElement->first_node("up")->first_node("x")->value()),
                std::stof(cameraElement->first_node("up")->first_node("y")->value()),
                std::stof(cameraElement->first_node("up")->first_node("z")->value())
            );
            GLfloat moveSpeed = std::stof(cameraElement->first_node("translationSpeed")->value());
            GLfloat rotateSpeed = std::stof(cameraElement->first_node("rotationSpeed")->value());
            GLfloat nearPlane = std::stof(cameraElement->first_node("near")->value());
            GLfloat farPlane = std::stof(cameraElement->first_node("far")->value());
            GLfloat fov = std::stof(cameraElement->first_node("fov")->value());

            Camera* camera = new Camera(position, target, up, moveSpeed, rotateSpeed, nearPlane, farPlane, fov);
            camera->setId(id);
            cameras.push_back(camera);
        }
        // Set active camera
        auto* activeCameraElement = root->first_node("activeCamera");
        if (activeCameraElement) {
            int activeCameraId = std::stoi(activeCameraElement->value());
            for (Camera* camera : cameras) {
                if (camera->getId() == activeCameraId) {
                    activeCamera = camera;
                    break;
                }
            }
        }
    }

    // Initialize scene objects
    auto* objectsElement = root->first_node("objects");
    if (objectsElement) {
        for (auto* objectElement = objectsElement->first_node("object"); objectElement; objectElement = objectElement->next_sibling("object")) {
            SceneObject* sceneObject = new SceneObject();
            sceneObject->id = std::stoi(objectElement->first_attribute("id")->value());
            sceneObject->position = Vector3(
                std::stof(objectElement->first_node("position")->first_node("x")->value()),
                std::stof(objectElement->first_node("position")->first_node("y")->value()),
                std::stof(objectElement->first_node("position")->first_node("z")->value())
            );
            sceneObject->rotation = Vector3(
                std::stof(objectElement->first_node("rotation")->first_node("x")->value()),
                std::stof(objectElement->first_node("rotation")->first_node("y")->value()),
                std::stof(objectElement->first_node("rotation")->first_node("z")->value())
            );
            sceneObject->scale = Vector3(
                std::stof(objectElement->first_node("scale")->first_node("x")->value()),
                std::stof(objectElement->first_node("scale")->first_node("y")->value()),
                std::stof(objectElement->first_node("scale")->first_node("z")->value())
            );
            int modelId = std::stoi(objectElement->first_node("model")->value());
            ModelResource* modelResource = ResourceManager::getInstance()->getModelResources()[modelId];
            sceneObject->model = ResourceManager::getInstance()->loadModel(modelResource);

            int shaderId = std::stoi(objectElement->first_node("shader")->value());
            ShaderResource* shaderResource = ResourceManager::getInstance()->getShaderResources()[shaderId];
            sceneObject->shader = ResourceManager::getInstance()->loadShader(shaderResource);

            auto* texturesElement = objectElement->first_node("textures");
            if (texturesElement) {
                for (auto* textureElement = texturesElement->first_node("texture"); textureElement; textureElement = textureElement->next_sibling("texture")) {
                    int textureId = std::stoi(textureElement->first_attribute("id")->value());
                    TextureResource* textureResource = ResourceManager::getInstance()->getTextureResources()[textureId];
                    sceneObject->textures.push_back(ResourceManager::getInstance()->loadTexture(textureResource));
                }
            }
            sceneObject->depthTest = objectElement->first_node("depthTest") != nullptr;
            sceneObject->wiredFormat = objectElement->first_node("wired") != nullptr;

            sceneObjects.push_back(sceneObject);
        }
    }
}

void SceneManager::Draw() {
    for (SceneObject* object : sceneObjects) {
        object->Draw();
    }
}

void SceneManager::Update(float deltaTime) {
    for (SceneObject* object : sceneObjects) {
        object->Update(deltaTime);
    }
}
