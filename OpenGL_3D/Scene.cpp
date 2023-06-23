#include "Scene.h"

//Private functions
void Scene::InitGLFW()
{
	if (glfwInit() == GLFW_FALSE) {
		cout << "ERROR::GLFW_INIT_FAILED\n";
		glfwTerminate();
	}
}

void Scene::InitWindow(const char* title, bool resizable)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	this->window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title, NULL, NULL);

	if (this->window == nullptr) {
		cout << "ERROR::GLFW_WINDOW_FAILED\n";
		glfwTerminate();
	}
	glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);
	glfwSetFramebufferSizeCallback(this->window, Scene::Framebuffer_Resize_Callback);

	glfwMakeContextCurrent(window);
}

void Scene::InitGLEW()
{
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		cout << "ERROR::GLEW_INIT_FAILED" << endl;
		glfwTerminate();
	}
}

void Scene::InitOpenGLOptions()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Scene::InitMatrices()
{
	this->ViewMatrix = mat4(1.f);
	ViewMatrix = lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	this->ProjectionMatrix = mat4(1.f);
	ProjectionMatrix = perspective(radians(fov), static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight,
		this->nearPlane, this->farPlane);
}

void Scene::InitShaders()
{
	this->shaders.push_back(new Shader(GL_VERSION_MAJOR, GL_VERSION_MINOR, 
		(char*)"vertex_core.glsl", (char*)"fragment_core.glsl"));

}

void Scene::InitTextures()
{
	this->textures.push_back(new Texture("./blender/textures/woodenceramic_4_basecolor-1K.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("./blender/textures/1K-wood_frame_7_basecolor.png", GL_TEXTURE_2D));
}

void Scene::InitMaterials()
{
	this->materials.push_back(new Material(vec3(0.1f), vec3(1.f), vec3(3.f), 0, 1));

}

void Scene::InitModels()
{
	vector<Mesh*> meshes;
	vector<Vertex> mesh;

	// load floor
	mesh = LoadOBJ("obj/floor.obj");
	meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0, vec3(0.f)));
	this->models.push_back(new Model(vec3(0.f, 0.f, -5.f),
		this->materials[MAT_1], this->textures[TEX_woodenceramic], this->textures[TEX_woodenceramic],
		meshes));
	meshes.pop_back();

	//load table
	mesh = LoadOBJ("obj/table.obj");
	meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0, vec3(0.f)));
	this->models.push_back(new Model(vec3(1.f, 0.f, -5.f),
		this->materials[MAT_1], this->textures[TEX_woodenwood], this->textures[TEX_woodenceramic],
		meshes));

	meshes.pop_back();
	//load chairs
	for (int i = 1; i <= 6; i++) {
		string filename = "obj/chair" + to_string(i) + ".obj";
		cout << filename << endl;
		mesh = LoadOBJ(filename.c_str());
		meshes.push_back(new Mesh(mesh.data(), mesh.size(), NULL, 0, vec3(0.f)));
		this->models.push_back(new Model(vec3(0.f, 0.f, -5.f),
			this->materials[MAT_1], this->textures[TEX_woodenwood], this->textures[TEX_woodenceramic],
			meshes));
		meshes.pop_back();
	}
	
	for (auto*& i : meshes)
		delete i;

	
}

void Scene::InitLights()
{
	this->lights.push_back(new vec3(0.f, 20.f, 1.f));
}

void Scene::InitUniforms()
{

	this->shaders[SHADER_CORE_PROGRAM]->SetMat4fv(ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->SetMat4fv(ProjectionMatrix, "ProjectionMatrix");

	this->shaders[SHADER_CORE_PROGRAM]->SetVec3f(*this->lights[0], "lightPos0");
}

void Scene::UpdateUniforms()
{
	
	//update projection matrix
	glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);

	this->ViewMatrix = this->camera.getViewMatrix();

	this->shaders[SHADER_CORE_PROGRAM]->SetMat4fv(this->ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->SetVec3f(this->camera.getPosition(), "cameraPos");

	ProjectionMatrix = perspective(radians(fov),
		static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight, nearPlane, farPlane);
	this->shaders[SHADER_CORE_PROGRAM]->SetMat4fv(this->ProjectionMatrix, "ProjectionMatrix");
}

//Constructor , Destructor
Scene::Scene(const char* title, const int WINDOW_WIDTH,
	const int WINDOW_HEIGHT,
	int GL_VERSION_MAJOR, int GL_VERSION_MINOR, bool resizable)
	: WINDOW_WIDTH(WINDOW_WIDTH), WINDOW_HEIGHT(WINDOW_HEIGHT),
	GL_VERSION_MAJOR(GL_VERSION_MAJOR), GL_VERSION_MINOR(GL_VERSION_MINOR),
	camera(vec3(0.f, 20.f, -2.f), vec3(0.f, 0.f, 1.f), vec3(0.f, 1.f, 0.f))
{
	//init variables
	modelIndex = 0;

	this->window = nullptr;
	this->frameBufferWidth = WINDOW_WIDTH;
	this->frameBufferHeight = WINDOW_HEIGHT;

	this->camPosition = vec3(0.f, 0.f, 1.f);
	this->worldUp = vec3(0.f, 1.f, 0.f);
	this->camFront = vec3(0.f, 0.f, -1.f);
	
	this->dt = 0.f;
	this->curTime = 0.f;
	this->lastTime = 0.f;

	this->lastMouseX	= 0.f;
	this->lastMouseY	= 0.f;	
	this->mouseX		= 0.f;
	this->mouseY		= 0.f;
	this->mouseOffsetX	= 0.f;
	this->mouseOffsetY	= 0.f;
	this->firstMouse	= true;

	//init projection variables
	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;
	
	this->InitGLFW();
	this->InitWindow(title, resizable);
	this->InitGLEW();
	this->InitOpenGLOptions();
	this->InitMatrices();
	this->InitShaders();
	this->InitTextures();
	this->InitMaterials();
	this->InitModels();
	this->InitLights();
	this->InitUniforms();
}

Scene::~Scene()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();

	for (size_t i = 0; i < shaders.size(); i++)
		delete this->shaders[i];
	for (size_t i = 0; i < textures.size(); i++)
		delete this->textures[i];
	for (size_t i = 0; i < materials.size(); i++)
		delete this->materials[i];
	for (auto*& i : models)
		delete i;
	for (size_t i = 0; i < lights.size(); i++)
		delete this->lights[i];

}

//Accessors
int Scene::GetWindowShouldClose()
{
	return glfwWindowShouldClose(this->window);
}


//Modifiers
void Scene::SetWindowShouldClose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}



//Functions

void Scene::UpdateDt()
{
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = this->curTime;
}

void Scene::UpdateMouseInput()
{
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->firstMouse) {
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}
	
	//calculate offset
	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->mouseY - this->lastMouseY;

	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;
}

void Scene::UpdateKeyboardInput()
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		modelIndex++;

		if (modelIndex - 1 == models.size())
			modelIndex = 0;
		cout << "Model Selected: " << modelIndex << "\n";
	}
	//close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	//control camera
	if (modelIndex == 0) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			this->camera.move(dt, FORWARD);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			this->camera.move(dt, BACKWARD);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			this->camera.move(dt, LEFT);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			this->camera.move(dt, RIGHT);
	}
	//control object
	else {
		vector<Mesh*> meshes = models[modelIndex - 1]->GetMeshes();
		//forward, back , right , left
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			for (auto*& i : meshes)
				i->Move(vec3(0, 0, -0.01f));
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			for (auto*& i : meshes)
				i->Move(vec3(0, 0, 0.01f));
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			for (auto*& i : meshes)
				i->Move(vec3(0.01f, 0, 0));
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			for (auto*& i : meshes)
				i->Move(vec3(-0.01f, 0, 0));
		//up, down
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			for (auto*& i : meshes)
				i->Move(vec3(0, 0.01f, 0.f));
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			for (auto*& i : meshes)
				i->Move(vec3(0, -0.01f, 0.0f));
		//rotate around y
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
			for (auto*& i : meshes)
				i->Rotate(vec3(0, 0.1f, 0));
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
			for (auto*& i : meshes)
				i->Rotate(vec3(0, -0.1f, 0));
		//rotate around x
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
			for (auto*& i : meshes)
				i->Rotate(vec3(0.1f, 0.f, 0));
		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
			for (auto*& i : meshes)
				i->Rotate(vec3(-0.1f, 0.f, 0));
		//scale
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
			for (auto*& i : meshes)
				i->Scale(vec3(0.01f, 0.01f, 0.01f));
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
			for (auto*& i : meshes)
				i->Scale(vec3(0.01f, 0.01f, 0.01f) * vec3(-1.f));
	}
}

void Scene::UpdateInput()
{
	glfwPollEvents();
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	this->UpdateKeyboardInput();
	this->UpdateMouseInput();
	this->camera.updateInput(dt, -1, this->mouseOffsetX, this->mouseOffsetY);
}

void Scene::Update()
{
	//update  input
	this->UpdateDt();
	this->UpdateInput();
}

void Scene::Render()
{

	//clear
	glClearColor(0.f, 0.f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//update uniforms
	this->UpdateUniforms();

	//Draw
	for (auto&i : this->models)
		i->Render(this->shaders[SHADER_CORE_PROGRAM]);
	//end draw
	glfwSwapBuffers(this->window);
	glFlush();

	//reset
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


//static functions
void Scene::Framebuffer_Resize_Callback(GLFWwindow* window, int fbw, int fbh)
{
	glViewport(0, 0, fbw, fbh);
}