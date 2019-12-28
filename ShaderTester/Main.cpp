//////////////////////////////////////////////////////////////////////////////
//
//  SHaded Cube.cpp
//
//////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "LoadShaders.h"
#include "Util.h";
#include <glm/glm.hpp> //includes GML
#include <glm/ext/matrix_transform.hpp> // GLM: translate, rotate
#include <glm/ext/matrix_clip_space.hpp> // GLM: perspective and ortho 
#include <glm/gtc/type_ptr.hpp> // GLM: access to the value_ptr

#include <iostream>
#include <vector>
#include "Mesh.h"
#include <string>
#include "ShaderManager.h"
#include "ConsolecColours.h"



// to use this example you will need to download the header files for GLM put them into a folder which you will reference in
// properties -> VC++ Directories -> libraries

std::vector<Mesh> meshes;

void
init(void)
{
	std::vector<Vertex> cubeVertices;
	//------------------------------------Position--------------Texture----------normal--------------------colour----------
	cubeVertices.push_back(Vertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f },{ 0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ 0.5f, -0.5f, -0.5f }, { 1.0f,0.0f }, { 0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ 0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f }, { 0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ 0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f }, { 0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f }, { 0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f }, { 0.0f,  0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }));
	
	cubeVertices.push_back(Vertex({ -0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f }, { 0.0f,  0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ 0.5f, -0.5f,  0.5f }, { 1.0f,0.0f }, { 0.0f,  0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ 0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }, { 0.0f,  0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ 0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }, { 0.0f,  0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }, { 0.0f,  0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ -0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f }, { 0.0f,  0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }));
	
	cubeVertices.push_back(Vertex({ -0.5f,  0.5f,  0.5 }, { 0.0f, 0.0f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ -0.5f,  0.5f, -0.5f }, { 1.0f,0.0f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ -0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ -0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f }, { -1.0f,  0.0f,  0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }));
	
	cubeVertices.push_back(Vertex({ 0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f }, { 1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 1.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ 0.5f,  0.5f, -0.5f }, { 1.0f,0.0f }, { 1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 1.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ 0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f }, { 1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 1.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ 0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f }, { 1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 1.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ 0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f }, { 1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 1.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ 0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f }, { 1.0f,  0.0f,  0.0f }, { 1.0f, 0.0f, 1.0f, 1.0f }));
	
	cubeVertices.push_back(Vertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f }, { 0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ 0.5f, -0.5f, -0.5f }, { 1.0f,0.0f }, { 0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ 0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f }, { 0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ 0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f }, { 0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ -0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f }, { 0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f }, { 0.0f, -1.0f,  0.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }));
	
	cubeVertices.push_back(Vertex({ -0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f }, { 0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f, 1.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ 0.5f,  0.5f, -0.5f }, { 1.0f,0.0f }, { 0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f, 1.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ 0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }, { 0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f, 1.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ 0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f }, { 0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f, 1.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f }, { 0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f, 1.0f, 1.0f }));
	cubeVertices.push_back(Vertex({ -0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f }, { 0.0f,  1.0f,  0.0f }, { 0.0f, 1.0f, 1.0f, 1.0f }));

	std::vector<GLuint> cubeIndices = { 0, 1, 2,
									 3, 4, 5, 
									 
									 8, 7, 6, 
									 11, 10, 9, 
									 
									 14, 13, 12, 
									 17, 16, 15, 
		
									 18, 19, 20, 
									 21, 22, 23, 
		
									 26, 25, 24, 
									 29, 28, 27,
	
									 30, 31, 32,
									 33, 34, 35 };

	std::string cubeTexture = "";

	Mesh* cubeMesh = new Mesh(cubeVertices, cubeIndices, cubeTexture);

	meshes.push_back(*cubeMesh);
}

//----------------------------------------------------------------------------
//
// display
//
void
display(GLfloat delta)
{
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	glClearBufferfv(GL_COLOR, 0, black);
	glClear(GL_COLOR_BUFFER_BIT);

	// bind textures on corresponding texture units
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	ShaderManager* shaderManager = ShaderManager::getInstance();

	

	for (int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw();
		shaderManager->SetModels(meshes[i].GenMVModel(delta), meshes[i].GenProjModel());
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{


	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->MoveLight(5.0f);
	}

	else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->MoveLight(-5.0f);
	}

	else if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->SwapShader();
	}

	//close program
	if (key == GLFW_KEY_ESCAPE && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		exit(0);
	}
}

//----------------------------------------------------------------------------
//
// main
//
int
main(int argc, char** argv)
{
	std::cout << CYAN << "================================================================" << std::endl;
	std::cout << " ____  _               _             _____         _            "<< std::endl;
	std::cout << "/ ___|| |__   __ _  __| | ___ _ __  |_   _|__  ___| |_ ___ _ __" << std::endl;
	std::cout << "\\___ \\| ' _\\ / _` |/ _` |/ _ \\ '__|   | |/ _ \\/ __| __/ _ \\ '__|" << std::endl;
	std::cout << " ___) | | | | (_| | (_| |  __/ |      | |  __/\\__ \\ ||  __/ |   " << std::endl;
	std::cout << "|____/|_| |_|\\__,_|\\__,_|\\___|_|      |_|\\___||___/\\__\\___|_|" << std::endl;
	std::cout << "================================================================" << RESET << std::endl;

	std::cout << "This program is used to test the resulting output of fragment and vertices shaders on a given model." << std::endl;
	std::cout << "Shaders are swapped out in runtime, if the inputed shader cannot be compiled the comilation error is outputed and the default shader is reverted to." << std::endl;
	std::cout << BOLDMAGENTA << "\nA Vertex shader can have the following properties : \n - layout( location = 0 ) in vec3 vPosition \n - layout( location = 1 ) in vec4 vColour \n - layout( location = 2 ) in vec3 vNormal \n - layout (location = 3) in vec2 aTexCoord \n - uniform vec3 lightPos (Light Postion) \n - uniform vec4 ambient (Ambient Light) \n - uniform vec3 dLight (Diffuse Light) \n - uniform vec3 sLight (Specular Light) \n - uniform float sShine (Specular Shine) \n - uniform mat4 mv_matrix (Model Matrix) \n - uniform mat4 p_matrix (Projection Matrix)";
	std::cout << YELLOW << "\n\nControlls: \n ~ Q - Prompt console for shader file path input \n ~ A/D - swing light source to and fro" << RESET << std::endl;

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "Shaded Cube", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();

	init();
	glfwSetKeyCallback(window, key_callback);
	GLfloat timer= 0.0f;
	
	while (!glfwWindowShouldClose(window))
	{
		// uncomment to draw only wireframe 
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		display(timer);
		glfwSwapBuffers(window);
		glfwPollEvents();
		timer += 0.1f;
	}

	glfwDestroyWindow(window);

	glfwTerminate();
}
