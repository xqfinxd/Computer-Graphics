#include <math.h>
#include <stdio.h>
#include "windows.h"
#include<GL/glut.h>
typedef struct {
	float x,y;
} Point2f;

typedef struct {
	float x,y,z;
} Point3f;

int p1[2][4] = {{0,1,-2,1}, {1,-2,1,0}};
int p2[2][4] = {{0,1,0,0}, {1,0,0,0}};

int matHermite[4][4] = {
    {2,-2,1,1},
    {-3,3,-2,-1},
    {0,0,1,0},
    {1,0,0,0},
};

int matBezier[4][4] = {
    {-1,3,-3,1},
    {3,6,-3,0},
    {-3,3,0,0},
    {1,0,0,0},
};

int matBspline[4][4] = {
    {-1, 3,-3, 1 },
    { 3,-6, 3, 0 },
    {-3, 0, 3, 0 },
    { 1, 4, 1, 0 },
};

Point2f hpp[4] = {
    {0,1},
    {3,0},
    {0,1},
    {-3,0},
};

Point3f bpp[4] = {
    {0,0,0},
    {1,1,1},
    {2,-1,-1},
    {3,0,0},
};

void drawCurve(int a[2][4], int ts, int tb, int n)
{
	Point2f p;
	float delta, t, t2, t3;

	delta = 1.0*(tb-ts)/(n-1);
	glBegin(GL_LINE_STRIP);
		for(int i=0; i<n; i++)
		{
			t = i*delta+ts;
			t2 = t*t;
			t3 = t2*t;
			p.x = a[0][0]*t3+a[0][1]*t2+a[0][2]*t+a[0][3];
			p.y = a[1][0]*t3+a[1][1]*t2+a[1][2]*t+a[1][3];
			glVertex2f(p.x, p.y);
		}
	glEnd();
}

void drawCurve3D(int a[3][4], int ts, int tb, int n)
{
	Point3f p;
	float delta, t, t2, t3;

	delta = 1.0*(tb-ts)/(n-1);
	glBegin(GL_LINE_STRIP);
		for(int i=0; i<n; i++)
		{
			t = i*delta+ts;
			t2 = t*t;
			t3 = t2*t;
			p.x = a[0][0]*t3+a[0][1]*t2+a[0][2]*t+a[0][3];
			p.y = a[1][0]*t3+a[1][1]*t2+a[1][2]*t+a[1][3];
			p.z = a[2][0]*t3+a[2][1]*t2+a[2][2]*t+a[2][3];
			glVertex3f(p.x, p.y, p.z);
		}
	glEnd();
}

void computeHermite(int arr[2][4], Point2f pp1, Point2f pp4, Point2f rp1, Point2f rp4) {
    for(int i=0; i<4; i++) {
        int sum = 0;
        sum += matHermite[i][0]*pp1.x;
        sum += matHermite[i][1]*pp4.x;
        sum += matHermite[i][2]*rp1.x;
        sum += matHermite[i][3]*rp4.x;
        arr[0][i] = sum;
        sum = 0;
        sum += matHermite[i][0]*pp1.y;
        sum += matHermite[i][1]*pp4.y;
        sum += matHermite[i][2]*rp1.y;
        sum += matHermite[i][3]*rp4.y;
        arr[1][i] = sum;
    }
}

void computeBezier(int arr[3][4], Point3f p1, Point3f p2, Point3f p3, Point3f p4) {
    for(int i=0; i<4; i++) {
        int sum = 0;
        sum += matBezier[i][0]*p1.x;
        sum += matBezier[i][1]*p2.x;
        sum += matBezier[i][2]*p3.x;
        sum += matBezier[i][3]*p4.x;
        arr[0][i] = sum;
        sum = 0;
        sum += matBezier[i][0]*p1.y;
        sum += matBezier[i][1]*p2.y;
        sum += matBezier[i][2]*p3.y;
        sum += matBezier[i][3]*p4.y;
        arr[1][i] = sum;
        sum = 0;
        sum += matBezier[i][0]*p1.z;
        sum += matBezier[i][1]*p2.z;
        sum += matBezier[i][2]*p3.z;
        sum += matBezier[i][3]*p4.z;
        arr[2][i] = sum;
    }
}

void computeBspline(int arr[3][4], Point3f p1, Point3f p2, Point3f p3, Point3f p4) {
    for(int i=0; i<4; i++) {
        float sum = 0.0f;
        sum += matBspline[i][0]*p1.x;
        sum += matBspline[i][1]*p2.x;
        sum += matBspline[i][2]*p3.x;
        sum += matBspline[i][3]*p4.x;
        arr[0][i] = sum/6.0;
        sum = 0;
        sum += matBspline[i][0]*p1.y;
        sum += matBspline[i][1]*p2.y;
        sum += matBspline[i][2]*p3.y;
        sum += matBspline[i][3]*p4.y;
        arr[1][i] = sum/6.0;
        sum = 0;
        sum += matBspline[i][0]*p1.z;
        sum += matBspline[i][1]*p2.z;
        sum += matBspline[i][2]*p3.z;
        sum += matBspline[i][3]*p4.z;
        arr[2][i] = sum/6.0;
    }
}

void init() {
	glClearColor(1.0,1.0,1.0,1.0);
}

void RenderScence()
{
	glClear(GL_COLOR_BUFFER_BIT);
/*
//Draw p1 and p2
	glColor3f(0.0,1.0,0.0);
	drawCurve(p1, 0, 1, 100);
	glColor3f(0.0,0.0,1.0);
	drawCurve(p2, 0, 1, 100);
*/
/*
//Draw hermite curve
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
        glVertex2f(hpp[0].x, hpp[0].y);
        glVertex2f(hpp[1].x, hpp[1].y);
        glVertex2f(hpp[2].x, hpp[2].y);
        glVertex2f(hpp[3].x, hpp[3].y);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(4.0);
    glBegin(GL_POINTS);
        glVertex2f(hpp[0].x, hpp[0].y);
        glVertex2f(hpp[1].x, hpp[1].y);
        glVertex2f(hpp[2].x, hpp[2].y);
        glVertex2f(hpp[3].x, hpp[3].y);
    glEnd();
    int arr[2][4] = {};
    computeHermite(arr, hpp[0], hpp[1], hpp[2], hpp[3]);
    glColor3f(0.0, 1.0, 0.0);
	drawCurve(arr, 0, 1, 100);
*/
/*
//Draw bezier curve
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
        glVertex3f(bpp[0].x, bpp[0].y, bpp[0].z);
        glVertex3f(bpp[1].x, bpp[1].y, bpp[1].z);
        glVertex3f(bpp[2].x, bpp[2].y, bpp[2].z);
        glVertex3f(bpp[3].x, bpp[3].y, bpp[3].z);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(4.0);
    glBegin(GL_POINTS);
        glVertex3f(bpp[0].x, bpp[0].y, bpp[0].z);
        glVertex3f(bpp[1].x, bpp[1].y, bpp[1].z);
        glVertex3f(bpp[2].x, bpp[2].y, bpp[2].z);
        glVertex3f(bpp[3].x, bpp[3].y, bpp[3].z);
    glEnd();
    int arrB[3][4] = {};
    computeBezier(arrB, bpp[0], bpp[1], bpp[2], bpp[3]);
    glColor3f(0.0,1.0,0.0);
    drawCurve3D(arrB, 0, 1, 100);
*/
//*
//Draw bspline curve
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
        glVertex3f(bpp[0].x, bpp[0].y, bpp[0].z);
        glVertex3f(bpp[1].x, bpp[1].y, bpp[1].z);
        glVertex3f(bpp[2].x, bpp[2].y, bpp[2].z);
        glVertex3f(bpp[3].x, bpp[3].y, bpp[3].z);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(4.0);
    glBegin(GL_POINTS);
        glVertex3f(bpp[0].x, bpp[0].y, bpp[0].z);
        glVertex3f(bpp[1].x, bpp[1].y, bpp[1].z);
        glVertex3f(bpp[2].x, bpp[2].y, bpp[2].z);
        glVertex3f(bpp[3].x, bpp[3].y, bpp[3].z);
    glEnd();
    int arrB[3][4] = {};
    computeBspline(arrB, bpp[0], bpp[1], bpp[2], bpp[3]);
    glColor3f(0.0,0.0,1.0);
    drawCurve3D(arrB, 0, 2, 200);
//*/
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
		glOrtho(-5.0,5.0,-5.0/aspectRatio,5.0/aspectRatio,1.0,-1.0);
	else
		glOrtho(-5.0*aspectRatio,5.0*aspectRatio,-5.0,5.0,1.0,-1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("DrawCurve");

	init();
	glutDisplayFunc(RenderScence);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();

	return 0;
}
