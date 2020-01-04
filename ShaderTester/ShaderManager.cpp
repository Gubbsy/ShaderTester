#include "ShaderManager.h"
#include "LoadShaders.h"
#include <glm\gtc\type_ptr.hpp>
#include <iostream>
#include "glm/gtx/string_cast.hpp"
#include "Util.h"
#include "ShaderException.h"
#include "ShaderCompilationEx.h"
#include "ConsolecColours.h"


ShaderManager* ShaderManager::instance = 0;

void ShaderManager::SetModels(glm::mat4 mv, glm::mat4 projection)
{
	//Bind model view matrix to shader
	int mvLoc = glGetUniformLocation(shader, "mv_matrix");
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mv));

	//Bind projection matrix to shader
	int pLoc = glGetUniformLocation(shader, "p_matrix");
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void ShaderManager::MoveLightX(float movement)
{
	currentLightPos.x += movement;

	if (currentLightPos.x < -120.0f) {
		currentLightPos.x = -120.f;
	}

	else if (currentLightPos.x > 120.0f) {
		currentLightPos.x = 120.0f;
	}
	SetLightPositon();
}

void ShaderManager::MoveLightY(float movement)
{
	currentLightPos.y += movement;

	if (currentLightPos.y < -120.0f) {
		currentLightPos.y = -120.f;
	}

	else if (currentLightPos.y > 120.0f) {
		currentLightPos.y = 120.0f;
	}
	SetLightPositon();
}

void ShaderManager::ChangeAmbient(float amount)
{
	if(ambMultiplier > 0) {
		ambMultiplier += amount;
	}
	else {
		ambMultiplier = 0.1f;
	}
}

void ShaderManager::ChangeDiffuse(float amount)
{
	if (diffMultiplier > 0) {
		diffMultiplier += amount;
	}
	else {
		diffMultiplier = 0.1f;
	}
}

void ShaderManager::ChangeSpecular(float amount)
{
	if (specMultiplier > 0) {
		specMultiplier += amount;
	}
	else {
		specMultiplier = 0.1f;
	}
}

void ShaderManager::SetMtlLighting(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec)
{
	//Set lighting using matrial values and respective multipliers
	ambient = glm::vec4(amb, 1.0f) * ambMultiplier;
	diffuseLight = diff * diffMultiplier;
	specularLight = spec * specMultiplier;
	BindLighting();
}

void ShaderManager::PrintCurrentLightingValues()
{
	std::cout << BOLDBLUE << "\nCurrent Light Multipliers: " << std::endl;
	std::cout << BOLDBLUE << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	std::cout << BLUE << "Ambient  - " << ambMultiplier << std::endl;
	std::cout << "Diffuse  - " << diffMultiplier << std::endl;
	std::cout << "Specular - " << specMultiplier << RESET << std::endl;
}

GLuint& ShaderManager::getCurrentShader()
{
	return shader;
}

void ShaderManager::BindLighting()
{
	//Bind ambient to shader uniform
	GLuint aLoc = glGetUniformLocation(shader, "ambient");
	glUniform4fv(aLoc, 1, glm::value_ptr(ambient));

	// Bind diffuse to shader uniform
	GLuint dLightLoc = glGetUniformLocation(shader, "dLight");
	glUniform3fv(dLightLoc, 1, glm::value_ptr(diffuseLight));

	// Bind specular light and shine to shader uniform
	GLfloat shininess = 256; //128 is max value
	GLuint sLightLoc = glGetUniformLocation(shader, "sLight");
	GLuint sShineLoc = glGetUniformLocation(shader, "sShine");
	glUniform3fv(sLightLoc, 1, glm::value_ptr(specularLight));
	glUniform1fv(sShineLoc, 1, &shininess);
}

void ShaderManager::SetLightPositon()
{
	//Bind light postion to shader uniform
	GLuint dLightPosLoc = glGetUniformLocation(shader, "lightPos");
	glUniform3fv(dLightPosLoc, 1, glm::value_ptr(currentLightPos));
}

void ShaderManager::InitialiseShader(std::string vertShader, std::string fragShader)
{
	// Delete current active shader
	if (shader != NULL) {
		glDeleteShader(shader);
	}

	//Load and apply new shader
	try {
		ShaderInfo  shaders[] =
		{
			{ GL_VERTEX_SHADER, vertShader.c_str() },
			{ GL_FRAGMENT_SHADER, fragShader.c_str() },
			{ GL_NONE, NULL }
		};

		shader = LoadShaders(shaders);
		glUseProgram(shader);

		std::cout << BOLDGREEN << "\nShader Compiled!" << RESET << std::endl;
	}
	//Catch errors when loading shader and revert to default
	catch (ShaderCompilationEx& e) {
		std::cout << RED << e.getMsg() << "Reverted to default shader" << RESET << std::endl;
		InitialiseShader("media/default.vert", "media/default.frag");
	}
	// Bind lighting for new shader
	BindLighting();
	// Bind light postion for new shader
	SetLightPositon();
}

void ShaderManager::SwapShader()
{
	bool vertExists = false;
	bool fragExists = false;

	std::string vertShader;
	std::string fragShader;

	std::cout << BOLDGREEN << "\nShader Slection: " << std::endl;
	std::cout << BOLDGREEN << "---------------- " << RESET << std::endl;

	// Take user input for vert file path of shader
	while (!vertExists) {
		std::cout << GREEN<< "Please enter a valid vertext shader file path" << RESET << std::endl;
		std::cin >> vertShader;
		vertExists = Exists(vertShader);
	}
	// Take user input for frag file path of shader
	while (!fragExists) {
		std::cout << GREEN << "Please enter a fragment shader file path" << RESET << std::endl;
		std::cin >> fragShader;
		fragExists = Exists(fragShader);
	}
	
	//Initialise new shader
	InitialiseShader(vertShader, fragShader);
}

ShaderManager::ShaderManager()
{
	//Assign default values for lighting (incase non are provided)
	currentLightPos = glm::vec3(100.0f, 1.25f, 1.25f);
	ambient = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
	diffuseLight = glm::vec3(0.9f, 0.9f, 0.9f);
	specularLight = glm::vec3(0.7f);

	//Initalise default shader
	InitialiseShader("media/default.vert", "media/default.frag");
}

ShaderManager* ShaderManager::getInstance()
{

	//Singleton Accessor
	{
		if (instance == 0)
		{
			instance = new ShaderManager();
		}

		return instance;
	}
}

