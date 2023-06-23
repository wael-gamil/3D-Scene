#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "ObjLoader.h"

class Model
{
private:
	Material* material;
	Texture* textureDiffuse;
	Texture* textureSpecular;
	vector<Mesh*> meshes;
	vec3 position;

	void UpdateUniforms();

public:
	Model(vec3 position, Material* material, Texture* textureDif, Texture* textureSpec, vector<Mesh*> meshes); 

	//Model(vec3 position, Material* material, Texture* textureDif, Texture* textureSpec, const char* objFile);
	~Model();
	//accessor
	vector<Mesh*> GetMeshes();
	void Render(Shader* shader);
};
