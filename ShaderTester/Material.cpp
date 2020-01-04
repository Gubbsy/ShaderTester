#include "Material.h"

void Material::SetName(string _materialName) {
	materialName = _materialName;
}

void Material::SetAmbient(vec3 _ambient) {
	ambient = _ambient;
}

void Material::setDiffuse(vec3 _diffuse) {
	diffuse = _diffuse;
}

void Material::SetSpecular(vec3 _specular) {
	specular = _specular;
}

void Material::SetSpecular(GLfloat _specularWeight) {
	specularWeight = _specularWeight;
}

void Material::SetDissolve(GLfloat _dissolve) {
	dissolve = _dissolve;
}

void Material::SetMapKD(string _mapKD) {
	mapKD = _mapKD;
}

void Material::SetMapD(string _mapD) {
	mapD = _mapD;
}

string& Material::GetMapD()
{
	return mapD;
}

string& Material::GetMapKD()
{
	return mapKD;
}

vec3& Material::GetDiffuse()
{
	return diffuse;
}

vec3& Material::GetAmbient()
{
	return ambient;
}

vec3& Material::GetSpecular()
{
	return specular;
}


