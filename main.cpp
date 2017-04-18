/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "callback.h"

#define quadx 1000
#define quady 6

using std::stringstream;
using std::cout;
using std::ends;

float red = 1, green = 1, blue = 1;

float counter = 0.0;
float color_red[3] = {1.0, 0.0, 0.0};
float color_white[3] = {1.0, 1.0, 1.0};
float color_black[3] = {0.0, 0.0, 0.0};
float color_green[3] = {0.0, 1.0, 0.0};

GLdouble quads[quadx][quady];

void circle(float x, float y, float r, int anglestart, int anglestop) {
    for (int i = anglestart;i < anglestop ;i++) {
        float degInRad = i*3.14159/180;
        //glColor3f(1, 1, 1);
        glVertex2f(cos(degInRad)*r + x, sin(degInRad)*r + y);
    }
}

void circle_gradation(float x, float y, float r, int anglestart, int anglestop) {
    for (int i = anglestart;i < anglestop ;i++) {
        float degInRad = i*3.14159/180;
        glColor3f(0, sin(degInRad) , 0);
        glVertex2f(cos(degInRad)*r + x, sin(degInRad)*r + y);
    }
}

void InverseCircle(float x, float y, float r, int anglestart, int anglestop) {
    for (int i = anglestart-1;i >= anglestop ;i--) {
        float degInRad = i*3.14159/180;
        //glColor3f(1, 1, 1);
        glVertex2f(cos(degInRad)*r + x, sin(degInRad)*r + y);
    }
}

void clearQuads() {
    for (int i = 0 ; i < quadx ; i++) {
        for (int j = 0 ; j < quady ; j++) {
            quads[i][j] = 0;
        }
    }
}

void addPoint(float x, float y, float z, float r, float g, float b, int index) {
    quads[index][0] = x;
    quads[index][1] = y;
    quads[index][2] = z;
    quads[index][3] = r;
    quads[index][4] = g;
    quads[index][5] = b;
}

void QuadCircle(float x, float y, float r, int anglestart, int anglestop, int idx) {
    for (int i = anglestart;i < anglestop ;i++) {
        float degInRad = i*3.14159/180;
        int index = idx+i-anglestart;
        quads[index][0] = cos(degInRad)*r + x;
        quads[index][1] = sin(degInRad)*r + y;
        quads[index][2] = 0;
        quads[index][3] = red;
        quads[index][4] = green;
        quads[index][5] = blue;
    }
}

void QuadInverseCircle(float x, float y, float r, int anglestart, int anglestop, int idx) {
    for (int i = anglestart-1;i >= anglestop ;i--) {
        float degInRad = i*3.14159/180;
        int index = idx-i+anglestart-1;
        quads[index][0] = cos(degInRad)*r + x;
        quads[index][1] = sin(degInRad)*r + y;
        quads[index][2] = 0;
        quads[index][3] = red;
        quads[index][4] = green;
        quads[index][5] = blue;
    }
}

void drawRainbow() {
    clearQuads();
    red = 1;
    green = 0;
    blue = 0;
    QuadCircle(0, -0.5, 0.8, 20, 160, 0);
    red = 1;
    green = 1;
    QuadInverseCircle(0, -0.5, 0.75, 160, 20, 140);
    blue = 0;
    green = 1;
    red = 0;
    QuadCircle(0, -0.5, 0.7, 20, 160, 280);
    blue = 1;
    green = 0;
    QuadInverseCircle(0, -0.5, 0.65, 160, 20, 420);
    red = 1;
    QuadCircle(0, -0.5, 0.6, 20, 160, 560);
}

void drawTess(int x, int xx) {
    // create tessellator
    GLUtesselator *tess = gluNewTess();

    // register callback functions
    gluTessCallback(tess, GLU_TESS_BEGIN, (void (__stdcall*)(void))tessBeginCB);
    gluTessCallback(tess, GLU_TESS_END, (void (__stdcall*)(void))tessEndCB);
    gluTessCallback(tess, GLU_TESS_ERROR, (void (__stdcall*)(void))tessErrorCB);
    gluTessCallback(tess, GLU_TESS_VERTEX, (void (__stdcall*)(void))tessVertexCB2);
    gluTessCallback(tess, GLU_TESS_COMBINE, (void (__stdcall*)(void))tessCombineCB);

    GLdouble quad1[4][3] = { {-0.2,0.6,0}, {0,0,0}, {0.2,0.6,0}, {0,0.4,0} };

    glColor3f(1, 1, 1);
    red = 1;
    green = 1;
    blue = 1;
    // describe non-convex polygon
    gluTessBeginPolygon(tess, NULL);
        // first contour

        gluTessBeginContour(tess);
            for (int i = x;i < (x+xx);i++) {
                //cout << i << " ";
                gluTessVertex(tess, quads[i], quads[i]);
            }
        gluTessEndContour(tess);

    gluTessEndPolygon(tess);

    // delete tessellator after processing
    gluDeleteTess(tess);

}

void drawLangit() {
    glBegin(GL_POLYGON);
        glColor3f(1, 1, 0);
        glVertex2f(-1,1);

        glColor3f(0, 0.9, 1);
        glVertex2f(-1, -1);

        glColor3f(0, 0, 1);
        glVertex2f(1, -1);

        glColor3f(0, 0.9, 1);
        glVertex2f(1, 1);
    glEnd();
}

void drawMatahari(float x, float y) {
   // for (float i = 0.2; i > 0; i-=0.05){
        glBegin(GL_POLYGON);
        glColor3f(1,1,0);
        circle(x, y, 0.2, 0, 360);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3f(0.9,0.9,0);
        circle(x, y, 0.19, 0, 360);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3f(0.80,0.80,0);
        circle(x, y, 0.18, 0, 360);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3f(0.85,0.85,0);
        circle(x, y, 0.17, 0, 360);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3f(0.9,0.9,0);
        circle(x, y, 0.16, 0, 360);
        glEnd();
    //}
}

void drawGunung() {
    clearQuads();
    red = 0.545;
    green = 0.2705;
    blue = 0.074;
    //QuadCircle(0, -0.5, 0.1, 0, 360, 0);
    addPoint(-1,-1,0, 0.4, 0.556, 0.15, 0);
    addPoint(-1,-0.4,0, 0.4, 0.556, 0.15, 1);
    QuadInverseCircle(-0.9,-0.4, 0.2, 180, 90, 2);

    QuadCircle(-0.9,0,0.2,270,330,92);

    addPoint(-0.6,0.2,0,red,green,blue,152);

    QuadInverseCircle(-0.3,0.1,0.3,160,20,153);

    addPoint(0.3, -0.3, 0, red, green, blue, 293);

    QuadInverseCircle(0.3, -0.4, 0.1, 90, 30, 294);

    addPoint(0.8, -1, 0, 0, 0, 0, 354);

    addPoint(0.5, -1, 0, 0, 0, 0, 355);

    //addPoint(-1,-1, 0, 1, 0, 0, 355);

    //addPoint(0.5,0.5,0, 1, 0, 0, 2);



    drawTess(0, 356);
    //drawTess(280);
    //drawTess(420);
}

void drawGunung2() {
    clearQuads();
    red = 0.2;
    green = 0.2;
    blue = 0.2;

    float red2 = 0.6;
    float blue2 = 0.6;
    float green2 = 0.6;

    addPoint(0,-1,0, red, green, blue, 0);
    addPoint(0.5,0.2,0, red2, green2, blue2, 1);
    addPoint(0.9,0.2,0, 0.45, 0.45, 0.45, 2);
    addPoint(1.5,-1,0, 0, 0, 0, 3);

    drawTess(0, 4);

    clearQuads();
    red = 1;
    green = 1;
    blue = 1;

    QuadCircle(0.7,0.1,0.23, 10, 170, 0);
    red = 0.5;
    green = 0.5;
    blue = 1;
    addPoint(0.41,0,0, red, green, blue, 160);
    addPoint(0.55,0.099,0, red, green, blue, 161);
    addPoint(0.6,-0.06,0, red, green, blue, 162);
    addPoint(0.69,0.099,0, red, green, blue, 163);
    addPoint(0.72,-0.15,0, red, green, blue, 164);
    addPoint(0.74,0.099,0, red, green, blue, 165);
    addPoint(0.79,-0.05,0, red, green, blue, 166);
    addPoint(0.88,0.099,0, red, green, blue, 167);
    addPoint(1.046,-0.1,0, red, green, blue, 168);

    drawTess(0,169);
}

void drawPelangi() {
    drawRainbow();
    drawTess(0, 280);
    drawTess(140, 280);
    drawTess(280, 280);
    drawTess(420, 280);
}

void drawPohon(GLfloat x, GLfloat y) {
    glBegin(GL_POLYGON);
        glColor3f(0.65, 0.38, 0.01);
        glVertex2f(x, y);

        glColor3f(0.33, 0.19, 0);
        glVertex2f(x + 0.05, y - 0.3);

        glColor3f(0.33, 0.19, 0);
        glVertex2f(x - 0.05, y - 0.3);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3fv(color_green);
        circle_gradation(x + 0.05, y, 0.1, 0, 360);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3fv(color_green);
        circle_gradation(x - 0.05, y, 0.1, 0, 360);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3fv(color_green);
        circle_gradation(x, y + 0.1, 0.1, 0, 360);
    glEnd();
}

void drawCemara(GLfloat x, GLfloat y) {
    glBegin(GL_POLYGON);
        glColor3f(0.65, 0.38, 0.01);
        glVertex2f(x, y);

        glColor3f(0.33, 0.19, 0);
        glVertex2f(x + 0.05, y - 0.3);

        glColor3f(0.33, 0.19, 0);
        glVertex2f(x - 0.05, y - 0.3);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3fv(color_green);
        glVertex2f(x, y+0.1);
        glColor3f(0.0, 0, 0.0);
        glVertex2f(x - 0.2, y-0.1);
        glColor3f(0.0, 0, 0.0);
        glVertex2f(x + 0.2, y-0.1);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3fv(color_green);
        glVertex2f(x, y+0.15);
        glColor3f(0.0, 0.1, 0.0);
        glVertex2f(x - 0.15, y);
        glColor3f(0.0, 0.1, 0.0);
        glVertex2f(x + 0.15, y);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3fv(color_green);
        glVertex2f(x, y+0.2);
        glColor3f(0.0, 0.2, 0.0);
        glVertex2f(x - 0.1, y+0.1);
        glColor3f(0.0, 0.2, 0.0);
        glVertex2f(x + 0.1, y+0.1);
    glEnd();
}

void drawHutan() {
    drawPohon(-0.65, -0.4);
    drawPohon(-0.5, -0.4);
    drawPohon(-0.575, -0.5);
    drawPohon(-0.75, -0.45);
    drawPohon(-0.85, -0.5);
    drawPohon(-0.2, -0.4);
    drawPohon(-0.3, -0.5);
    drawPohon(-0.2, -0.55);
    drawPohon(-0.15, -0.65);
    drawPohon(-0.5, -0.65);
    drawPohon(-0.3, -0.7);
    drawPohon(-0.8, -0.6);
    drawPohon(-0.4, -0.65);
    drawPohon(-0.5, -0.7);
    drawPohon(-0.7, -0.7);
    drawPohon(-0.6, -0.7);
    drawPohon(-0.85, -0.7);
    drawCemara(0.1, -0.55);
    drawCemara(0, -0.5);
    drawCemara(0.1, -0.65);
    drawCemara(0, -0.68);
    drawCemara(0.15, -0.7);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawLangit();
    drawPelangi();
    drawGunung2();
    drawGunung();
    drawMatahari(-0.8,0.8);
    drawHutan();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

void initOpenGL() {
    // color --- r    g    b    alpha
    glClearColor(0.0, 0.5, 1.0, 1.0);
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(700,600);
    glutInitWindowPosition(200,50);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Pelangi");
    initOpenGL();

    glutDisplayFunc(display);
    glutIdleFunc(display);

    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}



