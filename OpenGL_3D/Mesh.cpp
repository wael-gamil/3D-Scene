#include "Mesh.h"

void Mesh::InitVAO()
{
	//Create Vao
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), this->vertexArray, GL_STATIC_DRAW);

	if (nrOfIndices > 0) {
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), this->indexArray, GL_STATIC_DRAW);
	}
	//VertexattribPointer and enable
	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	//texcoord
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);
	//normal	
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	//bind vao 0
	glBindVertexArray(0);

}

void Mesh::UpdateUniform(Shader* shader)
{
	shader->SetMat4fv(this->ModelMatrix, "ModelMatrix");
}

void Mesh::UpdateModelMatrix()
{
	this->ModelMatrix = mat4(1.f); 
	this->ModelMatrix = translate(this->ModelMatrix, this->position);
	//this->ModelMatrix = translate(this->ModelMatrix, this->origin);
	this->ModelMatrix = rotate(this->ModelMatrix, radians(this->rotation.x), vec3(1.f, 0.f, 0.f));
	this->ModelMatrix = rotate(this->ModelMatrix, radians(this->rotation.y), vec3(0.f, 1.f, 0.f));
	this->ModelMatrix = rotate(this->ModelMatrix, radians(this->rotation.z), vec3(0.f, 0.f, 1.f));
	//this->ModelMatrix = translate(this->ModelMatrix, this->position - this->origin);
	this->ModelMatrix = scale(this->ModelMatrix, this->scaling);
}

Mesh::Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray,
	const unsigned& nrOfIndices, vec3 position, vec3 origin, vec3 rotation, vec3 scaling)
{
	this->position = position;
	this->origin = origin;
	this->rotation = rotation;
	this->scaling = scaling;

	this->nrOfVertices = nrOfVertices;
	this->nrOfIndices = nrOfIndices;

	this->vertexArray = new Vertex[this->nrOfVertices];
	for (size_t i = 0; i < nrOfVertices; i++)
	{
		this->vertexArray[i] = vertexArray[i];
	}

	this->indexArray = new GLuint[this->nrOfIndices];
	for (size_t i = 0; i < nrOfIndices; i++)
	{
		this->indexArray[i] = indexArray[i];
	}
}

Mesh::Mesh(const Mesh& obj)
{
	this->position = obj.position;
	this->origin = obj.origin;
	this->rotation = obj.rotation;
	this->scaling = obj.scaling;

	this->nrOfVertices = obj.nrOfVertices;
	this->nrOfIndices = obj.nrOfIndices;

	this->vertexArray = new Vertex[this->nrOfVertices];
	for (size_t i = 0; i < nrOfVertices; i++)
		this->vertexArray[i] = obj.vertexArray[i];
	this->indexArray = new GLuint[this->nrOfIndices];
	for (size_t i = 0; i < nrOfIndices; i++)
		indexArray[i] = obj.indexArray[i];

	this->InitVAO();
	this->UpdateModelMatrix();

}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	if (nrOfIndices > 0)
		glDeleteBuffers(1, &this->EBO);

	delete[] this->vertexArray;
	delete[] this->indexArray;
}

void Mesh::setPosition(const vec3 position)
{
	this->position = position;
}

void Mesh::setOrigin(const vec3 origin)
{
	this->origin = origin;
}

void Mesh::setRotation(const vec3 rotation)
{
	this->rotation = rotation;
}

void Mesh::setScale(const vec3 scaling)
{
	this->scaling = scaling;
}

void Mesh::Move(const vec3 position)
{
	this->position += position;
}

void Mesh::Rotate(const vec3 rotation)
{
	this->rotation += rotation;
}

void Mesh::Scale(const vec3 scaling)
{
	this->scaling += scaling;
}

void Mesh::Render(Shader* shader)
{
	//update uniform
	this->UpdateModelMatrix();
	this->UpdateUniform(shader);

	shader->Use();
	//bind vao
	glBindVertexArray(this -> VAO);

	//draw
	if (this->nrOfIndices == 0)
		glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices);
	else
		glDrawElements(GL_TRIANGLES,this-> nrOfIndices, GL_UNSIGNED_INT, 0);

	//CleanUp
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
