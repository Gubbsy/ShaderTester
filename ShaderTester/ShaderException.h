#pragma once
struct ShaderException
{
	const char* what() const throw ()
	{
		return "Shader Error";
	}
};