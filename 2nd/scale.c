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
	glColor3f(0.0,1.0,0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(45.0f, 1.0f, 1.0f, 1.0f);

	glutWireCube(15.0);
	glTranslatef(10.0f, 20.0f, 10.0f);
	glScalef(2.0, 1.0f, 0.5f);
	glTranslatef(10.0f, 20.0f, 10.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutWireCube(15.0f);

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
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow("Cube");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
	return 0;
}
