#pragma once
#include<stdio.h>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

class GLWindow
{
public:
	GLWindow();
	GLWindow(GLint windowWidow, GLint windowHeight);
	int initialize();

	inline GLfloat getBufferWidth() { return bufferWidth; }
	inline GLfloat getBufferHeight() { return bufferHeight; }

	inline bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	inline bool* getKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();

	inline void swapBuffers() { glfwSwapBuffers(mainWindow); }
	~GLWindow();

private:
	GLFWwindow* mainWindow;
	GLint width, height;
	GLint bufferWidth = 0, bufferHeight = 0;

	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

