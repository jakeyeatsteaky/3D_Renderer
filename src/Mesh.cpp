#include "Mesh.h"
#include "RendererAPI.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <fstream>

Mesh::Mesh(std::weak_ptr<Shader> shaderProgram, std::weak_ptr<Texture> meshTexture):
	m_modelMatrix(glm::mat4(1.0)),
	m_viewMatrix(glm::mat4(1.0)),
	m_projMatrix(glm::mat4(1.0)),
	m_shaderProgram(shaderProgram),
	m_meshTexture(meshTexture)
{
	VertexLayout attributeLayout_3(3);

	m_vao.Bind();
	// VertexBuffer vertexBuffer(vertices, sizeof(vertices));
	// IndexBuffer indexBuffer(indices, sizeof(indices));
	// attributeLayout_3.SetLayout(0, 3, 0, 0);	// Set Layout: Position idx 0
	
	// VertexBuffer colorBuffer(colors, sizeof(colors));
	// attributeLayout_3.SetLayout(1, 3, 0, 0);	// Set Layout: Color idx 1

	// VertexBuffer texCoordBuffer(texCoords, sizeof(texCoords));
	// attributeLayout_3.SetLayout(2, 2, 0, 0);	// Set Layout: TexCoords idx 2

	// // Clear bindings (don't clear index buffer)
	// texCoordBuffer.ClearFromBinding();
	// colorBuffer.ClearFromBinding();
	// vertexBuffer.ClearFromBinding();
	m_vao.ClearFromBinding();
}

void Mesh::InitMesh()
{

}

void Mesh::Bind() {
	m_vao.Bind();
}
 
void Mesh::SetShader()
{
	std::shared_ptr<Shader> shadProg = m_shaderProgram.lock();
	if(shadProg){
		shadProg->UseProgram();
	}
}

void Mesh::SetTexture()
{
	
	std::shared_ptr<Texture> tex = m_meshTexture.lock();
	if(tex)
		tex->Bind();
}

void Mesh::Draw()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Mesh::Render()
{
	SetShader();
	SetTexture();
	Bind();
	Draw();
}

void Mesh::Update(float time)
{
	m_modelMatrix = glm::mat4(1.0f);
	m_viewMatrix = glm::mat4(1.0f);
	m_projMatrix = glm::mat4(1.0f);
	
	m_modelMatrix = glm::rotate(m_modelMatrix, time * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)); 
	m_viewMatrix  = glm::translate(m_viewMatrix, glm::vec3(-0.9f, -0.5f, -7.0f));
	m_projMatrix  = glm::perspective(glm::radians(45.0f), (float)Renderer::WindowWidth / (float)Renderer::WindowHeight, 0.1f, 100.0f);
	
	GetShader()->setMat4Uniform("model", m_modelMatrix);
	GetShader()->setMat4Uniform("view", m_viewMatrix);
	GetShader()->setMat4Uniform("projection", m_projMatrix);
}

void Mesh::SetUniforms(std::string matName)
{
	std::shared_ptr<Shader> shader = m_shaderProgram.lock();
	if(shader)
	{
		shader->setMat4Uniform(matName, m_modelMatrix);
	}
}

void Mesh::SetModelMatrix(glm::mat4 trans)
{
	m_modelMatrix = trans;
}

std::shared_ptr<Shader> Mesh::GetShader()
{
	std::shared_ptr<Shader> shader = m_shaderProgram.lock();
	if(shader)
		return shader;
	std::cout << "ERROR: Could Not return Shader Program" << std::endl;
	return nullptr;

}
