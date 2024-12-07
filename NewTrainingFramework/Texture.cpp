#include "stdafx.h"
#include "Texture.h"


Texture::Texture(TextureResource* _tr) {
	this->tr = _tr;
}

Texture::~Texture() {
	if (this->tr != NULL) {
		delete this->tr;
	}
}

void Texture::Load() {
    std::string absolutePath = (*this->tr).filePath + (*this->tr).fileName;
    int width, height, bpp;
    char* pixelArray = LoadTGA(absolutePath.c_str(), &width, &height, &bpp);

    glGenTextures(1, (&this->textureId));
    glBindTexture(GL_TEXTURE_2D, (this->textureId));
    glTexImage2D(GL_TEXTURE_2D, 0, (bpp == 24 ? GL_RGB : GL_RGBA),
        width, height, 0, (bpp == 24 ? GL_RGB : GL_RGBA),
        GL_UNSIGNED_BYTE, pixelArray);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (*this->tr).wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (*this->tr).wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (*this->tr).min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (*this->tr).mag_filter);
    glBindTexture(GL_TEXTURE_2D, 0);
}