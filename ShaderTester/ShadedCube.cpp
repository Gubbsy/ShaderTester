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



// to use this example you will need to download the header files for GLM put them into a folder which you will reference in
// properties -> VC++ Directories -> libraries

GLuint shader;
std::vector<Mesh> meshes;
glm::vec3 currentLightPos = glm::vec3(100.0f, 75.0f, 75.0f);

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

void SetLightPos() {
	glm::vec3 lightPos = currentLightPos;
	GLuint dLightPosLoc = glGetUniformLocation(shader, "lightPos");
	glUniform3fv(dLightPosLoc, 1, glm::value_ptr(lightPos));
}

void ShaderInit(std::string vertShader, std::string fragShader) {
	ShaderInfo  shaders[] =
	{
		{ GL_VERTEX_SHADER, vertShader.c_str() },
		{ GL_FRAGMENT_SHADER, fragShader.c_str() },
		{ GL_NONE, NULL }
	};

	shader = LoadShaders(shaders);
	glUseProgram(shader);

	//
	//Configure Lighting
	//
	SetLightPos();

	// ambient light
	glm::vec4 ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	//adding the Uniform to the shader
	GLuint aLoc = glGetUniformLocation(shader, "ambient");
	glUniform4fv(aLoc, 1, glm::value_ptr(ambient));

	// light object


	// diffuse light
	glm::vec3 diffuseLight = glm::vec3(0.5f, 0.5f, 0.7f);
	GLuint dLightLoc = glGetUniformLocation(shader, "dLight");
	glUniform3fv(dLightLoc, 1, glm::value_ptr(diffuseLight));

	// specular light
	glm::vec3 specularLight = glm::vec3(0.7f);
	GLfloat shininess = 256; //128 is max value
	GLuint sLightLoc = glGetUniformLocation(shader, "sLight");
	GLuint sShineLoc = glGetUniformLocation(shader, "sShine");
	glUniform3fv(sLightLoc, 1, glm::value_ptr(specularLight));
	glUniform1fv(sShineLoc, 1, &shininess);

	//
	// Configure Model matrix
	//

	// creating the model matrix
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));


	// creating the view matrix
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));

	// creating the projection matrix
	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3, 0.1f, 20.0f);

	// Adding all matrices up to create combined matrix
	glm::mat4 mv = view * model;


	//adding the Uniform to the shader
	int mvLoc = glGetUniformLocation(shader, "mv_matrix");
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mv));
	//adding the Uniform to the shader
	int pLoc = glGetUniformLocation(shader, "p_matrix");
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(projection));

}

void ShaderSwapper() {
	bool vertExists = false;
	bool fragExists = false;

	std::string vertShader;
	std::string fragShader;

	while (!vertExists) {
		std::cout << "Please enter a valid path to your vertext shader" << std::endl;
		std::cin >> vertShader;
		vertExists = Exists(vertShader);
	}
	
	while (!fragExists) {
		std::cout << "Please enter a vald path to your fragment shader" << std::endl;
		std::cin >> fragShader;
		fragExists = Exists(fragShader);
	}
	
	ShaderInit(vertShader, fragShader);
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
	// creating the model matrix
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	model = glm::rotate(model, glm::radians(delta), glm::vec3(1.0f, 0.0f, 0.0f));


	// creating the view matrix
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));

	// creating the projection matrix
	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3, 0.1f, 20.0f);

	// Adding all matrices up to create combined matrix
	glm::mat4 mv = view * model;


	//adding the Uniform to the shader
	int mvLoc = glGetUniformLocation(shader, "mv_matrix");
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mv));
	//adding the Uniform to the shader
	int pLoc = glGetUniformLocation(shader, "p_matrix");
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(projection));

	for (int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw();
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	//WASD - Translate
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		std::cout << "W pressed" << std::endl;
		currentLightPos += glm::vec3(0.0f, 10.0f, 0.0f);
		SetLightPos();
	}

	else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		std::cout << "A pressed" << std::endl;
		currentLightPos += glm::vec3(10.0f, 0.0f, 0.0f);
		SetLightPos();
	}

	else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		std::cout << "S pressed" << std::endl;
		currentLightPos += glm::vec3(0.0f, -10.0f, 0.0f);
		SetLightPos();
	}

	else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		std::cout << "D pressed" << std::endl;
		currentLightPos += glm::vec3(-10.0f, 0.0f, 0.0f);
		SetLightPos();
	}

	//+/- - Scale
	else if (key == GLFW_KEY_KP_ADD && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		std::cout << "+ pressed" << std::endl;
	}

	else if (key == GLFW_KEY_KP_SUBTRACT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		std::cout << "- pressed" << std::endl;
	}

	else if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderSwapper();
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
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(800, 600, "Shaded Cube", NULL, NULL);

	glfwMakeContextCurrent(window);
	glewInit();

	ShaderInit("media/default.vert", "media/default.frag");
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
