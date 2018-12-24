#include"windows.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

int mouseCount = 0;
int points[32][2] = {};

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
}
void onClick( int button, int state, int x, int y) //响应ASCII对应键，鼠标的当前x和y位置也被返回。
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        points[mouseCount][0] = x/360.0*100 - 50;
        points[mouseCount][1] = 50 - y/360.0*100;
        printf("CLICKED:%d, %d\n", points[mouseCount][0], points[mouseCount][1]);
        mouseCount++;
        glutPostRedisplay();
    }
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int flag = GL_POLYGON;
	if(mouseCount < 2)
    {
        flag = GL_POINTS;
    }
    else if(mouseCount == 2)
    {
        flag = GL_LINE_STRIP;
    }
    else
    {
        flag = GL_POLYGON;
    }
	glBegin(flag);
	glColor3f(0.0, 0.0, 1.0);
    for(int i = 0; i < mouseCount; i++)
    {
        glVertex2i(points[i][0], points[i][1]);
    }
	glEnd();
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
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(360,360);
	glutCreateWindow("MouseFunc");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(onClick);

	glutMainLoop();
	return 0;
}
