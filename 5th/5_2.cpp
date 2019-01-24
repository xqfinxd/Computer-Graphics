#include <GL/glut.h>
#include <math.h>

static float angle_moon = 0.0f;
static float angle_earth = 0.0f;
const int step = 1000/60;
const float inc_earth = 1.0f;
const float inc_moon = 12.0f;

GLfloat whiteColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat blackColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat redColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
GLfloat blueColor[] = {0.0f, 0.0f, 1.0f, 1.0f};
GLfloat lightPos[] = {0.0f, 0.0f, -300.0f, 1.0f};

void DrawSun()
{
    GLfloat specular[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess[1] = { 5.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glLightfv(GL_LIGHT0,GL_AMBIENT,redColor);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,redColor);
	glLightfv(GL_LIGHT0,GL_SPECULAR,redColor);

    glTranslatef(0.0f, 0.0f, -300.0f);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidSphere(36.0f, 30, 17);
}

void DrawEarth()
{
    GLfloat specular[4] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat shininess[1] = { 5.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glRotatef(angle_earth, 0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glTranslatef(105.0f, 0.0f, 0.0f);
    glutSolidSphere(12.0f, 30, 17);
}

void DrawMoon()
{
    GLfloat specular[4] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat shininess[1] = { 5.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glColor3f(0.5f, 0.5f, 0.5f);
    glRotatef(angle_moon, 0.0f, 1.0f, 0.0f);
    glTranslatef(30.0f, 0.0f, 0.0f);
    glutSolidSphere(4.0f, 30, 17);
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
//  glDisable(GL_LIGHTING);
    DrawSun();
    DrawEarth();
    DrawMoon();
    glPopMatrix();
    glutSwapBuffers();
}
void init()
{
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    GLfloat ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0, 0, 0, 0);
}

void TimerFunc(int value)
{
    angle_moon += inc_moon;
    if (angle_moon > 360.0f)
        angle_moon = 0.0f;
    angle_earth += inc_earth;
    if (angle_earth > 360.0f)
        angle_earth = 0.0f;
    glutPostRedisplay();
    glutTimerFunc(step, TimerFunc, 1);
}

void ChangeSize(int w, int h)
{
    GLfloat fAspect;

    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w / (GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, fAspect, 1.0, 425.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("SUN");
    init();
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutTimerFunc(step, TimerFunc, 1);
    glutMainLoop();
    return 0;
}
