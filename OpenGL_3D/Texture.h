#pragma once
#include "libs.h"

class Texture
{
private:
	GLuint id;
	int width;
	int height;
	unsigned int type;
public:
	Texture(const char* filename, GLenum type);
	~Texture();
	inline GLuint GetID() const { return this->id; }
	void Bind(const GLint texture_unit);
	void UnBind();
};

