#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define _USE_MATH_DEFINES

#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

#include <vector>

const int width_window = 640;
const int height_window = 480;

class Vector3 {
public:
	union {
		struct { float x_, y_, z_; };
		struct { float r_, g_, b_; };
		float v_[3];
	};

	Vector3(const float& _x, const float& _y, const float& _z)
		:x_(_x), y_(_y), z_(_z) 
	{}
};

int main() {
	std::cout << "Size of Vector3: " << sizeof(Vector3) << std::endl;

	GLFWwindow *window = nullptr;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(width_window, height_window, "opengl week3", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	// callbacks here


	glfwMakeContextCurrent(window);
	printf("%s \n", glGetString(GL_VERSION));

	glClearColor(0.5, 0.5, 0.5, 1);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	const double aspect_ratio = (double)width / height; // 1.66
	glOrtho(-1, 1, -1.0 / aspect_ratio, 1.0 / aspect_ratio, -1.0, 1.0);
	
	// method 1
	const float color[3][3] = {
		{1.0,0.0,0.0},
		{0.0,1.0,0.0},
		{0.0,0.0,1.0} 
	};
	const float first_vertex[3][3] = {
		{0.0, 0.0, 0.0},    // first vectex
		{0.5, 0.0, 0.0},    // second vertex 
		{0.25, 0.5, 0.0} // third vertex
	};

	// method 2
	Vector3 vcolor[3] = {
		Vector3(1,0,0),
		Vector3(0,1,0),
		Vector3(0,0,1)
	};
	Vector3 vvertex[3] = {
		Vector3(0.0,0.0,0.0),
		Vector3(0.5,0.0,0.0),
		Vector3(0.25,0.5,0.0)
	};

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//TODO: draw here (old style)
		//glBegin(GL_TRIANGLES);
		//int num_vertices = 3;
		//for (int v = 0; v < num_vertices; v++) {
		//	// method 1
		//	//glColor3fv(color[v]);
		//	//glVertex3fv(first_vertex[v]);

		//	// method 2
		//	glColor3fv(vcolor[v].v_);
		//	glVertex3fv(vvertex[v].v_);
		//}
		//glEnd();

		// Send data to GPU at once. (new style)
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
			
		glColorPointer(3, GL_FLOAT, 0, vcolor);
		glVertexPointer(3, GL_FLOAT, 0, vvertex);
	
		glDrawArrays(GL_TRIANGLES, 0, 9);
		
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	return 0;
}