#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

typedef struct {
	int x, y;
} Point;

void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int MidpointCircle(int radius, Point pix[]) {
	int x = 0;
	int y = radius;
	int d = (int)1.25 - radius;
	int num = 0;
	while(y > x) {	//first area
		pix[num].x = x;
		pix[num].y = y;
		if(d < 0) {
			d += (x<<1) + 3;	//d += 2 * x + 3
		} else {
			d += ((x-y)<<1) + 5;	//d += 2 * (x - y) + 5
			--y;
		}
		++x;
		++num;
	}
	int count = num;
	for(int i = 0; i < count; ++i) {	//second area
		pix[num].x = pix[i].y;
		pix[num].y = pix[i].x;
		++num;
	}
	count = num;
	for(int i = 0; i < count; ++i) {	//third and forth area
		pix[num].x = pix[i].x;
		pix[num].y = -pix[i].y;
		++num;
	}
	count = num;
	for(int i = 0; i < count; ++i) {	//5th-8th area
		pix[num].x = -pix[i].x;
		pix[num].y = pix[i].y;
		++num;
	}
	return num;
}

void DrawCircle(int midx, int midy, int radius) {
	Point pix[1024];
	int count = MidpointCircle(radius, pix);
	glBegin(GL_POINTS);
	for(int i = 0; i < count; ++i) {
		glVertex2i(pix[i].x + midx, pix[i].y + midy);
	}
	glEnd();
}

void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f, 0.5f, 0.5f);
	//Draw circle
	DrawCircle(0, 0, 20);
	glFlush();
}

void ChangeSize(GLsizei w, GLsizei h) {
	GLfloat aspectRatio;
	if(h == 0) {
		h = 1;
	}
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat)w / (GLfloat)h;
	if(w <= h) {
		glOrtho(-100.0, 100.0, -100.0/aspectRatio, 100.0/aspectRatio, 1.0, -1.0);
	} else {
		glOrtho(-100.0*aspectRatio, 100.0*aspectRatio, -100.0, 100.0, 1.0, -1.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow("RoundDDA");

	init();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
	return 0;
}
