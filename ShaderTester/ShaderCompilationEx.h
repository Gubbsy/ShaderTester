#pragma once
#include <exception>
#include <GL\glew.h>

class ShaderCompilationEx : public std::exception
{
private:
	const GLchar* msg;
public:
	ShaderCompilationEx(const char* _log);
	const GLchar * getMsg();
};

