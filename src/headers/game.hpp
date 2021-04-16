#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext.hpp>

#include "shader.hpp"
#include "render.hpp"
#include "resources.hpp"

struct Vertex {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

class Game
{
private:
	GLint ref_height, ref_width;
	Vertex x1, x2, x3;
public:
	~Game();
	Game(
		GLint s_height,
		GLint s_width,
		Vertex s_x1,
		Vertex s_x2,
		Vertex s_x3
	) {
		this->ref_height = s_height;
		this->ref_width = s_width;
		this->x1 = s_x1;
		this->x2 = s_x2;
		this->x3 = s_x3;
	};

	void events(
		GLFWwindow *window,
		bool &ex1,
		bool &ex2,
		bool &ex4,
		bool &ex5
	);
	void projection(
		bool aspect_correction = true,
		bool ex1 = false,
		bool ex2 = false
	);
	void transformations(bool enabled = false);
	void init();
	void build();

	Render *get_render();
	Shader get_shader();
};

#endif // __GAME_HPP__
