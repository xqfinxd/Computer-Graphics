#include "windows.h"
#include <GL/glut.h>
void init()
{
	glClearColor(0.0,0.0,0.0,0.0);

}

void ChangeSize(GLsizei w,GLsizei h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(w<=h)
		glOrtho(-20.0,20.0,-20.0*(GLfloat)h/(GLfloat)w,20.0*(GLfloat)h/(GLfloat)w,-50.0,50.0);
	else
		glOrtho(-20.0*(GLfloat)h/(GLfloat)w,20.0*(GLfloat)h/(GLfloat)w,-20.0,20.0,-50.0,50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void DrawColors()
{
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-10.0, -10.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(10.0, 10.0);
    glEnd();
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	DrawColors();
	glFlush();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(100,100);
	glutInitWindowPosition(0,0);

	glutCreateWindow("Colors");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
	return 0;
}
