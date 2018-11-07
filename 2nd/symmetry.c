#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	
	glBegin(GL_LINES);
	glVertex2f(30.0f, 33.0f);
	glVertex2f(-30.0f, -27.0f);
	glEnd();
	glColor3f(0.0,1.0,0.0);
	glRectf(-10.0f, 10.0f, 5.0f, 0.0f);
	glTranslatef(0.0f, 3.0f, 0.0f);
	glRotatef(180.0f, 1.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, -3.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glRectf(-10.0f, 10.0f, 5.0f, 0.0f);

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
	if(w<=h)
		glOrtho(-50.0,50.0,-50.0/aspectRatio,50.0/aspectRatio,-50.0,50.0);
	else
		glOrtho(-50.0*aspectRatio,50.0*aspectRatio,-50.0,50.0,-50.0,50.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow("Cube");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
}
