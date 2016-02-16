#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "BatManager.h"
#include "VonMisesDist.h"
#define PI 3.14159265

#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
int rotate_Y; //used to rotate the cube about the Y-axis
int rotate_X; //used to rotate the cube about the X-axis
			  // Display list for coordinate axis 
GLuint axisList;
GLsizei width = 1200, height = 600;
Echo echo, echo1;
BatManager *bat, *bat1;
int noFrames;
const GLfloat vertices[] = {
	-0.25f,  -0.25f,
	0.0f,    0.0f,
	0.0f,    0.5f,
	0.25f, -0.25f,
};

int AXIS_SIZE = 200;
int axisEnabled = 1;
//the display function draws the scene and redraws it
void timerFunc(int value) {
	noFrames += 1;
	if (noFrames < 300)
		glutTimerFunc(100, timerFunc, 0);
	glutPostRedisplay();


}
void display() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (noFrames % 5 == 0) {
		(*bat).echolocateBat(bat1);
		(*bat1).echolocateBat(bat);

	}
	(*bat).updateBat();
	(*bat1).updateBat();
	std::cout << bat->currentState.speed << " " << bat->currentState.heading << " " << bat->currentState.x << " " << bat->currentState.y << std::endl;


	glEnable(GL_SCISSOR_TEST);


	GLfloat aspect = ((GLfloat)width) / 2 / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(width / 2, 0, width / 2, height);

	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix
	if (width >= height) {
		// aspect >= 1, set the height from -1 to 1, with larger width
		gluOrtho2D(-50.0 * aspect, 50.0 * aspect, -50.0, 50.0);
	}
	else {
		// aspect < 1, set the width to -1 to 1, with larger height
		gluOrtho2D(-50.0, 50.0, -50.0 / aspect, 50.0 / aspect);
	}
	glScissor(((float)width / 2), 0, width, height);

	glMatrixMode(GL_MODELVIEW);
	std::cout << bat->currentState.speed << " " << bat->currentState.heading << " " << bat->currentState.x << " " << bat->currentState.y << std::endl;
	glClearColor(0.0, 0.0, 0.0, 0.0);
       // Clear the color buffer (background)
	//glTranslatef(0.5, 0.5, 0 );
	glPushMatrix();
	glTranslatef(bat->currentState.x, bat->currentState.y, 0);
	glRotatef(bat->currentState.heading * 180 / PI, 0, 0, 1);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(2, 0);
	glVertex2f(0, 1);
	glVertex2f(0, -1);
	glEnd();
	glPopMatrix();
	glPointSize(2.0);
	glBegin(GL_POINTS);
	for (auto const &it : bat->prevStates) {
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex2f(it.second.x, it.second.y);
	}
	glEnd();
	glPushMatrix();
	glTranslatef(bat1->currentState.x, bat1->currentState.y, 0);
	glRotatef(bat1->currentState.heading * 180 / PI, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex2f(2, 0);
	glVertex2f(0, 1);
	glVertex2f(0, -1);
	glEnd();
	glPopMatrix();
	glPointSize(2.0);
	glBegin(GL_POINTS);
	for (auto const &it : bat1->prevStates) {
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex2f(it.second.x, it.second.y);
	}
	glEnd();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)width / 2, (GLsizei)height);
	gluPerspective(130, ((float)width / 2) / (float)height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glScissor(0, 0, (float)width, height);
	glPushMatrix();
	////clear the screen and the z-buffer 
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//glDisable(GL_CULL_FACE);
	glLoadIdentity(); //resets the transformations
	double heading1 = 30;
	double x = 1, y = 1;
	gluLookAt((bat->currentState.x+50)*30/100, 15.0, -(bat->currentState.y + 50) * 30 / 100, (bat->currentState.x + 50) * 30 / 100 + cos(bat->currentState.heading * PI / 180.0), 15.0, -(bat->currentState.y + 50) * 30 / 100 - sin(bat->currentState.heading * PI / 180.0), 0.0, 1.0, 0.0);

	//Front Face of the cube - vertex definition
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0f, 0.0f, -30.0f);
	glVertex3f(0.0f, 30.0f, -30.0f);
	glVertex3f(30.0f, 30.0f, -30.0f);
	glVertex3f(30.0f, 0.0f, -30.0f);
	glEnd();
	//Back Face of the cube - vertex definition
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 30.0f, 0.0f);
	glVertex3f(30.0f, 30.0f, 0.0f);
	glVertex3f(30.0f, 0.0f, 0.0f);
	glEnd();

	//Right Face of the cube - vertex definition
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(30.0f, 0.0f, 0.0f);
	glVertex3f(30.0f, 30.0f, 0.0f);
	glVertex3f(30.0f, 30.0f, -30.0f);
	glVertex3f(30.0f, 0.0f, -30.0f);
	glEnd();

	//Left Face of the cube - vertex definition
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.0);
	glVertex3f(0.0f, 0.0f, -30.0f);
	glVertex3f(0.0f, 30.0f, -30.0f);
	glVertex3f(0.0f, 30.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	//Upper Face of the cube - vertex definition
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.3);
	glVertex3f(0.0f, 30.0f, 0.0f);
	glVertex3f(0.0f, 30.0f, -30.0f);
	glVertex3f(30.0f, 30.0f, -30.0f);
	glVertex3f(30.0f, 30.0f, 0.0f);
	glEnd();

	//Bottom Face of the cube - vertex definition
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.2, 0.8);
	glVertex3f(0.0f, 0.0f, -30.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(30.0f, 0.0f, 0.0f);
	glVertex3f(30.0f, 0.0f, -30.0f);
	glEnd();
	if (axisEnabled) glCallList(axisList);

	glPushMatrix();

	glTranslatef((bat->currentState.x + 50) * 30 / 100, 15.0, -(bat->currentState.y + 50) * 30 / 100);
	glRotatef(bat->currentState.heading, 0.0, 1.0, 0.0);

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-0.6f, -0.2f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glEnd();

	//Back Face of the cube - vertex definition
	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(-0.6f, -0.2f, 0.1f);
	glVertex3f(-0.6f, 0.0f, 0.1f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glVertex3f(0.0f, -0.2f, 0.1f);
	glEnd();

	//Right Face of the cube - vertex definition
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(0.0f, -0.2f, 0.1f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glEnd();

	//Left Face of the cube - vertex definition
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-0.6f, -0.2f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.1f);
	glVertex3f(-0.6f, -0.2f, 0.1f);
	glEnd();

	//Upper Face of the cube - vertex definition
	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(-0.6f, 0.0f, 0.1f);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glEnd();

	//Bottom Face of the cube - vertex definition
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-0.6f, -0.2f, 0.0f);
	glVertex3f(-0.6f, -0.2f, 0.1f);
	glVertex3f(0.0f, -0.2f, 0.1f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();

	glTranslatef((bat1->currentState.x + 50) * 30 / 100, 15.0, -(bat1->currentState.y + 50) * 30 / 100);
	glRotatef(bat1->currentState.heading, 0.0, 1.0, 0.0);

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-0.6f, -0.2f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glEnd();

	//Back Face of the cube - vertex definition
	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);
	glVertex3f(-0.6f, -0.2f, 0.1f);
	glVertex3f(-0.6f, 0.0f, 0.1f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glVertex3f(0.0f, -0.2f, 0.1f);
	glEnd();

	//Right Face of the cube - vertex definition
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(0.0f, -0.2f, 0.1f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glEnd();

	//Left Face of the cube - vertex definition
	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.7, 0.7);
	glVertex3f(-0.6f, -0.2f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.1f);
	glVertex3f(-0.6f, -0.2f, 0.1f);
	glEnd();

	//Upper Face of the cube - vertex definition
	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(-0.6f, 0.0f, 0.1f);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glEnd();

	//Bottom Face of the cube - vertex definition
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-0.6f, -0.2f, 0.0f);
	glVertex3f(-0.6f, -0.2f, 0.1f);
	glVertex3f(0.0f, -0.2f, 0.1f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glEnd();
	glPopMatrix();
    glPopMatrix();

	glDisable(GL_SCISSOR_TEST);

	// If enabled, draw coordinate axis

	glFlush();
	glutSwapBuffers(); //send image to the screen
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//the special keys function allows interaction via keys (also special ones)
void specialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		exit(0);
		break;
	case GLUT_KEY_LEFT:
		rotate_Y -= 5;
		break;
	case GLUT_KEY_UP:
		rotate_X -= 5;
		break;
	case GLUT_KEY_RIGHT:
		rotate_Y += 5;
		break;
	case GLUT_KEY_DOWN:
		rotate_X += 5;
		break;
	}

	glutPostRedisplay(); //request a screen refresh to see changes 

}
void makeAxes() {
	// Create a display list for drawing coord axis
	axisList = glGenLists(1);
	glNewList(axisList, GL_COMPILE);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);       // X axis - red
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(AXIS_SIZE, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);       // Y axis - green
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, AXIS_SIZE, 0.0);
	glColor3f(0.0, 0.0, 1.0);       // Z axis - blue
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, AXIS_SIZE);
	glEnd();
	glEndList();
}
void reshape(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);

}
int main(int argc, char*argv[]) {

	echo.sourceLevel = 110, echo.targetStrength = -10, echo.A = 16, echo.c = -1.28;
	echo1 = echo;
	bat = new BatManager(10, 0, 10, echo);
	bat1 = new BatManager(10, 0, 10, echo1);
	////initialize GLUT 
	glutInit(&argc, argv);

	//request double buffering, RGB colors window and a z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);

	//create a window
	glutInitWindowSize(1200, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Space");

	//enable depth
	glEnable(GL_DEPTH_TEST);
	//

	//callback functions
	glutDisplayFunc(display); //display - redraws the scene
	glutTimerFunc(100, timerFunc, 0);
	//glutReshapeFunc(reshape);

	glutSpecialFunc(specialKeys); //special - allows interaction with specialkeys
	makeAxes();								  //pass control to GLUT for events
	glutMainLoop();
	// terminate lib
	//libricianDistTerminate();

	// terminate MCR
	//mclTerminateApplication();
	return 0; //this line is never reached
}