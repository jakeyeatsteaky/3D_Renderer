#ifndef MESH_H
#define MESH_H
#include "GL/glew.h"
#include "VertexArray.h"
#include "Shaders.h"
#include "Texture.h"
#include <memory>

class Mesh
{
public:
	// Apply the rule of five here - potentiall pass a Vertex Array by const reference, rvalue reference, etc
	Mesh(std::weak_ptr<Shader> shaderProgram, std::weak_ptr<Texture> meshTexture, bool diff = false);

	Mesh(VertexArray&& vao, std::weak_ptr<Shader> shaderProgram) : m_vao(std::move(vao)), m_shaderProgram(shaderProgram) {}
	~Mesh() = default;
	
	void Bind();
	void Draw();
	void SetShader();
	void SetTexture();
	void SetUniforms(std::string matName);
	void SetModelMatrix(glm::mat4 trans);
	void Render();
	void Update(float time);
	void InitMesh();
	
	std::shared_ptr<Shader> GetShader();

	glm::mat4 m_modelMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projMatrix;

private:
	VertexArray m_vao;
	std::weak_ptr<Shader> m_shaderProgram;
	std::weak_ptr<Texture> m_meshTexture; 
};


#endif