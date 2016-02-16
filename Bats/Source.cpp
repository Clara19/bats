//
//#include <stdlib.h>
//#include <stdio.h>
//#include <time.h>
//#include <math.h>
//
//#ifdef MACOSX
//#include <GLUT/glut.h>
//#else
//#include <GL/glut.h>
//#endif
//
//
//int rotate_Y; //used to rotate the cube about the Y-axis
//int rotate_X; //used to rotate the cube about the X-axis
//
//			  //the display function draws the scene and redraws it
//void display() {
//
//	//clear the screen and the z-buffer 
//	//glDisable(GL_CULL_FACE);
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glLoadIdentity(); //resets the transformations
//
//	//glRotatef(rotate_X, 1.0, 0.0, 0.0);
//	//glRotatef(rotate_Y, 0.0, 1.0, 0.0);
//	
//		glPushMatrix();
//		//glRotatef(0,0,0,1);
//		//glScalef(2,1,2);
//		glBegin(GL_QUADS);
//		/* Floor */
//		glColor3f(1, 1, 0);
//		glVertex3f(-1, -1, -1);
//		glVertex3f(1, -1, -1);
//		glVertex3f(1, -1, 1);
//		glVertex3f(-1, -1, 1);
//		/* Ceiling */
//		glColor3f(1, 1, 1);
//		glVertex3f(-1, 1, -1);
//		glVertex3f(1, 1, -1);
//		glVertex3f(1, 1, 1);
//		glVertex3f(-1, 1, 1);
//		/* Walls */
//		glColor3f(0, 1, 1);
//		glVertex3f(-1, -1, 1);
//		glVertex3f(1, -1, 1);
//		glVertex3f(1, 1, 1);
//		glVertex3f(-1, 1, 1);
//
//		glVertex3f(-1, -1, -1);
//		glVertex3f(1, -1, -1);
//		glVertex3f(1, 1, -1);
//		glVertex3f(-1, 1, -1);
//
//		glVertex3f(1, 1, 1);
//		glVertex3f(1, -1, 1);
//		glVertex3f(1, -1, -1);
//		glVertex3f(1, 1, -1);
//
//		glVertex3f(-1, 1, 1);
//		glVertex3f(-1, -1, 1);
//		glVertex3f(-1, -1, -1);
//		glVertex3f(-1, 1, -1);
//		glEnd();
//
//		glPopMatrix();
//
//	
//	glFlush();
//	glutSwapBuffers(); //send image to the screen
//}
//
//int main(int argc, char*argv[]) {
//
//	//initialize GLUT 
//	glutInit(&argc, argv);
//
//	//request double buffering, RGB colors window and a z-buffer
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
//
//	//create a window
//	glutInitWindowSize(600, 600);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow("Space");
//
//	//enable depth
//	glEnable(GL_DEPTH_TEST);
//	//callback functions
//	glutDisplayFunc(display); //display - redraws the scene
//								  //pass control to GLUT for events
//	glutMainLoop();
//
//	return 0; //this line is never reached
//}