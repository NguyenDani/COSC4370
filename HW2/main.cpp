/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "./freeglut-3.2.1/include/GL/freeglut.h"

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0,1,4,1};
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 4; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() {
    // TODO: Your code here!
  float add = 360/11;
  float angle = 0;
  for(int i = 0; i < 10; i++){
    float x = (1*cos(angle));
    float y = (1*sin(angle));
    glPushMatrix();
      glTranslatef(x, y, 0.0);
      glRotatef(angle, 0, 0, 1);
      glutSolidTeapot(.1);
    glPopMatrix(); 
    
    angle += add;
  }
  
  
}

void problem2() {
    // TODO: Your code here!
  float x = 1.0;
  for(int i = 0; i < 20; i++){
    float y = 0.0;
    for(int j = 0; j <= i+1; j++){
      glPushMatrix();
        glTranslatef(x, y, 0.0);
        glutSolidCube(.1);
      glPopMatrix();
      y += 0.025;
    }
    x -= 0.1;
  }
}

void problem3() {
    // TODO: Your code here!
  float sub, x = 0.0, y = -0.9, change = 0.15;
  sub = change*2;
  for(int i = 0; i < 6; i++){
    float temp = x;
    for(int j = 0; j <= i; j++){
      glPushMatrix();
        glTranslatef(temp, y, 0.0);
        glutSolidTeapot(0.1);
      glPopMatrix();
      temp += sub;
    }
    x -= change;
    y += 0.3;
  }
}

void problem4() {
    // TODO: Your code here!
  // Eyes
  float eyex = -0.5;
  for(int i = 0; i < 2; i++){
    float eyey = 1.0;
    for(int j = 0; j < 5; j++){
      glPushMatrix();
        glTranslatef(eyex, eyey, 0.0);
        glutSolidCube(0.1);
      glPopMatrix();
      eyey -= 0.1;
    }
    eyex *= -1.0;
  }
  
  // Head
  for(int i = 0; i < 360; i++){
    float x = (1.5*cos(i));
    float y = (1.5*sin(i));
    glPushMatrix();
      glTranslatef(x, y, 0.0);
      glutSolidCube(0.05);
    glPopMatrix();
  }
  
  // Mouth
  glPushMatrix();
    glTranslatef(0.0, -0.75, 0.0);
    glRotatef(45, 0.0, 0.0, 1.0);
    glutSolidCube(0.2);
    glRotatef(45, 0.0, 0.0, 1.0);
    glutSolidCube(0.2);
  glPopMatrix();

  //Nose
  glBegin(GL_TRIANGLES);
    glVertex3f(0, 0.25, 0);
    glVertex3f(-0.1, 0, 0);
    glVertex3f(0.1, 0, 0);

    glVertex3f(0, 0.25, 0);
    glVertex3f(-0.1, 0, 0);
    glVertex3f(0, 0, -.25);
    
    glVertex3f(0, 0.25, 0);
    glVertex3f(0, 0, -.25);
    glVertex3f(0.1, 0, 0);
  glEnd();
  
}

void display() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
		glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(1,0,0); // x axis
		glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,1,0); // y axis
		glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,windowWidth,windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot,0,1,0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0])*.1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1,(y-lastPos[1])*.1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key-'0';
    if (key == 'q' || key == 'Q' || key == 27){
        exit(0);
    }
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
