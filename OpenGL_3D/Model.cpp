#include "Model.h"

void Model::UpdateUniforms()
{
}

Model::Model(vec3 position, Material* material, Texture* textureDif, Texture* textureSpec, vector<Mesh*> meshes)
{
	this->position = position;
	this->material = material;
	this->textureDiffuse = textureDif;
	this->textureSpecular = textureSpec;

	for (auto* i : meshes) 
		this->meshes.push_back(new Mesh(*i));
	for (auto* i : this->meshes) {
		i->Move(this->position);
		i->setOrigin(this->position);
	}
}
/*
Model::Model(vec3 position, Material* material, Texture* textureDif, Texture* textureSpec, const char* objFile)
{

	this->position = position;
	this->material = material;
	this->textureDiffuse = textureDif;
	this->textureSpecular = textureSpec;

	vector<Vertex> mesh = LoadOBJ(objFile);

	this->meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0, vec3(0.f)));

	for (auto* i : this->meshes) {
		i->Move(this->position);
		i->setOrigin(this->position);
	}
}*/

Model::~Model()
{
	for (auto*& i : this->meshes)
		delete i;
}

vector<Mesh*> Model::GetMeshes()
{
	return this->meshes;
}

void Model::Render(Shader* shader)
{

	//update uniforms
	this->UpdateUniforms();
	this->material->sendToShader(*shader);

	//use a program
	shader->Use();

	//Draw
	for (auto& i : this->meshes) {
		//activate textures
		this->textureDiffuse->Bind(0);
		//this->textureDiffuse->Bind(1);

		i->Render(shader);
	}

}
