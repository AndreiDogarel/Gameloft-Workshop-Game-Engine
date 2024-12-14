#include "stdafx.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include "Camera.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include "ResourceManager.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

#define PI 3.14159265358979323846

GLuint vboId;
GLuint lineVboId;
GLuint modelVboId, modelIboId;
GLuint idTexture;
Shaders myShaders;
Shaders lineShaders;
Shaders modelShader;


Camera myCamera;
float angle = 0.0f;
float step = 0.1f;
float totalTime = 0.0f;
int numVertices = 0, numIndices = 0;

void readNfg(const std::string& filePath, std::vector<Vertex>& vertices, std::vector<unsigned short>& indices) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        printf("Failed to open NFG file: %s\n", filePath.c_str());
        return;
    }

    std::string line;

    std::getline(file, line);
    sscanf(line.c_str(), "NrVertices: %d", &numVertices);

    for (int i = 0; i < numVertices; ++i) {
        std::getline(file, line);
        Vertex vertex;
        sscanf(line.c_str(), "%*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f]",
            &vertex.pos.x, &vertex.pos.y, &vertex.pos.z,
            &vertex.norm.x, &vertex.norm.y, &vertex.norm.z,
            &vertex.binorm.x, &vertex.binorm.y, &vertex.binorm.z,
            &vertex.tgt.x, &vertex.tgt.y, &vertex.tgt.z,
            &vertex.uv.x, &vertex.uv.y);
        vertices.push_back(vertex);
    }

    std::getline(file, line);
    sscanf(line.c_str(), "NrIndices: %d", &numIndices);

    for (int i = 0; i < numIndices / 3; ++i) {
        std::getline(file, line);
        unsigned short idx1, idx2, idx3;
        sscanf(line.c_str(), "%*d. %hu, %hu, %hu", &idx1, &idx2, &idx3);
        indices.push_back(idx1);
        indices.push_back(idx2);
        indices.push_back(idx3);
    }

    file.close();
}

int Init(ESContext* esContext) {

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // triangle data (heap)
    /*Vertex verticesData[6];

    verticesData[0].pos.x = 0.5f;  verticesData[0].pos.y = 0.5f;  verticesData[0].pos.z = 0.0f;
    verticesData[1].pos.x = -0.5f;  verticesData[1].pos.y = 0.5f;  verticesData[1].pos.z = 0.0f;
    verticesData[2].pos.x = -0.5f;  verticesData[2].pos.y = -0.5f;  verticesData[2].pos.z = 0.0f;
    verticesData[3].pos.x = -0.5f;  verticesData[3].pos.y = -0.5f;  verticesData[3].pos.z = 0.0f;
    verticesData[4].pos.x = 0.5f;  verticesData[4].pos.y = -0.5f;  verticesData[4].pos.z = 0.0f;
    verticesData[5].pos.x = 0.5f;  verticesData[5].pos.y = 0.5f;  verticesData[5].pos.z = 0.0f;

    verticesData[0].color.x = 1.0f;  verticesData[0].color.y = 0.0f;  verticesData[0].color.z = 0.0f;
    verticesData[1].color.x = 0.0f;  verticesData[1].color.y = 1.0f;  verticesData[1].color.z = 0.0f;
    verticesData[2].color.x = 0.0f;  verticesData[2].color.y = 0.0f;  verticesData[2].color.z = 1.0f;
    verticesData[3].color.x = 0.0f;  verticesData[3].color.y = 0.0f;  verticesData[3].color.z = 1.0f;
    verticesData[4].color.x = 1.0f;  verticesData[4].color.y = 1.0f;  verticesData[4].color.z = 0.0f;
    verticesData[5].color.x = 1.0f;  verticesData[5].color.y = 0.0f;  verticesData[5].color.z = 0.0f;

    Vertex lineVerticesData[2];
    lineVerticesData[0].pos.x = 0.0f; lineVerticesData[0].pos.y = 0.5f; lineVerticesData[0].pos.z = 0.5f;
    lineVerticesData[1].pos.x = 0.0f; lineVerticesData[1].pos.y = -0.5f; lineVerticesData[1].pos.z = 0.5f;

    // buffer object
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &lineVboId);
    glBindBuffer(GL_ARRAY_BUFFER, lineVboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVerticesData), lineVerticesData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // creation of shaders and program 
    myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
    lineShaders.Init("../Resources/Shaders/LineShaderVS.vs", "../Resources/Shaders/LineShaderFS.fs");*/
    /*
    std::vector<Vertex> vertices;
    std::vector<unsigned short> indices;
    
    readNfg("C:/Users/andre/OneDrive/Desktop/proiect_2015/proiect_2015/NewResourcesPacket/Models/Croco.nfg", vertices, indices);

    glGenBuffers(1, &modelVboId);
    glBindBuffer(GL_ARRAY_BUFFER, modelVboId);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &modelIboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelIboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    int width, height, bpp;
    char* pixelArray = LoadTGA("C:/Users/andre/OneDrive/Desktop/proiect_2015/proiect_2015/NewResourcesPacket/Textures/Croco.tga", &width, &height, &bpp);

    glGenTextures(1, &idTexture);
    glBindTexture(GL_TEXTURE_2D, idTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, (bpp == 24 ? GL_RGB : GL_RGBA),
        width, height, 0, (bpp == 24 ? GL_RGB : GL_RGBA),
        GL_UNSIGNED_BYTE, pixelArray);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return modelShader.Init("../Resources/Shaders/ModelShaderVS.vs", "../Resources/Shaders/ModelShaderFS.fs");
    */
    ResourceManager* resourceManager = ResourceManager::getInstance();
    resourceManager->initialize("C:/Users/andre/OneDrive/Desktop/proiect_2015/NewResourcesPacket/resourceManager.xml");

    return 0;
}

void Draw(ESContext* esContext) {
    glClear(GL_COLOR_BUFFER_BIT);

    /*glUseProgram(myShaders.program);

    glBindBuffer(GL_ARRAY_BUFFER, vboId);

    if (myShaders.positionAttribute != -1) {
        glEnableVertexAttribArray(myShaders.positionAttribute);
        glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    }

    if (myShaders.colorAttribute != -1) {
        glEnableVertexAttribArray(myShaders.colorAttribute);
        glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
    }

    Matrix mRotation;
    mRotation.SetRotationZ(angle);

    if (myShaders.matrixUniform != -1) {
        glUniformMatrix4fv(myShaders.matrixUniform, 1, GL_FALSE, (float*)mRotation.m);
    }

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glUseProgram(lineShaders.program);

    glBindBuffer(GL_ARRAY_BUFFER, lineVboId);

    if (lineShaders.positionAttribute != -1) {
        glEnableVertexAttribArray(lineShaders.positionAttribute);
        glVertexAttribPointer(lineShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    }

    glDrawArrays(GL_LINES, 0, 2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);*/

    /*
    glUseProgram(modelShader.program);

    glBindBuffer(GL_ARRAY_BUFFER, modelVboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelIboId);
    glBindTexture(GL_TEXTURE_2D, idTexture);

    Matrix mvp;
    mvp = myCamera.viewMatrix * myCamera.perspectiveMatrix;

    if (modelShader.matrixUniform != -1) {
        glUniformMatrix4fv(modelShader.matrixUniform, 1, GL_FALSE, (float*)mvp.m);
    }

    if (modelShader.positionAttribute != -1) {
        glEnableVertexAttribArray(modelShader.positionAttribute);
        glVertexAttribPointer(modelShader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    }

    if (modelShader.textureUniform != -1) {
        glUniform1i(modelShader.textureUniform, 0);
    }

    if (modelShader.uvAttribute != -1) {
        glEnableVertexAttribArray(modelShader.uvAttribute);
        glVertexAttribPointer(modelShader.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    }
    
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
    */
}

void Update(ESContext* esContext, float deltaTime) {
    /*angle += step;
    if (angle >= 2 * PI) {
        angle -= 2 * PI;
    }*/
    totalTime += deltaTime;
    if (totalTime > Globals::frameTime) {
        totalTime = totalTime - Globals::frameTime;
        myCamera.setDeltaTime(Globals::frameTime);
    }
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed) {
    if (bIsPressed) {
        printf("Key pressed: %c (ASCII: %d)\n", key, key);
    }

    switch (key) {
    case 'W': case 'w':
        myCamera.moveOz(1); // Move forward
        break;
    case 'S': case 's':
        myCamera.moveOz(-1); // Move backward
        break;
    case 'A': case 'a':
        myCamera.moveOx(-1); // Move left
        break;
    case 'D': case 'd':
        myCamera.moveOx(1); // Move right
        break;
    case 'Q': case 'q':
        myCamera.moveOy(1); // Move up
        break;
    case 'E': case 'e':
        myCamera.moveOy(-1); // Move down
        break;
    case VK_UP:
        myCamera.rotateOx(1); // Rotate up
        break;
    case VK_DOWN:
        myCamera.rotateOx(-1); // Rotate down
        break;
    case VK_LEFT:
        myCamera.rotateOy(1); // Rotate left
        break;
    case VK_RIGHT:
        myCamera.rotateOy(-1); // Rotate right
        break;
    case 'Z': case 'z':
        myCamera.rotateOz(1); // Rotate clockwise around Z
        break;
    case 'X': case 'x':
        myCamera.rotateOz(-1); // Rotate counter-clockwise around Z
        break;
    }
}

void Mouse(ESContext* esContext, MouseButtons btn, MouseEvents event, int x, int y) {
    if (event == MouseEvents::BTN_DOWN) {
        if (btn == MouseButtons::LEFT) {
            if (x < esContext->width / 2) {
                step = -fabs(step);
            }
            else {
                step = fabs(step);
            }
        }
    }
}


void CleanUp() {
    glDeleteBuffers(1, &vboId);
    glDeleteBuffers(1, &lineVboId);
    glDeleteBuffers(1, &modelVboId);
    glDeleteBuffers(1, &modelIboId);
    glDeleteTextures(1, &idTexture);
}

int _tmain(int argc, _TCHAR* argv[]) {
    // identifying memory leaks
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    ESContext esContext;

    esInitContext(&esContext);

    esCreateWindow(&esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

    if (Init(&esContext) != 0)
        return 0;

    esRegisterDrawFunc(&esContext, Draw);
    esRegisterUpdateFunc(&esContext, Update);
    esRegisterKeyFunc(&esContext, Key);
    esRegisterMouseFunc(&esContext, Mouse);

    esMainLoop(&esContext);

    // releasing OpenGL resources
    CleanUp();

    printf("Press any key...\n");
    _getch();

    return 0;
}