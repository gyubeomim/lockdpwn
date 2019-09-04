#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <cmath>
#include <thread>
#include <chrono>
#include <iostream>

const int width_window = 640;
const int height_window = 480;

int main() {
	GLFWwindow *window = nullptr;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(width_window, height_window, "hello glfw", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glClearColor(0.5, 0.5, 0.5, 1);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	//glOrtho(0, 1, 0, 1, -1.0, 1.0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//TODO: draw here
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.5, 0.0, 0.0);
		glVertex3f(0.25, 0.5, 0.0);
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