#include "ObjLoaderEx.h"

ObjLoaderEx::ObjLoaderEx(const char* _file)
{
	file = _file;
}

const char* ObjLoaderEx::getFile()
{
	return file;
}
