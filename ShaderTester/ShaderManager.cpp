#include "ShaderManager.h"
#include "LoadShaders.h"
#include <glm\gtc\type_ptr.hpp>
#include <iostream>
#include "Util.h"
#include "ShaderException.h"
#include "ShaderCompilationEx.h"
#include "ConsolecColours.h"


ShaderManager* ShaderManager::instance = 0;

void ShaderManager::SetModels(glm::mat4 mv, glm::mat4 projection)
{
	//adding the Uniform to the shader
	int mvLoc = glGetUniformLocation(shader, "mv_matrix");
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mv));

	//adding the Uniform to the shader
	int pLoc = glGetUniformLocation(shader, "p_matrix");
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void ShaderManager::MoveLight(float movement)
{
	currentLightPos.x = currentLightPos.x + movement;

	if (currentLightPos.x < -40.0f) {
		currentLightPos.x = -40.f;
	}

	else if (currentLightPos.x > 120.0f) {
		currentLightPos.x = 120.0f;
	}
	SetLightPositon();
}

void ShaderManager::SetLighting()
{
	// ambient light
	glm::vec4 ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	//adding the Uniform to the shader
	GLuint aLoc = glGetUniformLocation(shader, "ambient");
	glUniform4fv(aLoc, 1, glm::value_ptr(ambient));

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
}

void ShaderManager::SetLightPositon()
{
	GLuint dLightPosLoc = glGetUniformLocation(shader, "lightPos");
	glUniform3fv(dLightPosLoc, 1, glm::value_ptr(currentLightPos));
}

void ShaderManager::InitialiseShader(std::string vertShader, std::string fragShader)
{
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
	catch (ShaderCompilationEx& e) {
		std::cout << RED << e.getMsg() << "Reverted to default shader" << RESET << std::endl;
		InitialiseShader("media/default.vert", "media/default.frag");
	}

	SetLighting();
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

	while (!vertExists) {
		std::cout << GREEN<< "Please enter a valid vertext shader file path" << RESET << std::endl;
		std::cin >> vertShader;
		vertExists = Exists(vertShader);
	}

	while (!fragExists) {
		std::cout << GREEN << "Please enter a fragment shader file path" << RESET << std::endl;
		std::cin >> fragShader;
		fragExists = Exists(fragShader);
	}

	InitialiseShader(vertShader, fragShader);
}

ShaderManager::ShaderManager()
{
	currentLightPos = glm::vec3(100.0f, 45.0f, -30.0f);
	InitialiseShader("media/default.vert", "media/default.frag");
}

ShaderManager* ShaderManager::getInstance()
{
	{
		if (instance == 0)
		{
			instance = new ShaderManager();
		}

		return instance;
	}
}

