#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

typedef struct {
	int x, y;
} Point;

void init() {
	glClearColor(.0f, .0f, .0f, 1.0f);
}

void Draw() {
	Point points[5] = {
		{ 47, 29 },
		{ 58, 45 },
		{ 83, 44 },
		{ 94, 29 },
		{105, 10 },
	};
	Point lines[6] = {
		{ 19, 151},
		{ 88, 120},
		{ 82, 140},
		{158, 152},
		{150, 160},
		{122, 179},
	};
	Point line_strip[5] = {
		{246, 148},
		{322, 183},
		{304, 160},
		{258, 168},
		{253, 180},
	};
	Point line_loop[6] = {
		{438, 137},
		{463, 174},
		{531, 174},
		{512, 136},
		{494, 166},
		{469, 116},
	};
	Point polygon[5] = {
		{ 56, 279},
		{111, 267},
		{100, 300},
		{ 46, 321},
		{ 41, 301},
	};
	Point quads[8] = {
		{210, 284},
		{270, 290},
		{270, 254},
		{224, 260},
		{300, 315},
		{323, 315},
		{347, 243},
		{305, 261},
	};
	Point quad_strip[6] = {
		{442, 302},
		{435, 268},
		{473, 302},
		{473, 366},
		{512, 293},
		{494, 259},
	};
	Point triangles[6] = {
		{ 23, 463},
		{ 23, 432},
		{ 63, 463},
		{ 92, 449},
		{ 38, 407},
		{146, 407},
	};
	Point triangle_strip[5] = {
		{225, 385},
		{225, 439},
		{278, 385},
		{306, 439},
		{324, 385},
	};
	Point triangle_fan[5] = {
		{464, 429},
		{464, 380},
		{501, 392},
		{511, 423},
		{508, 451},
	};
	glBegin(GL_POINTS);
	for(int i = 0; i < 5; ++i) {
		glColor3f(1.0f, 0.1f*i, 0.1f*i);
		glVertex2i(points[i].x, points[i].y);
	}
	glEnd();
	glBegin(GL_LINES);
	for(int i = 0; i < 6; ++i) {
		glColor3f(1.0f, 0.1f*i, 0.1f*i);
		glVertex2i(lines[i].x, lines[i].y);
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	for(int i = 0; i < 5; ++i) {
		glColor3f(1.0f, 0.1f*i, 0.1f*i);
		glVertex2i(line_strip[i].x, line_strip[i].y);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < 6; ++i) {
		glColor3f(1.0f, 0.1f*i, 0.1f*i);
		glVertex2i(line_loop[i].x, line_loop[i].y);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for(int i = 0; i < 5; ++i) {
		glColor3f(1.0f, 0.1f*i, 0.1f*i);
		glVertex2i(polygon[i].x, polygon[i].y);
	}
	glEnd();
	glBegin(GL_QUADS);
	for(int i = 0; i < 8; ++i) {
		glColor3f(1.0f, 0.1f*i, 0.1f*i);
		glVertex2i(quads[i].x, quads[i].y);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for(int i = 0; i < 6; ++i) {
		glColor3f(1.0f, 0.1f*i, 0.1f*i);
		glVertex2i(quad_strip[i].x, quad_strip[i].y);
	}
	glEnd();
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < 6; ++i) {
		glColor3f(1.0f, 0.1f*i, 0.1f*i);
		glVertex2i(triangles[i].x, triangles[i].y);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for(int i = 0; i < 5; ++i) {
		glColor3f(1.0f, 0.1f*i, 0.1f*i);
		glVertex2i(triangle_strip[i].x, triangle_strip[i].y);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	for(int i = 0; i < 5; ++i) {
		glColor3f(1.0f, 0.1f*i, 0.1f*i);
		glVertex2i(triangle_fan[i].x, triangle_fan[i].y);
	}
	glEnd();
}

void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	Draw();
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
	glOrtho(0.0, 560.0, 0.0, 500.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowSize(560, 500);
	glutCreateWindow("draw");

	init();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
	return 0;
}
