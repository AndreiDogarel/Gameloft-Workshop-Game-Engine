#pragma once
#include <vector>
#include "math.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"

class SceneObject {
public:
    SceneObject();
    virtual ~SceneObject();

    void Draw();
    void Update(float deltaTime);

    int id;
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
    Model* model;
    Shaders* shader;
    std::vector<Texture*> textures;
    bool depthTest;
    bool wiredFormat;

protected:
    virtual void sendCommonData();
    virtual void sendSpecificData();
};

