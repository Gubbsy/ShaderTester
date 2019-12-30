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
#include "Model.h"
#include <string>
#include "ShaderManager.h"
#include "ConsolecColours.h"
#include "ObjReader.h"
#include "ObjLoaderEx.h"


// to use this example you will need to download the header files for GLM put them into a folder which you will reference in
// properties -> VC++ Directories -> libraries

Model* model = nullptr;

void
init(void)
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
}

//----------------------------------------------------------------------------
//
// display
//
void
display(GLfloat delta)
{
	glClearColor(0.24, 0.24, 0.23, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	if (model != NULL) {
		model->Draw();
	}

}

void RenderModel(string path) {

	ObjReader* objReader = new ObjReader();
	Model* mod = nullptr;

	try {
		mod = objReader->ReadFile(path);
	}
	catch (ObjLoaderEx e) {
		cerr << RED << "Unable to read obj file: " << e.getFile() << ". The file you entered may be corrupted" << RESET << endl;
	}

	if (model != nullptr) {
		model->Delete();
	} 
	model = mod;
}

void TakeUserInput() {

	string modelPath;
	cout << "Enter the relative file path to your model. \n";
	cin >> modelPath;

	string extension = modelPath.substr((modelPath.length()) - 3);

	if (extension == "obj" && Exists(modelPath)) {
		RenderModel(modelPath);
	}
	else {
		std::cout << RED << "File is unsupprted is unsupported or cannot be found" << RESET << endl;
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

	else if (key == GLFW_KEY_M && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		TakeUserInput();
	}

	//+/- - Scale
	else if (key == GLFW_KEY_KP_ADD && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		model->Scale(glm::vec3(0.3f, 0.3f, 0.3f));
	}

	else if (key == GLFW_KEY_KP_SUBTRACT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		model->Scale(glm::vec3(-0.3f, -0.3f, -0.3f));
	}

	//Arrow keys - Rotate
	else if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		model->Rotate(glm::vec3(0.0f, 10.0f, 0.0f));
	}

	else if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		model->Rotate(glm::vec3(0.0f, -10.0f, 0.0f));
	}

	else if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		model->Rotate(glm::vec3(-10.0f, 0.0f, 0.0f));
	}

	else if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		model->Rotate(glm::vec3(10.0f, 0.0f, 0.0f));
	}

	//Alter Lighting Values
	//Ambient
	else if (key == GLFW_KEY_Z && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->ChangeAmbient(glm::vec4(0.1f, 0.1f, 0.1f, 0.0f));
	}

	else if (key == GLFW_KEY_X && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->ChangeAmbient(glm::vec4(-0.1f, -0.1f, -0.1f, 0.0f));
	}

	//Diffuse
	else if (key == GLFW_KEY_C && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->ChangeDiffuse(glm::vec3(0.1f));
	}

	else if (key == GLFW_KEY_V && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->ChangeDiffuse(glm::vec3(-0.1f));
	}

	//Specular
	else if (key == GLFW_KEY_B && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->ChangeSpecular(glm::vec3(0.1f));
	}

	else if (key == GLFW_KEY_N && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->ChangeSpecular(glm::vec3(-0.1f));
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
	std::cout << BOLDMAGENTA << "\nA Vertex shader can have the following properties : \n - layout( location = 0 ) in vec3 vPosition \n - layout( location = 1 ) in vec4 vColour \n - layout( location = 2 ) in vec2 aTexCoord \n - layout (location = 3) in vec3 vNormal \n - uniform vec3 lightPos (Light Postion) \n - uniform vec4 ambient (Ambient Light) \n - uniform vec3 dLight (Diffuse Light) \n - uniform vec3 sLight (Specular Light) \n - uniform float sShine (Specular Shine) \n - uniform mat4 mv_matrix (Model Matrix) \n - uniform mat4 p_matrix (Projection Matrix)";
	std::cout << YELLOW << "\n\nControlls: \n ~ Q - Prompt console for shader file path input \n ~ A/D - swing light source to and fro" << RESET << std::endl;

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "Shaded Cube", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();

	init();
	glfwSetKeyCallback(window, key_callback);
	GLfloat timer= 0.0f;

	RenderModel("models/creeper/creeper.obj");
	
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
