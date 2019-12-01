#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define _USE_MATH_DEFINES

#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

const int width_window = 640;
const int height_window = 480;

double circle_center_x = 0.0;
double circle_center_y = 0.0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		circle_center_x += 0.05;
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		circle_center_x -= 0.05;
	}
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	std::cout << xpos << " " << ypos << std::endl;
}


int main() {
	GLFWwindow *window = nullptr;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(width_window, height_window, "hello glfw", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	// callbacks here
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	glfwMakeContextCurrent(window);
	glClearColor(0.5, 0.5, 0.5, 1);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	const double aspect_ratio = (double)width / height; // 1.66
	glOrtho(-1, 1, -1.0 / aspect_ratio, 1.0 / aspect_ratio, -1.0, 1.0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//TODO: draw here
		glBegin(GL_TRIANGLE_FAN);

		//glColor3f(1.0, 0.0, 0.0);
		//glVertex3f(0.0, 0.0, 0.0);
		//glColor3f(0.0, 1.0, 0.0);
		//glVertex3f(0.5, 0.0, 0.0);
		//glColor3f(0.0, 0.0, 1.0);
		//glVertex3f(0.25, 0.5, 0.0);

		// center of polygonized circle
		glVertex2f(circle_center_x, circle_center_y);

		const int num_triangles = 1000;
		const double dtheta = 2.0 * M_PI / (double)num_triangles;
		const double radius = 0.5;

		double theta = 0.0;
		for (int i = 0; i <= num_triangles; i++, theta += dtheta) {
			const double x = radius * cos(theta) + circle_center_x;
			const double y = radius * sin(theta) + circle_center_y;
			glVertex2f(x, y);
		}

		glEnd();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	return 0;
}