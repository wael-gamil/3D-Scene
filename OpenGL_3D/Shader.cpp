#include "Shader.h"

Shader::Shader(const int versionMajor, const int versionMinor, 
	char* vertexFile, char* fragmentFile)
	: versionMajor(versionMajor), versionMinor(versionMinor)
{
	GLuint vertexShader = 0;
	GLuint fragmentShader = 0;
	
	vertexShader = LoadShader(GL_VERTEX_SHADER, vertexFile);
	fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentFile);

	this->LinkProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(this->id);
}

void Shader::Use()
{
	glUseProgram(this->id);
}

void Shader::UnUse()
{
	glUseProgram(0);
}

void Shader::SetVec3f(fvec3 value, const GLchar* name)
{
	this->Use();
	
	glUniform3fv(glGetUniformLocation(this->id, name),1, value_ptr(value));

	this->UnUse();
}

void Shader::Set1i(GLuint value, const GLchar* name)
{
	this->Use();

	glUniform1i(glGetUniformLocation(this->id, name), value);

	this->UnUse();
}

void Shader::SetMat4fv(mat4 value, const GLchar* name)
{
	this->Use();

	glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, value_ptr(value));

	this->UnUse();
}

void Shader::Set1f(GLfloat value, const GLchar* name)
{
	this->Use();

	glUniform1f(glGetUniformLocation(this->id, name), value);

	this->UnUse();
}

string Shader::LoadShaderSource(char* filename)
{
	string temp = "";
	string src = "";

	ifstream in_file;

	in_file.open(filename);

	if (in_file.is_open())
		while (getline(in_file, temp))
			src += temp + "\n";
	else {
		cout << "ERROR::SHADER::COULD_NOT_OPEN: " << filename << "\n";
	}
	in_file.close();
	//440
	string versionNr = to_string(versionMajor) + to_string(versionMinor) + "0";
	src.replace(src.find("#version"), 12, "#version " + versionNr);

    return src;
}

GLuint Shader::LoadShader(GLenum type, char* filename)
{
	bool loadSuccess = true;

	char infoLog[512];
	GLint success;

	GLuint shader = glCreateShader(type);
	string str_src = this->LoadShaderSource(filename);
	const GLchar* src = str_src.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER: " << filename << "\n";
		cout << infoLog << "\n";
		loadSuccess = false;
	}

    return shader;
}

void Shader::LinkProgram(GLuint vertexShader, GLuint fragmentShader)
{
	char infoLog[512];
	GLint success;

	this->id = glCreateProgram();

	glAttachShader(this->id, vertexShader);
	glAttachShader(this->id, fragmentShader);

	glLinkProgram(this->id);

	glGetProgramiv(this->id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->id, 1, NULL, infoLog);
		cout << "ERROR::LOADSHADER::COULD_NOT_LINK_PROGRAM\n";
		cout << infoLog << "\n";
	}

	glUseProgram(0);
}
