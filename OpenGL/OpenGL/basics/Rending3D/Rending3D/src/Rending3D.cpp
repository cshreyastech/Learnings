#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "include/Mesh.h"
#include "include/Shader.h"
#include "include/GLWindow.h"
#include "include/Camera.h"
#include "include/Texture.h"

//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_glfw_gl3.h"

const float toRadians = 3.14159265f / 180.0f;

GLWindow* mainWindow;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
Camera* camera;

Texture* brickTexture;
Texture* dirtTexture;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "res/shaders/render3D.vert.glsl";
// Fragment Shader
static const char* fShader = "res/shaders/render3D.frag.glsl";
void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
	//	    x,     y,    z,     u,    v, 
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		 0.0f, -1.0f, 1.0f,  0.5f, 0.0f,
		 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,  0.5f, 1.0f
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 20, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 20, 12);
	meshList.push_back(obj2);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(shader1);
}

int main()
{
	mainWindow = new GLWindow(800, 600);
	mainWindow->initialize();

	CreateObjects();
	CreateShaders();

	camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.02f);

	//http://texturer.com/set3299/
	brickTexture = new Texture("res/textures/brick.png");
	brickTexture->LoadTexture();

	dirtTexture = new Texture("res/textures/dirt.png");
	dirtTexture->LoadTexture();

	GLuint uniformModel = 0, uniformProjection = 0, uniformView = 0;

	glm::mat4 projection = glm::perspective(45.0f, mainWindow->getBufferWidth() / mainWindow->getBufferHeight(), 0.1f, 100.0f);
	while (!mainWindow->getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		//Get Handle user input events
		glfwPollEvents();

		camera->keyControl(mainWindow->getKeys(), deltaTime);
		camera->mouseControl(mainWindow->getXChange(), mainWindow->getYChange());
		//Clear Window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shaderList[0]->UseShader();
		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetProjectionLocation();
		uniformView = shaderList[0]->GetViewLocation();

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));
		brickTexture->UseTexture();
		meshList[0]->RenderMesh();

		// Render Second object
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture->UseTexture();
		meshList[1]->RenderMesh();

		// Unassign shader
		glUseProgram(0);
		mainWindow->swapBuffers();
	}
	return 0;
}