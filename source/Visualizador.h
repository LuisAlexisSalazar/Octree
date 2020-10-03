#pragma once

#include <GL/freeglut.h>
#include <GL/glut.h>
#include"CPunto.h"
#include<vector>

#define CCOLORG 0.5,0.5,0.5
#define CCOLORN 0.0,0.0,0.0

double rotX = 0.0, rotY = 0.0, rotZ = 0.0;
double zoom = -40.0;
bool viewMode = 1;

void drawSkelethonCube(CPunto pos0, CPunto dim) {
    glBegin(GL_LINE_LOOP);
    glColor3d(CCOLORN);
    glVertex3f(pos0.x, pos0.y, pos0.z);
    glVertex3f(pos0.x + dim.x, pos0.y, pos0.z);
    glVertex3f(pos0.x + dim.x, pos0.y + dim.y, pos0.z);
    glVertex3f(pos0.x, pos0.y + dim.y, pos0.z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3d(CCOLORN);
    glVertex3f(pos0.x, pos0.y, pos0.z + dim.z);
    glVertex3f(pos0.x + dim.x, pos0.y, pos0.z + dim.z);
    glVertex3f(pos0.x + dim.x, pos0.y + dim.y, pos0.z + dim.z);
    glVertex3f(pos0.x, pos0.y + dim.y, pos0.z + dim.z);
    glEnd();

    glBegin(GL_LINES);
    glColor3d(CCOLORN);
    glVertex3f(pos0.x, pos0.y, pos0.z);
    glVertex3f(pos0.x, pos0.y, pos0.z + dim.z);
    glEnd();

    glBegin(GL_LINES);
    glColor3d(CCOLORN);
    glVertex3f(pos0.x + dim.x, pos0.y, pos0.z);
    glVertex3f(pos0.x + dim.x, pos0.y, pos0.z + dim.z);
    glEnd();

    glBegin(GL_LINES);
    glColor3d(CCOLORN);
    glVertex3f(pos0.x + dim.x, pos0.y + dim.y, pos0.z);
    glVertex3f(pos0.x + dim.x, pos0.y + dim.y, pos0.z + dim.z);
    glEnd();

    glBegin(GL_LINES);
    glColor3d(CCOLORN);
    glVertex3f(pos0.x, pos0.y + dim.y, pos0.z);
    glVertex3f(pos0.x, pos0.y + dim.y, pos0.z + dim.z);
    glEnd();
}

void drawFilledCube(CPunto pos0, CPunto dim) {
    glBegin(GL_QUADS);

    glColor3d(CCOLORG);
    glVertex3f(pos0.x, pos0.y, pos0.z);
    glVertex3f(pos0.x + dim.z, pos0.y, pos0.z);
    glVertex3f(pos0.x + dim.x, pos0.y + dim.y, pos0.z);
    glVertex3f(pos0.x, pos0.y + dim.y, pos0.z);

    glVertex3f(pos0.x, pos0.y, pos0.z + dim.z);
    glVertex3f(pos0.x + dim.x, pos0.y, pos0.z + dim.z);
    glVertex3f(pos0.x + dim.x, pos0.y + dim.y, pos0.z + dim.z);
    glVertex3f(pos0.x, pos0.y + dim.y, pos0.z + dim.z);

    glVertex3f(pos0.x, pos0.y, pos0.z);
    glVertex3f(pos0.x, pos0.y, pos0.z + dim.z);
    glVertex3f(pos0.x, pos0.y + dim.y, pos0.z + dim.z);
    glVertex3f(pos0.x, pos0.y + dim.y, pos0.z);

    glVertex3f(pos0.x + dim.x, pos0.y, pos0.z);
    glVertex3f(pos0.x + dim.x, pos0.y, pos0.z + dim.z);
    glVertex3f(pos0.x + dim.x, pos0.y + dim.y, pos0.z + dim.z);
    glVertex3f(pos0.x + dim.x, pos0.y + dim.y, pos0.z);

    glVertex3f(pos0.x, pos0.y, pos0.z);
    glVertex3f(pos0.x + dim.x, pos0.y, pos0.z);
    glVertex3f(pos0.x + dim.x, pos0.y, pos0.z + dim.z);
    glVertex3f(pos0.x, pos0.y, pos0.z + dim.z);

    glVertex3f(pos0.x, pos0.y + dim.y, pos0.z);
    glVertex3f(pos0.x + dim.x, pos0.y + dim.y, pos0.z);
    glVertex3f(pos0.x + dim.x, pos0.y + dim.y, pos0.z + dim.z);
    glVertex3f(pos0.x, pos0.y + dim.y, pos0.z + dim.z);
    glEnd();
}


struct DrawableOctant {
    CPunto startP, dim;
    DrawableOctant(CPunto boundMin, CPunto boundMax) {
        startP = boundMin;
        dim = boundMax - boundMin;
        dim = CPunto(dim.x * 0.5, dim.y * 0.5, dim.z * 0.5);
    }
    void show() {
        if (viewMode) {
            drawFilledCube(startP, dim);
            drawSkelethonCube(startP, dim);
        }
        else {
            drawSkelethonCube(startP, dim);
        }
    }
};

static vector<DrawableOctant> octants;




void init(int w, int h) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClearDepth(80.0);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    gluPerspective(45, (float)w / h, .01, 100);
    glMatrixMode(GL_MODELVIEW);
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0, 0, zoom);

    glRotatef(rotX, 1.0, 0.0, 0.0);
    glRotatef(rotY, 0.0, 1.0, 0.0);
    glRotatef(rotZ, 0.0, 0.0, 1.0);

    for (auto& cube : octants) {
        cube.show();
    }

    glutSwapBuffers();
    glFlush();
    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '2':
        rotX--;
        return;
    case '8':
        rotX++;
        return;
    case '4':
        rotY--;
        return;
    case '6':
        rotY++;
        return;
    case '9':
        rotZ--;
        return;
    case '7':
        rotZ++;
        return;
    case ' ':
        rotX = 0;
        rotY = 0;
        rotZ = 0;
        zoom = -40;
        return;
    case '+':
        zoom += 1.0;
        return;
    case '-':
        zoom -= 1.0;
        return;
    case '.':
        viewMode = !viewMode;
        return;
    }
    glutPostRedisplay();
}


void runOPENGL(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Range Octree Visualization");
    init(1024, 768);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}