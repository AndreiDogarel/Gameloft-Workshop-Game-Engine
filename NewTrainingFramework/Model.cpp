#include "stdafx.h"
#include "Model.h"
#include <fstream>

Model::Model(ModelResource* _mr) {
	this->mr = _mr;
}

Model::~Model() {
	if (this->mr != NULL) {
		delete this->mr;
	}
}

void Model::Load() {
    int numVertices, numIndices;
	std::string absolutePath = (*this->mr).filePath + (*this->mr).fileName;
    std::vector<Vertex> vertices;
    std::vector<unsigned short> indices;

    std::ifstream file(absolutePath);
    if (!file.is_open()) {
        printf("Failed to open NFG file: %s\n", absolutePath.c_str());
        return;
    }

    std::string line;

    std::getline(file, line);
    sscanf(line.c_str(), "NrVertices: %d", (&this->nrVertecsi));

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
    sscanf(line.c_str(), "NrIndices: %d", (&this->nrIndici));

    for (int i = 0; i < numIndices / 3; ++i) {
        std::getline(file, line);
        unsigned short idx1, idx2, idx3;
        sscanf(line.c_str(), "%*d. %hu, %hu, %hu", &idx1, &idx2, &idx3);
        indices.push_back(idx1);
        indices.push_back(idx2);
        indices.push_back(idx3);
    }

    file.close();

    glGenBuffers(1, (&this->vboId));
    glBindBuffer(GL_ARRAY_BUFFER, (this->vboId));
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, (&this->iboId));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (this->iboId));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}