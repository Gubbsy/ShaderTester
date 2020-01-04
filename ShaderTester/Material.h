#pragma once
#include <string>
#include <glm\ext\vector_float3.hpp>
#include <GL\glew.h>


using namespace std;
using namespace glm;

class Material
{

private:
	string materialName;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	GLfloat specularWeight;
	GLfloat dissolve;
	string mapKD;
	string mapD;
	
public:
	void SetName(string _matrialName);
	void SetAmbient(vec3 _ambient);
	void setDiffuse(vec3 _diffuse);
	void SetSpecular(vec3 _specular);
	void SetSpecular(GLfloat _specularWeight);
	void SetDissolve(GLfloat _disolve);
	void SetMapKD(string _mapKD);
	void SetMapD(string _mapD);
	
	string& GetMapD();
	string& GetMapKD();
	vec3& GetDiffuse();
	vec3& GetAmbient();
	vec3& GetSpecular();
};

