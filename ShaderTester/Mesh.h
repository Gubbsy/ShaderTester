#pragma once

#include <GL\glew.h>
#include <vector>
#include <filesystem>
#include <iostream>
#include "Vertex.h"


#define BUFFER_OFFSET(offset) ((void*)(offset))

class Mesh
{
private:
	enum Attrib_IDs { vPosition = 0, cPosition = 1, tPosition = 2, nPosition = 3 };

	GLuint texture1;
	GLuint shader;

	std::vector<Vertex> vertexes;
	std::vector<GLuint> indices;
	GLuint VAO;
	GLuint VBO;
	GLuint indicesEBO;
	std::string texturePath;

	void BindIndices();
	void BindVertices();
	void ApplyTexture();

public:
	Mesh(std::vector<Vertex>& _vertexes, std::vector<GLuint>& _indices, std::string& tetxurePath);
	void PassToShader();
	void Draw(GLuint& shaderProgram);
	void Remove();
	bool exists(const std::string& name);
};

