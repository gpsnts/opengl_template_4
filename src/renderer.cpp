#include "headers/renderer.hpp"

Renderer::Renderer(Shader &shader)
{
	this->shader = shader;
	this->render_data();
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &this->VAO);
}

void Renderer::render_data()
{
	GLuint VBO;
	GLfloat vertices[] = {
		// Pos    // Tex
		0.f, 1.f, 0.f, 1.f,
		1.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 0.f,

		0.f, 1.f, 0.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 0.f, 1.f, 0.f
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer::draw_texture(
	Texture &texture,
	glm::vec2 position,
	glm::vec2 size,
	GLfloat rotate,
	glm::vec3 color
)
{
	this->shader.use();
  mat4 model(1.f);
  model = glm::translate(model, glm::vec3(position, 0.0f));
  model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
  model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
  model = glm::scale(model, glm::vec3(size, 1.0f));
	this->shader.set_mat4("model", model);
  this->shader.set_vec3("spriteColor", color);
  glActiveTexture(GL_TEXTURE0);
  texture.bind();
  glBindVertexArray(this->VAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}