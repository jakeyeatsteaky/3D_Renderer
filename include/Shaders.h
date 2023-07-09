#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void UseProgram() const;
	unsigned int getID() const { return ID; }
	

	void setBoolUniform(const std::string& name, bool value) const;
	void setIntUniform(const std::string& name, int value) const;
	void setFloatUniform(const std::string& name, float value) const;
	void setMat4Uniform(const std::string& name, const glm::mat4& mat) const;

private:
	unsigned int ID;
};


#endif

