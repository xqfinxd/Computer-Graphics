#include"windows.h" 
#include <glut.h>
void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	glRotatef(45.0,1.0,1.0,1.0);//绕着向量（1,1,1）所指定的轴旋转45°
	glPushMatrix();//保存矩阵状态	
	glutWireCube(10.0);

	glColor3f(0.0,0.0,1.0);
	glTranslatef(0.0,20.0,0.0); //沿y轴正方向移动20个单位
	glutWireCube(10.0);
	glPopMatrix();//恢复矩阵状态

	glColor3f(0.0,1.0,0.0);
	glScalef(2.0,1.0,2.0);  //在x和z轴放大2倍，而y轴保持原大小不变
	glutWireCube(10.0);

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
int main()
{
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow("Cube");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
	return 0;
}
