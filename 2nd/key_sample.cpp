#include"windows.h" 
#include <stdlib.h>
#include <stdio.h>
#include <glut.h>
int currentMode = 0;
const int ModeNums = 4;
void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
}
void myKey( unsigned char key, int x, int y) //响应ASCII对应键，鼠标的当前x和y位置也被返回。
{
	switch(key)
	{
		case ' ': currentMode = (currentMode+1)%ModeNums;
			      glutPostRedisplay();
				  break;
		case 27:  exit(-1);
	}
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	switch(currentMode)
	{
		case 0: glPointSize(5);
				glBegin(GL_POINTS);
			    glColor3f(1.0,0.0,0.0);
				break;
		case 1: glBegin(GL_LINE_STRIP);
			    glColor3f(0.0,1.0,0.0);
			    break;
		case 2: glBegin(GL_LINE_LOOP);
			    glColor3f(0.0,0.0,1.0);
				break;
		case 3: glBegin(GL_TRIANGLES);
			    glColor3f(1.0,1.0,0.0);
				break;
	}
	glVertex2f( 3.0, 3.0 );
	glVertex2f( 8.0, 3.0 );
	glVertex2f( 5.0, 8.0 );
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
		gluOrtho2D(0.0,10.0,0.0/ratio,10.0/ratio);
	else
		gluOrtho2D(0.0*ratio,10.0*ratio,0.0,10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main()
{
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(360,360);
	glutCreateWindow("KeyboardFunc");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(myKey);  //为当前窗口设置键盘回调函数。
	
	printf("Press space to continue,press escape to exit!\n");
	glutMainLoop();
	return 0;
}
