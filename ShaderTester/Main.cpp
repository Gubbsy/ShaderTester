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
display()
{
	glClearColor(0.24, 0.24, 0.23, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	if (model != NULL) {
		model->Draw();
	}

}

void RenderModel(string path) {

	//Create obj reader and model pointer
	ObjReader* objReader = new ObjReader();
	Model* mod = nullptr;

	// Read obj file
	try {
		mod = objReader->ReadFile(path);
	}
	// Catch reading exceptions
	catch (ObjLoaderEx e) {
		SetColour(4);
		cerr << "Unable to read obj file: " << e.getFile() << ". The file you entered may be corrupted" << endl;
		SetColour(7);
	}

	//Delete previouse model if present
	if (model != nullptr) {
		model->Delete();
	} 
	// Assign newly read model
	model = mod;
}

void TakeUserInput() {

	// Take user input for model path
	string modelPath;
	cout << "Enter the relative file path to your model. \n";
	cin >> modelPath;

	//Check file exstention
	if (modelPath.length() > 3 && modelPath.substr((modelPath.length()) - 3) == "obj" && Exists(modelPath)) {
		RenderModel(modelPath);
	}
	else {
		SetColour(4);
		std::cout << "\n" << "File is unsupprted or cannot be found" << endl;
		SetColour(7);
	}
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->MoveLightX(-5.0f);
	}

	else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->MoveLightX(5.0f);
	}

	else if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->MoveLightY(5.0f);
	}

	else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->MoveLightY(-5.0f);
	}

	else if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->SwapShader();
	}

	else if (key == GLFW_KEY_E && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
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
		ShaderManager::getInstance()->ChangeAmbient(0.1f);
	}

	else if (key == GLFW_KEY_X && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->ChangeAmbient(-0.1f);
	}

	//Diffuse
	else if (key == GLFW_KEY_C && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->ChangeDiffuse(0.1f);
	}

	else if (key == GLFW_KEY_V && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->ChangeDiffuse(-0.1f);
	}

	//Specular
	else if (key == GLFW_KEY_B && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->ChangeSpecular(0.1f);
	}

	else if (key == GLFW_KEY_N && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->ChangeSpecular(-0.1f);
	}

	else if (key == GLFW_KEY_P && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ShaderManager::getInstance()->PrintCurrentLightingValues();
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
	SetColour(1);
	std::cout  << "================================================================" << std::endl;
	std::cout << " ____  _               _             _____         _            "<< std::endl;
	std::cout << "/ ___|| |__   __ _  __| | ___ _ __  |_   _|__  ___| |_ ___ _ __" << std::endl;
	std::cout << "\\___ \\| ' _\\ / _` |/ _` |/ _ \\ '__|   | |/ _ \\/ __| __/ _ \\ '__|" << std::endl;
	std::cout << " ___) | | | | (_| | (_| |  __/ |      | |  __/\\__ \\ ||  __/ |   " << std::endl;
	std::cout << "|____/|_| |_|\\__,_|\\__,_|\\___|_|      |_|\\___||___/\\__\\___|_|" << std::endl;
	std::cout << "================================================================" << std::endl;

	SetColour(15);
	std::cout << "This program is used to test the resulting output of fragment and vertices shaders on a given model." << std::endl;
	std::cout << "Shaders are and models can be swapped out in runtime, if the inputed shader/model cannot be compiled the comilation error is outputed and the default shader is reverted to." << std::endl;
	SetColour(8);
	std::cout << "\nSee the ReadMe for a list of supported shader properties and their respect types and names";
	SetColour(6);
	std::cout << "\n\nControlls: \n ~ Q - Prompt console for shader file path input \n ~ E - Prompt console for model file path input \n ~ P - Print current light multipliers \n ~ A/D - Move light source \n ~ Z/X - Increase & Decrease Ambient Light Value \n ~ C/V - Increase & Decrease Diffuse Light Value \n ~ B/N - Increase & Decrease Specular Light Value" << std::endl;

	SetColour(7);

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "Shaded Cube", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();

	init();
	glfwSetKeyCallback(window, key_callback);

	RenderModel("models/creeper/creeper.obj");
	
	while (!glfwWindowShouldClose(window))
	{
		// uncomment to draw only wireframe 
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
}
