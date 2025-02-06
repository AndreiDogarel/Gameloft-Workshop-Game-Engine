#include "stdafx.h"
#include "SceneObject.h"

SceneObject::SceneObject()
    : id(0), position(Vector3()), rotation(Vector3()), scale(Vector3(1.0f, 1.0f, 1.0f)),
    model(nullptr), shader(nullptr), depthTest(true), wiredFormat(false) {
}

SceneObject::~SceneObject() {
    // Clean up resources if necessary
}

void SceneObject::Draw() {
    
}

void SceneObject::Update(float deltaTime) {
    // Update logic for the scene object
}

void SceneObject::sendCommonData() {
    
}

void SceneObject::sendSpecificData() {
    // Send specific data to the shader (to be overridden by derived classes)
}

