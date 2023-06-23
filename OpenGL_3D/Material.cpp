#include "Material.h"

Material::Material(vec3 ambient, vec3 diffuse, vec3 specular, GLint diffuseTex, GLint specularTex)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->diffuseTex = diffuseTex;
	this->specularTex = specularTex;
}

Material::~Material()
{
}

void Material::sendToShader(Shader& program)
{
	program.SetVec3f(ambient, "material.ambient");
	program.SetVec3f(diffuse, "material.diffuse");
	program.SetVec3f(specular, "material.specular");
	program.Set1i(diffuseTex, "material.diffuseTex");
	program.Set1i(specularTex, "material.specularTex");
}
