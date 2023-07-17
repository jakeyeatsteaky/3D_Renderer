#include "Mesh.h"
#include "RendererAPI.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <fstream>

Mesh::Mesh(
		std::weak_ptr<VertexBuffer> vertexBuffer,
		std::weak_ptr<IndexBuffer> indexBuffer,
		std::weak_ptr<Shader> shaderProgram, 
		std::weak_ptr<Texture> meshTexture, 
		unsigned numAttributes):

	m_modelMatrix(glm::mat4(1.0)),
	m_viewMatrix(glm::mat4(1.0)),
	m_projMatrix(glm::mat4(1.0)),
	m_vbo(vertexBuffer),
	m_ibo(indexBuffer),
	m_shaderProgram(shaderProgram),
	m_meshTexture(meshTexture)
{
	VertexLayout attributeLayout_3(numAttributes);
	std::shared_ptr<VertexBuffer> vbo = m_vbo.lock();
	std::shared_ptr<IndexBuffer> ibo = m_ibo.lock();

	m_vao.Bind();
	if(vbo && ibo){ 
		vbo->Bind();
		ibo->Bind();
	} else {
		std::cout << "ERROR::Unable to bind Vertex/Index buffers\n";
	}

	attributeLayout_3.SetLayout(0, 3, 8, 0);	// Set Layout: Position idx 0
	attributeLayout_3.SetLayout(1, 3, 8, 3);	// Set Layout: Color idx 1
	attributeLayout_3.SetLayout(2, 2, 8, 6);	// Set Layout: TexCoords idx 2

	vbo->ClearFromBinding();
	// dont clear the index buffer
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
