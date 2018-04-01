#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "Shader.h"
#include "Input.h"

#include <GLFW\glfw3.h>

class SimpleRenderer :
	public Renderer
{
public:
	SimpleRenderer(float3 ulim, float3 llim) : m_ulim(ulim), m_llim(llim) { init();  };
	~SimpleRenderer();

	void render(uint pos, int m_nparticle);
private:

	void init();
	void __binding();
	void __render();
	void __processInput();

	/* event callback */
	void __window_size_callback(GLFWwindow* window, int width, int height);
	void __mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
	void __mouse_button_callback(GLFWwindow* w, int button, int action, int mods);
	void __mouse_scroll_callback(GLFWwindow* w, float dx, float dy);

	int m_width, m_height;
	int m_nparticle;
	/* Nsight debugging cannot work without a vao */
	uint d_vao, d_bbox_vao, d_bbox_vbo;
	/* particle position vbo */
	uint d_pos;
	/* bounding box */
	float3 m_llim, m_ulim;

	/* Renderer states */
	Camera *m_camera;

	Shader *m_shader;

	GLFWwindow *m_window;
	Input *m_input;
};
