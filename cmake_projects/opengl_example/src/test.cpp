#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

void draw() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1, -1, 0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1, -1, 0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 1, 0);
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("My first GLUT window");
		
	glutDisplayFunc(draw);

	glutMainLoop();
}
