#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

typedef struct Vertex2f {
	int x, y;
} Vertex2f;
typedef struct Vertex3f {
	int x, y, z;
} Vertex3f;

int display_mode = 0;
unsigned int gem_type = GL_LINES;
Vertex2f triangle[3] = 
{{ 25.0f, 15.0f },
 { 15.0f, 25.0f },
 { 0.0f, -10.0f }};

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
}
void myKey( unsigned char key, int x, int y)
{
	switch(key)
	{
		case ' ':
			display_mode++;
			glutPostRedisplay();
			break;
		case 27:  exit(-1);
	}
}
void RenderScene()
{
	Vertex3f tran_var = { 10.0f, 15.0f, 0.0f };
	Vertex3f scale_var = { 1.5f, 2.0f, 0.0f };
	Vertex2f midpoint = { (triangle[0].x+triangle[1].x+triangle[2].x)/3,
		(triangle[0].y+triangle[1].y+triangle[2].y)/3 };
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	switch(display_mode)
	{
		case 0:
			gem_type = GL_POINTS;
			break;
		case 1:
			gem_type = GL_LINE_STRIP;
			break;
		case 2:
			gem_type = GL_TRIANGLES;
			break;
		case 3:
			glTranslatef(tran_var.x, tran_var.y, tran_var.z);
			break;
		case 4:
//			glTranslatef(tran_var.x, tran_var.y, tran_var.z);
			glScalef(scale_var.x, scale_var.y, scale_var.z);
			break;
		default:
			glTranslatef(midpoint.x, midpoint.y, 0.0f);
			glRotatef(10.0f*(display_mode-5), 0.0f, 0.0f, 1.0f);
			glTranslatef(-midpoint.x, -midpoint.y, 0.0f);
//			glTranslatef(tran_var.x, tran_var.y, tran_var.z);
//			glScalef(scale_var.x, scale_var.y, scale_var.z);
			break;
	}
	glBegin(gem_type);
	glVertex2f(triangle[0].x, triangle[0].y);
	glVertex2f(triangle[1].x, triangle[1].y);
	glVertex2f(triangle[2].x, triangle[2].y);
	glEnd();
	glFlush();
}
void ChangeSize(GLsizei w,GLsizei h)
{
	float ratio;
	if(h==0)
		h = 1;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ratio = (float)w/(float)h;
	if(w<=h)
		gluOrtho2D(-50.0,50.0,50.0/ratio,-50.0/ratio);
	else
		gluOrtho2D(-50.0*ratio,50.0*ratio,50.0,-50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(360,360);
	glutCreateWindow("KeyboardFunc");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(myKey);
	
	glutMainLoop();
	return 0;
}
