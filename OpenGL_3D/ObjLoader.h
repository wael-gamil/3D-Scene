#pragma once
#include "libs.h"
#include "Vertex.h"

static vector<Vertex> LoadOBJ(const char* filename) {
	//vector portions
	vector<fvec3> vertexPosition;
	vector<fvec2> vertexTexcoord;
	vector<fvec3> vertexNormal;

	//face vectors
	vector<GLint> vertexPositionIndices;
	vector<GLint> vertexTexcoordIndices;
	vector<GLint> vertexNormalIndices;

	//vertex Array
	vector<Vertex> vertices;

	stringstream ss;
	fstream in_file(filename);
	string line = "";
	string prefix = "";
	vec3 temp_vec3;
	vec2 temp_vec2;
	GLint temp_glint = 0;

	if (!in_file.is_open())
		throw "ERROR::OBJLOADER::COULD_NOT_OPEN_FILE";
	
	//read one line at time
	while (getline(in_file,line)) {
		//get prefix
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "#") {}
		else if (prefix == "o") {}
		else if (prefix == "s") {}
		else if (prefix == "usemtl"){}
		else if (prefix == "v") {
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertexPosition.push_back(temp_vec3);
		}
		else if (prefix == "vt") {

			ss >> temp_vec2.x >> temp_vec2.y;
			vertexTexcoord.push_back(temp_vec2);
		}
		else if (prefix == "vn") {
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertexNormal.push_back(temp_vec3);
		}
		else if (prefix == "f") {
			int count = 0;
			while (ss >> temp_glint) {

				if (count == 0)
					vertexPositionIndices.push_back(temp_glint);
				else if (count == 1)
					vertexTexcoordIndices.push_back(temp_glint);
				else if (count == 2)
					vertexNormalIndices.push_back(temp_glint);
				
				if (ss.peek() == '/') {
					count++;
					ss.ignore(1,'/');
				}
				else if (ss.peek() == ' ') {
					count++;
					ss.ignore(1, ' ');
				}
				
				if (count > 2)
					count = 0;
			}
		}
		else{}

	}

	vertices.resize(vertexPositionIndices.size(), Vertex());

	for (size_t i = 0; i < vertices.size(); i++)
	{
		vertices[i].position = vertexPosition[vertexPositionIndices[i] - 1];
		vertices[i].texcoord = vertexTexcoord[vertexTexcoordIndices[i] - 1];
		vertices[i].normal = vertexNormal[vertexNormalIndices[i] - 1];
		vertices[i].color = vec3(1.f, 1.f, 1.f);
	}

	cout << "Nr of Vertices: " << vertices.size() << "\n";

	cout << "obj loaded success\n";
	return vertices;
}
class ObjLoader
{
private:

public:
};

