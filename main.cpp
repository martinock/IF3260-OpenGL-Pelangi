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

float counter = 0.0;
float red[3] = {1.0, 0.0, 0.0};
float white[3] = {1.0, 1.0, 1.0};
float black[3] = {0.0, 0.0, 0.0};
float green[3] = {0.0, 1.0, 0.0};

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

void drawMatahari() {

}

void drawGunung() {

}

void drawPelangi() {

}

void drawPohon() {
    glBegin(GL_POLYGON);
        glColor3fv(green);
        circle(0, 0, 1, -45, 225);
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
