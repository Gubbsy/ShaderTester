#pragma once
#include <GL\glew.h>
#include <string>
#include <glm\ext\vector_float3.hpp>
#include <glm\ext\vector_float4.hpp>
#include <glm/glm.hpp> //includes GML
#include <glm/ext/matrix_transform.hpp> // GLM: translate, rotate
#include <glm/ext/matrix_clip_space.hpp> // GLM: perspective and ortho 

class ShaderManager
{
private:
	static ShaderManager* instance;

	GLuint shader;
	glm::vec3 currentLightPos; 

	glm::vec4 ambient;
	glm::vec3 diffuseLight;
	glm::vec3 specularLight;

	ShaderManager();
	void SetLighting();
	void SetLightPositon();
	void InitialiseShader(std::string vertShader, std::string fragShader);

public:
	void SwapShader();
	static ShaderManager* getInstance();
	void SetModels(glm::mat4 mv, glm::mat4 projection);
	void MoveLight(float movement);
	void ChangeAmbient(glm::vec4 amount);
	void ChangeDiffuse(glm::vec3 amount);
	void ChangeSpecular(glm::vec3 amount);
	GLuint& getCurrentShader();
};

