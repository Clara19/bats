#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

// Std. Includes
#include <string>
#include <algorithm>
using namespace std;

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#pragma once

// Std. Includes
#include <vector>


// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL.h"

#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "Model_OBJ.h"
#define PI 3.14159265
#include "BatManager.h"
#include "VonMisesDist.h"
int rotate_Y; //used to rotate the cube about the Y-axis
int rotate_X; //used to rotate the cube about the X-axis
			  // Display list for coordinate axis 
int translateX, translateY;
GLfloat zoom = 1;
GLsizei width = 1200, height = 800;
Echo echo, echo1;
BatManager *bat, *bat1;
Model_OBJ obj, obj1;
int noFrames, batView = 0, echos = 0;
bool seesBat0, seesBat1;
int up = 1;
GLuint cubemapTexture;
#pragma region "object_initialization"
// Set the object data (buffers, vertex attributes)

GLfloat skyboxVertices[] = {
	// Positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};
const GLfloat vertices[] = {
	-0.25f,  -0.25f,
	0.0f,    0.0f,
	0.0f,    0.5f,
	0.25f, -0.25f,
};

GLuint loadTexture(GLchar* path);
GLuint loadCubemap(vector<const GLchar*> faces);
GLuint skyboxVAO, skyboxVBO;

int AXIS_SIZE = 200;
int axisEnabled = 1;
void DrawDisk(float cx, float cy, float z, float r, int num_segments)
{

	glLineWidth(6);

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		if(z==NULL)
			glVertex2f(x + cx,y + cy);//output vertex 
		else
			glVertex3f(x + cx,z, y + cy);//output vertex 

	}
	glEnd();
	glLineWidth(1);

}
//the display function draws the scene and redraws it
void timerFunc(int value) {
	if (echos == 0)
		noFrames += 1;
	if (noFrames % 5 == 0 && echos == 0) {
		echos = 5;
		seesBat1 = (*bat).echolocateBat(bat1);
		seesBat0 = (*bat1).echolocateBat(bat);

	}

	if (noFrames < 1000)
		if(echos > 0)
			glutTimerFunc(50, timerFunc, 0);
		else 
			glutTimerFunc(250, timerFunc, 0);
	glutPostRedisplay();
	if(echos>0)
		echos--;

}


void display() {

	int seesOtherBat;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgramObjectARB(0);
	if (echos == 0) {
		(*bat).updateBat();
		(*bat1).updateBat();
	}
	
	//std::cout << bat->currentState.speed << " " << bat->currentState.heading << " " << bat->currentState.x << " " << bat->currentState.y << std::endl;
	BatManager* mainBat, *otherBat;
	if (batView) {
		mainBat = bat1;
		otherBat = bat;
		seesOtherBat = seesBat0;
	}
	else {
		mainBat = bat;
		otherBat = bat1;
		seesOtherBat = seesBat1;
	}
	glEnable(GL_SCISSOR_TEST);


	GLfloat aspect = ((GLfloat)width) / 2 / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(width / 2, 0, width / 2, height);

	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix
	if (width >= height) {
		// aspect >= 1, set the height from -1 to 1, with larger width
		gluOrtho2D(-40.0 * aspect * zoom, 40.0 * aspect * zoom, -40.0* zoom, 40.0* zoom);
	}
	else {
		// aspect < 1, set the width to -1 to 1, with larger height
		gluOrtho2D(-40.0* zoom, 40.0* zoom, -40.0 / aspect* zoom, 40.0 / aspect* zoom);
	}
	//glScissor(((float)width / 2), 0, width, height);

	glMatrixMode(GL_MODELVIEW);
	//std::cout << bat->currentState.speed << " " << bat->currentState.heading << " " << bat->currentState.x << " " << bat->currentState.y << std::endl;
	glClearColor(0.0, 0.0, 0.0, 0.0);
       // Clear the color buffer (background)
	glPushMatrix();
	glTranslatef(translateX, translateY, 0);
	
	glPushMatrix();
	glTranslatef(bat->currentState.x, bat->currentState.y, 0);
	glRotatef(bat->currentState.heading * 180 / PI, 0, 0, 1);

	glBegin(GL_TRIANGLES);
	if(bat1->leader == bat)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(1.0f, 0.0f, 1.0f);
	glVertex2f(1.75, 0);
	glVertex2f(0, 0.5);
	glVertex2f(0, -0.5);
	glEnd();
	glPopMatrix();
	glPointSize(2.0 / zoom);
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
	if (bat->leader == bat1)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(1.0f, 0.0f, 1.0f);
	glVertex2f(1.75, 0);
	glVertex2f(0, 0.5);
	glVertex2f(0, -0.5);
	glEnd();
	glPopMatrix();
	glPointSize(2.0 / zoom);
	glBegin(GL_POINTS);
	for (auto const &it : bat1->prevStates) {
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex2f(it.second.x, it.second.y);
	}
	glEnd();
	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_LINES);
	for (GLfloat i = -100; i <= 100; i += 1.5) {
		glVertex2f(i, 100); glVertex2f(i, -100);
		glVertex2f(100, i); glVertex2f(-100, i);
	}
	glEnd();

	glPopMatrix();
	Shader shader("cubemaps.vs", "cubemaps.frag");
	Shader skyboxShader("skybox.vs", "skybox.frag");
	glViewport(0, (GLsizei)height / 2, (GLsizei)width/2 , (GLsizei)height/2);
	//glScissor(0, 0, (float)width, height);
	//enable depth



	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// Setup skybox VAO
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	glDepthMask(GL_FALSE);// Remember to turn depth writing off
	skyboxShader.Use();
	glm::mat4 view = glm::mat4(glm::mat3(glm::lookAt(glm::vec3((mainBat->currentState.x) , 0.0, -(mainBat->currentState.y)),
		glm::vec3((mainBat->currentState.x) + cos(mainBat->currentState.heading),0.0, -(mainBat->currentState.y) - sin(mainBat->currentState.heading)),
		glm::vec3(0.f, 1.f, 0.f))));// Remove any translation component of the view matrix
	glm::mat4 projection = glm::perspective(90.0f, (float)width / (float)height, 0.02f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(shader.Program, "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDepthMask(GL_TRUE);
	
	glUseProgramObjectARB(0);
	//// Cubes
	glPushMatrix();
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLfloat amb_light[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat diffuse[] = { 0.2, 0.2, 0.2, 1 };
	GLfloat specular[] = { 0.3, 0.3, 0.1, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glPushMatrix();
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix
	gluPerspective(120, ((float)width ) / (float)height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt((mainBat->currentState.x), 0.5, -(mainBat->currentState.y),
		(mainBat->currentState.x) + cos(mainBat->currentState.heading),
		0.3, -(mainBat->currentState.y) - sin(mainBat->currentState.heading), 0.0, 1.0, 0.0);
	if (echos > 0)
		DrawDisk((mainBat->currentState.x) + 2*cos(mainBat->currentState.heading),  -(mainBat->currentState.y) - 2*sin(mainBat->currentState.heading), 0.2 - up*0.02, 2 + (5 - echos)*2 / 5, 100);
	//obj.Draw(0.1f, 0.1f, 0.1f, 1);
	glColor4f(1.0, 1.0, 1.0, 0.5);
	glBegin(GL_LINES);
	for (GLfloat i = -100; i <= 100; i +=1) {
		glVertex3f(i, -1, 100); glVertex3f(i, -1 + 0.05*up, -100);
		glVertex3f(100, -1, i); glVertex3f(-100, -1 + 0.05*up, i);
	}
	glEnd();
	glPushMatrix();
	GLfloat alpha;

	glTranslatef(otherBat->currentState.x, 0.2 - up*0.02, -otherBat->currentState.y);

	glRotatef(otherBat->currentState.heading * 180/PI, 0.0, 1.0, 0.0);
	glRotatef(270, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glRotatef(350, 1, 0, 0);

	   glScalef(0.3, 0.2, 0.2); 
	   if (seesOtherBat)
	   	alpha = 1;
	   else
	   	alpha = 0.5;
	   if (up>0)
		   obj.Draw(alpha, 0.1f / alpha, 0.1f / alpha, alpha);
	   else
		   obj1.Draw(alpha, 0.1f / alpha, 0.1f / alpha, alpha);
	   
		glPopMatrix();


	glPopMatrix();
	//
	glViewport(0, 0, (GLsizei)width/2, (GLsizei)height/2);
	//glScissor(0, 0, (float)width, height);
	//enable depth



	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// Setup skybox VAO
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	glDepthMask(GL_FALSE);// Remember to turn depth writing off
	skyboxShader.Use();
	view = glm::mat4(glm::mat3(glm::lookAt(glm::vec3((mainBat->currentState.x), 0.0, -(mainBat->currentState.y)),
		glm::vec3((mainBat->currentState.x) - cos(mainBat->currentState.heading), 0.0, -(mainBat->currentState.y) + sin(mainBat->currentState.heading)),
		glm::vec3(0.f, 1.f, 0.f))));// Remove any translation component of the view matrix
	projection = glm::perspective(120.0f, (float)width / (float)height, 0.05f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(shader.Program, "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDepthMask(GL_TRUE);

	glUseProgramObjectARB(0);
	//// Cubes
	glPushMatrix();
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix
	gluPerspective(120, ((float)width) / (float)height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt((mainBat->currentState.x), 0.5, -(mainBat->currentState.y),
		(mainBat->currentState.x) - cos(mainBat->currentState.heading),
		0.3, -(mainBat->currentState.y) + sin(mainBat->currentState.heading), 0.0, 1.0, 0.0);
	if (echos > 0)
		DrawDisk((mainBat->currentState.x) + 2 * cos(mainBat->currentState.heading), -(mainBat->currentState.y) - 2 * sin(mainBat->currentState.heading), 0.2 - up*0.02,2 + (5 - echos)*2 / 5, 100);
	glColor4f(1.0, 1.0, 1.0, 0.5);
	glBegin(GL_LINES);
	for (GLfloat i = -100; i <= 100; i += 1) {
		glVertex3f(i, -1, 100); glVertex3f(i, -1 + 0.05*up, -100);
		glVertex3f(100, -1, i); glVertex3f(-100, -1 + 0.05*up, i);
	}
	glEnd();
	glPushMatrix();

	glTranslatef((otherBat->currentState.x), 0.2 - up*0.02, -(otherBat->currentState.y));

	glRotatef(otherBat->currentState.heading * 180 / PI, 0.0, 1.0, 0.0);
	glRotatef(270, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glRotatef(330, 1, 0, 0);

	glScalef(0.3, 0.2, 0.2);
	if (seesOtherBat)
		alpha = 1;
	else
		alpha = 0.5;
	if (up>0 )
		obj.Draw(alpha, 0.1f / alpha, 0.1f / alpha, alpha);
	else
		obj1.Draw(alpha, 0.1f / alpha, 0.1f / alpha, alpha);

	glPopMatrix();

	glPopMatrix();

	glDisable(GL_SCISSOR_TEST);

	//// If enabled, draw coordinate axis
	if(echos==0)
		up *= -1;
	glFlush();
	glutSwapBuffers(); //send image to the screen
}

void reshape(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);

}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'q')
		batView = !batView;
	if (key == 'a')
		translateX += 5;
	if (key == 's')
		translateX -= 5;
	if (key == 'w')
		translateY += 5;
	if (key == 'z')
		translateY -= 5;
	if (key == 'x')
		zoom *= 5.0/4;
	if (key == 'c')
		zoom *= 4.0/5;
}


int main(int argc, char*argv[]) {

	echo.sourceLevel = 110, echo.targetStrength = -10, echo.A = 16, echo.c = -1.28;
	echo1.sourceLevel = 110, echo1.targetStrength = -10, echo1.A = 16, echo1.c = -1.28;
	bat = new BatManager(10, 0, 10, echo);
	bat1 = new BatManager(10, 0, 10, echo1);
	//initialize GLUT 
	glutInit(&argc, argv);

	//request double buffering, RGB colors window and a z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);

	//create a window
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bats");


	//callback functions
	glutDisplayFunc(display); //display - redraws the scene
	glutKeyboardFunc(keyboard);
	glutTimerFunc(100, timerFunc, 0);
	glutReshapeFunc(reshape);

	glewExperimental = GL_TRUE;
	glewInit();
	


	// Load textures
#pragma endregion

	// Cubemap (Skybox)
	vector<const GLchar*> faces;
	faces.push_back("skybox/3.bmp");
	faces.push_back("skybox/1.bmp");
	faces.push_back("skybox/6.bmp");
	faces.push_back("skybox/5.bmp");
	faces.push_back("skybox/2.bmp");
	faces.push_back("skybox/4.bmp");
	cubemapTexture = loadCubemap(faces);
	obj.Load("batt2.obj");
	obj1.Load("batt3.obj");
	//glutSpecialFunc(specialKeys); //special - allows interaction with specialkeys
	glutMainLoop();

	return 0; //this line is never reached
}
GLuint loadCubemap(vector<const GLchar*> faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}
GLuint loadTexture(GLchar* path)
{
	//Generate texture ID and load texture data 
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	return textureID;
}