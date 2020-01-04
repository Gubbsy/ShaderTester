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

	float ambMultiplier = 1;
	float diffMultiplier = 1;
	float specMultiplier = 1;

	ShaderManager();
	void BindLighting();
	void SetLightPositon();
	void InitialiseShader(std::string vertShader, std::string fragShader);

public:
	void SwapShader();
	static ShaderManager* getInstance();
	void SetModels(glm::mat4 mv, glm::mat4 projection);
	void MoveLightX(float movement);
	void MoveLightY(float movement);
	void ChangeAmbient(float amount);
	void ChangeDiffuse(float amount);
	void ChangeSpecular(float amount);
	void SetMtlLighting(glm::vec3 amb, glm::vec3 diff , glm::vec3 spec);
	void PrintCurrentLightingValues();
	GLuint& getCurrentShader();
};

