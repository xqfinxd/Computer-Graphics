#include "windows.h"
#include <GL/glut.h>

int n = 7;

typedef struct vector3f{
    float r, g, b;
} Color3f;

Color3f gray = {0.5, 0.5, 0.5};
Color3f black = {0.0, 0.0, 0.0};
Color3f white = {1.0, 1.0, 1.0};
Color3f orange = {1.0, 0.5, 0.0};
Color3f red = {1.0, 0.0, 0.0};
Color3f green = {0.0, 1.0, 0.0};
Color3f blue = {0.0, 0.0, 1.0};
Color3f cyan = {0.0, 1.0, 1.0};
Color3f magenta = {1.0, 0.0, 1.0};
Color3f yellow = {1.0, 1.0, 0.0};

void init()
{
	glClearColor(gray.r, gray.g, gray.b, 1.0);
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
void DrawColors(int x, int y, Color3f c)
{
    glColor3f(c.r, c.g, c.b);
    int h = n/2;
    glBegin(GL_POLYGON);
    glVertex2i(x-h, y-h);
    glVertex2i(x+h, y-h);
    glVertex2i(x+h, y+h);
    glVertex2i(x-h, y+h);
    glEnd();
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	DrawColors(-n*2, -n*2, black);
	DrawColors(0, -n*2, white);
	DrawColors(n*2, -n*2, orange);
	DrawColors(-n*2, 0, red);
	DrawColors(0, 0, green);
	DrawColors(n*2, 0, blue);
	DrawColors(-n*2, n*2, cyan);
	DrawColors(0, n*2, magenta);
	DrawColors(n*2, n*2, yellow);
	glFlush();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    //scanf("%d", &n);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(200, 200);
	glutInitWindowPosition(0,0);

	glutCreateWindow("Colors");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
	return 0;
}
