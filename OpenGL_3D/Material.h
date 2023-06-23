#pragma once

#include "libs.h"
#include "Shader.h"
using namespace glm;
class Material
{
private:
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	GLint diffuseTex;
	GLint specularTex;
public:
	Material(vec3 ambient, vec3 diffuse, vec3 specular, GLint diffuseTex, GLint specularTex);
	~Material();
	void sendToShader(Shader& program);
};

