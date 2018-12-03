#include "windows.h"
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>

typedef struct vertex3f {
    float x, y, z;
} Vertex3f;

Vertex3f tp = {0.0, 1.0, 0.0};
float angle = 0.0;

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,1.0,0.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(0.0,0.0,-200.0);
	glRotatef(angle,0.0,1.0,0.0);
	glTranslated(80.0, 0.0, 0.0);
	glutWireCube(45.0);
    glPopMatrix();

	glFlush();
}

void ChangeSize(GLsizei w,GLsizei h)
{
	GLfloat aspectRatio;
	if(h==0)
		h = 1;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat)w/(GLfloat)h;

	gluPerspective(60.0,aspectRatio,1.0,400.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void onRotate(int value) {
    angle += 5.0;
    glutPostRedisplay();
    glutTimerFunc(25, onRotate, 1);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow("Rotate");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
    glutTimerFunc(25, onRotate, 1);
	glutMainLoop();
	return 0;
}
