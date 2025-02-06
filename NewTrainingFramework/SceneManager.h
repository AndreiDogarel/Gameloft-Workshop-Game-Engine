#pragma once
#include <vector>
#include "Camera.h"
#include "SceneObject.h"

class SceneManager {
public:
    static SceneManager* getInstance();
    void InitWindow(const char* configFilePath);
    void Init(const char* configFilePath);
    void Draw();
    void Update(float deltaTime);

private:
    SceneManager() = default;
    static SceneManager* instance;
    std::vector<SceneObject*> sceneObjects;
    std::vector<Camera*> cameras;
    Camera* activeCamera;
    // Add other properties as needed
};
