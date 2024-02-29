#include <iostream>
#include <math.h>
#include <GL/freeglut.h>
#include <time.h>
#include <sys/timeb.h>
#include <string.h>
using namespace std;

#define HOUR_HAND_LENGTH 50.0
#define MINUTE_HAND_LENGTH 70.0
#define SECOND_HAND_LENGTH 78.0
#define CLOCK_RADIUS 80.0
#define PI 3.14159
#define CLOCK_VOL 100.00
#define ANGLE_ONE_MIN PI/30.0

//FUNCTION TO INITIALIZE STUFF
void init(void)
{
    gluOrtho2D(100, 100, 100, 100);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glShadeModel (GL_SMOOTH);
    glLoadIdentity();
}


//STRUCTURE DEFINING POINT
typedef struct point
{
    double x, y;
} point;

//FUNCTION TO DRAW A POINT
void drawPoint(point p)
{
    glBegin(GL_POINTS);
    glVertex2f(p.x, p.y);
    glEnd();
}


//FUNCTION TO DRAW A LINE
void drawLine(double x, double y, double angle)
{
    glVertex2f(x, x);
    glVertex2f(y*cos(angle), y*sin(angle));
}


//FUNCTION TO DRAW MIN AND HOUR Marks of a CLOCK
void drawMarks(void)
{
    point startp, endp, p;
    int count = 0;
    double i = PI/6.0;
    startp.x = 0, startp.y = 0, endp.x = 0, endp.y = CLOCK_RADIUS;
    glPointSize(15.0);
    drawPoint(startp);
    for(i=0; i<=2*PI; i+=PI/30.0)
    {
        if(i==PI/6.0)
            p.x = CLOCK_RADIUS;
        else
            p.x = endp.y*sin(i);
        p.y = endp.y*cos(i);
        if (count%5==0)
            glPointSize(10.0);
        drawPoint(p);
        {
        }
        else
        {
            glPointSize(5.0);
            drawPoint(p);
        }
        count++;
    }
}

//ANGLES FOR EACH HAND
double secondAngle = 0, minute Angle = 0, hourAngle = 0;

//FUNCTION To Draw Main CLOCK STRUCTURE
void drawClock(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    drawMarks();
    glLineWidth(10.0);
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    drawLine(0.0, HOUR_HAND_LENGTH, -hourAngle+PI/2);
    glEnd();
    glLineWidth(6.0);
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    drawLine(0.0, MINUTE_HAND_LENGTH, -minuteAngle+PI/2);
    glEnd();
    glLineWidth(3.0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    drawLine(0.0, SECOND_HAND_LENGTH, -secondAngle+PI/2);
    glEnd();
    glFlush();
    glutSwapBuffers();
}

//FUNCTION TO MAINTAIN ASPECT RATIO WHEN SCREEN IS RESIZED
void reshape(int w, int h)
{
    double aspectRatio;
    if(h==0)
        h=1; //to avoid division by O
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectRatio = (double)w/(double)h;
    if (w <= h)
        glOrtho (-CLOCK_VOL, CLOCK_VOL, -CLOCK_VOL / aspectRatio, CLOCK_VOL/ aspectRatio, 1.0,-1.0);
    else
        glOrtho (-CLOCK_VOL*aspectRatio, CLOCK_VOL*aspectRatio, -CLOCK_VOL, CLOCK_VOL, 1.0,-1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//TIMER FUNCTION TO ANIMATE
void redraw(int)
{
    struct timeb tb;
    time_t tim=time(0);
    struct tm* t=localtime (&tim);
    ftime(&tb);
    secondAngle = (double) (t->tm_sec+ (double)tb.millitm/1000.0)/30.0* PI;
    minuteAngle = (double) (t->tm_min)/30.0* PI+ secondAngle/60.0;
    hourAngle = (double) (t->tm_hour>12 ? t->tm_hour-12: t->tm_hour)/6.0 * Pl+ minuteAngle/12.0;
    glutPostRedisplay();
    glutTimerFunc(15, redraw, 1);
}

//DRIVER FUNCTION
int main(int a, char **b)
{
    glutInit(&a, b);
    glutInitDisplayMode (GLUT_SINGLE|GLUT_RGB);
    glutinitWindowSize(700, 700);
    glutinitWindowPosition (650, 200);
    glutCreateWindow("Analog Clock");
    init();
    glutDisplayFunc(drawClock);
    glutReshapeFunc(reshape);
    glutTimerFunc(15, redraw, 1);
    glutMainLoop();
    return 0;
}
