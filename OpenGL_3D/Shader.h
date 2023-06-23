#pragma once

#include "libs.h"

class Shader
{

private:
	//shader id
	GLuint id;
	//opengl version
	const int versionMajor;
	const int versionMinor;

	string LoadShaderSource(char* filename);
	GLuint LoadShader(GLenum type, char* filename);
	void LinkProgram(GLuint vertexShader, GLuint fragmentShader);
public:
	Shader(const int versionMajor, const int versionMinor, char* vertexFile, char* fragmentFile);
	~Shader();

	void Use();
	void UnUse();
	void SetVec3f(fvec3 value, const GLchar* name);
	void Set1i(GLuint value, const GLchar* name);
	void Set1f(GLfloat value, const GLchar* name);
	void SetMat4fv(mat4 value, const GLchar* name);
};

