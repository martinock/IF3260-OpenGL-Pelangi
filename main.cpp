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

void drawMatahari() {

}

void drawGunung() {
    clearQuads();
    red = 0;
    green = 0;
    blue = 1;
    QuadCircle(0, -0.5, 0.1, 0, 360, 0);


    drawTess(0, 360);
    //drawTess(280);
    //drawTess(420);
}

void drawPelangi() {
    drawRainbow();
    drawTess(0, 280);
    drawTess(140, 280);
    drawTess(280, 280);
    drawTess(420, 280);
}

void drawPohon() {
    glBegin(GL_POLYGON);
        glColor3fv(color_green);
        circle(-0.6, -0.2, 0.1, 0, 360);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3fv(color_green);
        circle(-0.7, -0.2, 0.1, 0, 360);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3fv(color_green);
        circle(-0.65, -0.1, 0.1, 0, 360);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3fv(color_green);
        glVertex2f(-0.65, -0.2);
        glVertex2f(-0.6, -0.5);
        glVertex2f(-0.7, -0.5);
    glEnd();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawPelangi();
    drawGunung();
    drawMatahari();
    drawPohon();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(150, 0, w/(1.5), h);
}

void initOpenGL() {
    // color --- r    g    b    alpha
    glClearColor(0.0, 0.5, 1.0, 1.0);
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(900,600);
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
