#pragma once
#include "libs.h"
#include "Vertex.h"

class Primitive
{
private:
	vector<Vertex> vertices;
	vector<GLuint> indices;
public:
	Primitive();
	~Primitive();

	void Set(const Vertex* vertices, const unsigned nrOfVertices, const GLuint* indices, const unsigned nrOfIndices);

	Vertex* GetVertices();
	GLuint* GetIndices();
	const unsigned GetNrOfVertices();
	const unsigned GetNrOfIndices();
};

class Quad : public Primitive {
public:
	Quad();
};
class Triangle : public Primitive {
public:
	Triangle();
};
class Cube : public Primitive {
public:
	Cube();
};
