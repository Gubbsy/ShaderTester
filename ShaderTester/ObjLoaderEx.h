#pragma once
#include <exception>
#include <GL\glew.h>


class ObjLoaderEx : public std::exception
{
private:
	const GLchar * file;
public:
	ObjLoaderEx(const char* _file);
	const char* getFile();
};


