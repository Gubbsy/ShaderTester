//////////////////////////////////////////////////////////////////////////////
//
//  SHaded Cube.cpp
//
//////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "LoadShaders.h"
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

void
init(void)
{
	//
    // configuring lighting
    //

	// setting up the cube

	//

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

	std::string cubeTexture = "media/textures/awesomeface.png";

	Mesh* cubeMesh = new Mesh(cubeVertices, cubeIndices, cubeTexture);

	meshes.push_back(*cubeMesh);
}

void ShaderInit() {
	ShaderInfo  shaders[] =
	{
		{ GL_VERTEX_SHADER, "media/triangles.vert" },
		{ GL_FRAGMENT_SHADER, "media/triangles.frag" },
		{ GL_NONE, NULL }
	};

	shader = LoadShaders(shaders);
	glUseProgram(shader);

	//
	//Configure Lighting
	//

	// ambient light
	glm::vec4 ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	//adding the Uniform to the shader
	GLuint aLoc = glGetUniformLocation(shader, "ambient");
	glUniform4fv(aLoc, 1, glm::value_ptr(ambient));

	// light object
	glm::vec3 lightPos = glm::vec3(100.0f, 25.0f, 100.0f);
	GLuint dLightPosLoc = glGetUniformLocation(shader, "lightPos");
	glUniform3fv(dLightPosLoc, 1, glm::value_ptr(lightPos));


	// diffuse light
	glm::vec3 diffuseLight = glm::vec3(0.5f, 0.2f, 0.7f);
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
		meshes[i].Draw(shader);
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

	ShaderInit();
	init();
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
