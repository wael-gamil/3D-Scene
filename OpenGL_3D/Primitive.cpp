#include "Primitive.h"

Primitive::Primitive()
{
}

Primitive::~Primitive()
{
}

void Primitive::Set(const Vertex* vertices, const unsigned nrOfVertices, const GLuint* indices, const unsigned nrOfIndices)
{
	for (size_t i = 0; i < nrOfVertices; i++)
	{
		this->vertices.push_back(vertices[i]);
	}
	for (size_t i = 0; i < nrOfIndices; i++)
	{
		this->indices.push_back(indices[i]);
	}
}

Vertex* Primitive::GetVertices()
{
	return vertices.data();
}

GLuint* Primitive::GetIndices()
{
	return this->indices.data();
}

const unsigned Primitive::GetNrOfVertices()
{
	return this->vertices.size();
}

const unsigned Primitive::GetNrOfIndices()
{
	return this->indices.size();
}

Quad::Quad() : Primitive()
{
	Vertex vertices[] =
	{
		vec3(-0.5f,0.5f,0.f),	vec3(1.f,0.f,0.f) ,		vec2(0.f,1.f),	vec3(0.f,0.f,1.f) ,
		vec3(-0.5f,-0.5f,0.f),	vec3(0.f, 1.f, 0.f),	vec2(0.f,0.f),	vec3(0.f,0.f, 1.f),
		vec3(0.5f,-0.5f,0.f),	vec3(0.f,0.f,1.f),		vec2(1.f,0.f),	vec3(0.f,0.f,1.f),
		vec3(0.5f,0.5f,0.f),	vec3(1.f,0.f,0.f) ,		vec2(1.f,1.f),  vec3(0.f,0.f,1.f)
	};

	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[]{
		0, 1, 2,
		0, 2, 3
	};

	unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

	this->Set(vertices, nrOfVertices, indices, nrOfIndices);
}

Triangle::Triangle() : Primitive()
{

	Vertex vertices[] =
	{
		vec3(0.f,0.5f,0.f),		vec3(1.f,0.f,0.f) ,		vec2(0.5f,1.f),	vec3(0.f,0.f,1.f) ,
		vec3(-0.5f,-0.5f,0.f),	vec3(0.f, 1.f, 0.f),	vec2(0.f,0.f),	vec3(0.f,0.f,1.f),
		vec3(0.5f,-0.5f,0.f),	vec3(0.f,0.f,1.f),		vec2(1.f,0.f),	vec3(0.f,0.f,1.f)
	};

	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[]{
		0, 1, 2,
	};

	unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

	this->Set(vertices, nrOfVertices, indices, nrOfIndices);
}

Cube::Cube() : Primitive()
{
	Vertex vertices[] =
	{
		//front
		vec3(0.5f,0.5f,0.5f),		vec3(1.f,0.f,0.f) ,		vec2(1.f,1.f),	vec3(0.f,0.f, 1.f),
		vec3(-0.5f,0.5f,0.5f),		vec3(0.f, 1.f, 0.f),	vec2(0.f,1.f),	vec3(0.f,0.f, 1.f),
		vec3(-0.5f,-0.5f,0.5f),		vec3(0.f,0.f,1.f),		vec2(0.f,0.f),	vec3(0.f,0.f, 1.f),

		vec3(-0.5f,-0.5f,0.5f),		vec3(0.f,0.f,1.f),		vec2(0.f,0.f),	vec3(0.f,0.f, 1.f),
		vec3(0.5f,-0.5f,0.5f),		vec3(1.f,0.f,0.f) ,		vec2(1.f,0.f),  vec3(0.f,0.f, 1.f),
		vec3(0.5f,0.5f,0.5f),		vec3(1.f,0.f,0.f) ,		vec2(1.f,1.f),	vec3(0.f,0.f, 1.f),

		//left
		vec3(-0.5f, 0.5f,0.5f),		vec3(1.f,0.f,0.f) ,		vec2(1.f,1.f),	vec3(-1.f,0.f, 0.f),
		vec3(-0.5f, 0.5f,-0.5f),		vec3(0.f, 1.f, 0.f),	vec2(0.f,1.f),	vec3(-1.f,0.f, 0.f),
		vec3(-0.5f,-0.5f,-0.5f),		vec3(0.f,0.f,1.f),		vec2(0.f,0.f),	vec3(-1.f,0.f, 0.f),
					
		vec3(-0.5f,-0.5f,-0.5f),		vec3(0.f,0.f,1.f),		vec2(0.f,0.f),	vec3(-1.f,0.f, 0.f),
		vec3(-0.5f,-0.5f,0.5f),		vec3(1.f,0.f,0.f) ,		vec2(1.f,0.f),  vec3(-1.f,0.f, 0.f),
		vec3(-0.5f, 0.5f,0.5f),		vec3(1.f,0.f,0.f) ,		vec2(1.f,1.f),	vec3(-1.f,0.f, 0.f),
					
		//back		
					
		vec3(-0.5f, 0.5f,-0.5f),		vec3(0.f, 1.f, 0.f),	vec2(0.f,1.f),	vec3(0.f,0.f, -1.f),
		vec3(0.5f,  0.5f,-0.5f),		vec3(1.f,0.f,0.f) ,		vec2(1.f,1.f),	vec3(0.f,0.f, -1.f),
		vec3(0.5f, -0.5f,-0.5f),		vec3(1.f,0.f,0.f) ,		vec2(1.f,0.f),  vec3(0.f,0.f, -1.f),
						 
		vec3(0.5f, -0.5f,-0.5f),		vec3(1.f,0.f,0.f) ,		vec2(1.f,0.f),  vec3(0.f,0.f, -1.f),
		vec3(-0.5f,-0.5f,-0.5f),		vec3(0.f,0.f,1.f),		vec2(0.f,0.f),	vec3(0.f,0.f, -1.f),
		vec3(-0.5f, 0.5f,-0.5f),		vec3(0.f, 1.f, 0.f),	vec2(0.f,1.f),	vec3(0.f,0.f, -1.f),
						 
		//right			 
		vec3(0.5f,  0.5f,-0.5f),		vec3(0.f, 1.f, 0.f),	vec2(0.f,1.f),	vec3(1.f,0.f, 0.f),
		vec3(0.5f,  0.5f,0.5f),		vec3(1.f,0.f,0.f) ,		vec2(1.f,1.f),	vec3(1.f,0.f, 0.f),
		vec3(0.5f,- 0.5f,0.5f),		vec3(1.f,0.f,0.f) ,		vec2(1.f,0.f),  vec3(1.f,0.f, 0.f),
					
		vec3(0.5f,- 0.5f,0.5f),		vec3(1.f,0.f,0.f) ,		vec2(1.f,0.f),  vec3(1.f,0.f, 0.f),
		vec3(0.5f,- 0.5f,-0.5f),		vec3(0.f,0.f,1.f),		vec2(0.f,0.f),	vec3(1.f,0.f, 0.f),
		vec3(0.5f,  0.5f,-0.5f),		vec3(0.f, 1.f, 0.f),	vec2(0.f,1.f),	vec3(1.f,0.f, 0.f),
					
		//bottom
		vec3(0.5f,- 0.5f,0.5f),		vec3(0.f, 1.f, 0.f),	vec2(1.f,1.f),	vec3(0.f,-1.f, 0.f),
		vec3(-0.5f,-0.5f,0.5f),		vec3(0.f, 1.f, 0.f),	vec2(0.f,1.f),	vec3(0.f,-1.f, 0.f),
		vec3(-0.5f,-0.5f,-0.5f),		vec3(0.f, 1.f, 0.f),	vec2(0.f,0.f),	vec3(0.f,-1.f, 0.f),
																	 	 
		vec3(-0.5f,-0.5f,-0.5f),		vec3(0.f, 1.f, 0.f),	vec2(0.f,0.f),	vec3(0.f,-1.f, 0.f),
		vec3(0.5f,- 0.5f,-0.5f),		vec3(0.f, 1.f, 0.f),	vec2(1.f,0.f),	vec3(0.f,-1.f, 0.f),
		vec3(0.5f,- 0.5f,0.5f),		vec3(0.f, 1.f, 0.f),	vec2(1.f,1.f),	vec3(0.f,-1.f, 0.f),
					
		//top		
		vec3(0.5f,  0.5f,-0.5f),		vec3(0.f, 1.f, 0.f),	vec2(1.f,0.f),	vec3(0.f,1.f, 0.f),
		vec3(-0.5f, 0.5f,-0.5f),		vec3(0.f, 1.f, 0.f),	vec2(0.f,0.f),	vec3(0.f,1.f, 0.f),
		vec3(-0.5f, 0.5f,0.5f),		vec3(0.f, 1.f, 0.f),	vec2(0.f,1.f),	vec3(0.f,1.f, 0.f),
					
		vec3(-0.5f, 0.5f,0.5f),		vec3(0.f, 1.f, 0.f),	vec2(0.f,1.f),	vec3(0.f,1.f, 0.f),
		vec3(0.5f,  0.5f,0.5f),		vec3(0.f, 1.f, 0.f),	vec2(1.f,1.f),	vec3(0.f,1.f, 0.f),
		vec3(0.5f,  0.5f,-0.5f),		vec3(0.f, 1.f, 0.f),	vec2(1.f,0.f),	vec3(0.f,1.f, 0.f)
	};

	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

	this->Set(vertices, nrOfVertices, nullptr, 0);
}
