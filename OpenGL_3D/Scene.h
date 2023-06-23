#pragma once
#include "Headers.h"

//Enums
enum shader_enums {
	SHADER_CORE_PROGRAM = 0
};
enum texture_enums {
	TEX_woodenceramic = 0,
	TEX_woodenwood
};
enum material_enums {
	MAT_1 = 0
};
enum mesh_enums {
	MESH_QUAD = 0
};

class Scene
{
private:
// variables
	//input for model selection
	int modelIndex;
	//window
	GLFWwindow* window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int frameBufferWidth;
	int frameBufferHeight;
	//openGL context
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;

	//delta time
	float dt;
	float curTime;
	float lastTime;

	//mouse input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	Camera camera;
	//matrices
	mat4 ViewMatrix;
	vec3 camPosition;
	vec3 worldUp;
	vec3 camFront;

	mat4 ProjectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;


	//Shaders
	vector<Shader*> shaders;
	//Textures
	vector<Texture*> textures;
	//Material
	vector<Material*>  materials;
	//Meshs
	//Models
	vector<Model*> models;
	//Lights
	vector<vec3*> lights;

// private functions
	void InitGLFW();
	void InitWindow(const char* title, bool resizable);
	void InitGLEW();//after context creation

	void InitOpenGLOptions();
	void InitMatrices();
	void InitShaders();
	void InitTextures();
	void InitMaterials();
	void InitModels();
	void InitLights();
	void InitUniforms();

	void UpdateUniforms();
// static variables

public:
	Scene(const char* title, const int WINDOW_WIDTH,
		const int WINDOW_HEIGHT,
		int GL_VERSION_MAJOR, int GL_VERSION_MINOR, bool resizable);
	~Scene();

	//Accessors
	int GetWindowShouldClose();

	//Modifiers
	void SetWindowShouldClose();

	//Functions
	void UpdateDt();
	void UpdateMouseInput();
	void UpdateKeyboardInput();
	void UpdateInput();
	void Update();
	void Render();
	//static Functions
	static void Framebuffer_Resize_Callback(GLFWwindow* window, int fbw, int fbh);
	static void UpdateInput(GLFWwindow* window, vector<Mesh*> meshes);

};

