#pragma once

#include "libs.h"
#include "Vertex.h"
#include "Shader.h"
#include "Primitive.h"

class Mesh
{
private:
	Vertex* vertexArray;
	unsigned nrOfVertices;
	GLuint* indexArray;
	unsigned nrOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	vec3 position;
	vec3 origin;
	vec3 rotation;
	vec3 scaling;
	mat4 ModelMatrix;



	void InitVAO();
	void UpdateUniform(Shader* shader);
	void UpdateModelMatrix();
public:
	Mesh(Vertex* vertexArray,
		const unsigned& nrOfVertices,
		GLuint* indexArray,
		const unsigned& nrOfIndices, vec3 position = vec3(0.f), vec3 origin = vec3(0.f),
		vec3 rotation = vec3(0.f), vec3 scaling = vec3(1.f));

	Mesh(const Mesh& obj);
	~Mesh();
	//Accessors

	//Modifiers
	void setPosition(const vec3 position);
	void setOrigin(const vec3 origin);
	void setRotation(const vec3 rotation);
	void setScale(const vec3 scale);

	//Functions
	void Move(const vec3 position);
	void Rotate(const vec3 rotation);
	void Scale(const vec3 Scaling);
	void Render(Shader* shader);

};