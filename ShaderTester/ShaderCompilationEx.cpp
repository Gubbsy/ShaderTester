#include "ShaderCompilationEx.h"

ShaderCompilationEx::ShaderCompilationEx(const char* _log)
{
	msg = _log;
}

const GLchar* ShaderCompilationEx::getMsg()
{
	return msg;
}
