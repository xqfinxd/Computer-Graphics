#include "windows.h"
#include <GL/glut.h>

typedef struct vertex2f {
    float x, y;
} Vertex2f;

Vertex2f tp = {0.0, 0.0};

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
	glTranslated(tp.x,tp.y,-200.0);
	glRotatef(45.0,1.0,1.0,1.0);
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

void onTransform(int value) {
    tp.x += 1;
    tp.y += 1;
    glutPostRedisplay();
    glutTimerFunc(25, onTransform, 1);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow("Transform");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
    glutTimerFunc(25, onTransform, 1);
	glutMainLoop();
	return 0;
}
