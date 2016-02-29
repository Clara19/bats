//// Std. Includes
//#include <string>
//#include <algorithm>
//using namespace std;
//
//// GLEW
//#define GLEW_STATIC
//#include <GL/glew.h>
//
//
//
//// GL includes
//#include "Shader.h"
////#include "Camera.h"
//#pragma once
//
//// Std. Includes
//#include <vector>
//#include "Model_OBJ.h"
//Model_OBJ obj;
//// GLM Mathemtics
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//// Other Libs
//#include "SOIL.h"
//#include <GL/glut.h>
//
//// Properties
//GLuint screenWidth = 800, screenHeight = 600;
//GLuint cubemapTexture;
//
//GLuint loadTexture(GLchar* path);
//GLuint loadCubemap(vector<const GLchar*> faces);
//
//// Camera
////Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//bool keys[1024];
//GLfloat lastX = 400, lastY = 300;
//bool firstMouse = true;
//
//GLfloat deltaTime = 0.0f;
//GLfloat lastFrame = 0.0f;
//
//
//GLuint skyboxVAO, skyboxVBO;
//
//void display() {
//	Shader shader("cubemaps.vs", "cubemaps.frag");
//	Shader skyboxShader("skybox.vs", "skybox.frag");
//	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//	// Draw skybox first
//	glDepthMask(GL_FALSE);// Remember to turn depth writing off
//	skyboxShader.Use();
//	glm::mat4 view = glm::mat4(glm::mat3(glm::lookAt(glm::vec3(2.f, 2.f, 2.f), glm::vec3(-15.f, 15.f, 0.f), glm::vec3(0.f, 1.f, 0.f))));// Remove any translation component of the view matrix
//	glm::mat4 projection = glm::perspective(90.0f, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
//	glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
//	glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//	// skybox cube
//	glBindVertexArray(skyboxVAO);
//	glActiveTexture(GL_TEXTURE0);
//	glUniform1i(glGetUniformLocation(shader.Program, "skybox"), 0);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//	glBindVertexArray(0);
//	glDepthMask(GL_TRUE);
//	glFlush();
//	glutSwapBuffers();
//
//}
//// The MAIN function, from here we start our application and run our Game loop
//int main(int argc, char*argv[])
//{
//	// Init GLFW
//	glutInit(&argc, argv);
//
//	//request double buffering, RGB colors window and a z-buffer
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
//
//	//create a window
//	glutInitWindowSize(1200, 600);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow("Bats");
//	glutDisplayFunc(display);
//
//	glewExperimental = GL_TRUE;
//	glewInit();
//
//
//	// Define the viewport dimensions
//	glViewport(0, 0, screenWidth, screenHeight);
//
//	// Setup some OpenGL options
//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LESS);
//
//	// Setup and compile our shaders
//	
//
//#pragma region "object_initialization"
//	// Set the object data (buffers, vertex attributes)
//	
//	GLfloat skyboxVertices[] = {
//		// Positions          
//		-1.0f,  1.0f, -1.0f,
//		-1.0f, -1.0f, -1.0f,
//		1.0f, -1.0f, -1.0f,
//		1.0f, -1.0f, -1.0f,
//		1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//
//		-1.0f, -1.0f,  1.0f,
//		-1.0f, -1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f,  1.0f,
//		-1.0f, -1.0f,  1.0f,
//
//		1.0f, -1.0f, -1.0f,
//		1.0f, -1.0f,  1.0f,
//		1.0f,  1.0f,  1.0f,
//		1.0f,  1.0f,  1.0f,
//		1.0f,  1.0f, -1.0f,
//		1.0f, -1.0f, -1.0f,
//
//		-1.0f, -1.0f,  1.0f,
//		-1.0f,  1.0f,  1.0f,
//		1.0f,  1.0f,  1.0f,
//		1.0f,  1.0f,  1.0f,
//		1.0f, -1.0f,  1.0f,
//		-1.0f, -1.0f,  1.0f,
//
//		-1.0f,  1.0f, -1.0f,
//		1.0f,  1.0f, -1.0f,
//		1.0f,  1.0f,  1.0f,
//		1.0f,  1.0f,  1.0f,
//		-1.0f,  1.0f,  1.0f,
//		-1.0f,  1.0f, -1.0f,
//
//		-1.0f, -1.0f, -1.0f,
//		-1.0f, -1.0f,  1.0f,
//		1.0f, -1.0f, -1.0f,
//		1.0f, -1.0f, -1.0f,
//		-1.0f, -1.0f,  1.0f,
//		1.0f, -1.0f,  1.0f
//	};
//
//	// Setup skybox VAO
//
//	glGenVertexArrays(1, &skyboxVAO);
//	glGenBuffers(1, &skyboxVBO);
//	glBindVertexArray(skyboxVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
//	glBindVertexArray(0);
//
//	// Load textures
//#pragma endregion
//
//	// Cubemap (Skybox)
//	vector<const GLchar*> faces;
//	faces.push_back("skybox/right.jpg");
//	faces.push_back("skybox/left.jpg");
//	faces.push_back("skybox/top.jpg");
//	faces.push_back("skybox/bottom.jpg");
//	faces.push_back("skybox/back.jpg");
//	faces.push_back("skybox/front.jpg");
//	cubemapTexture = loadCubemap(faces);
//
//	
//
//	// Draw as wireframe
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	// Game loop
//
//
//		// Clear buffers
//		
//		//// Then draw scene as normal
//		//shader.Use();
//		//glm::mat4 model;
//		//view = glm::lookAt(glm::vec3(2.f, 2.f, 2.f), glm::vec3(15.f, 2.f, -15.f), glm::vec3(0.f, 1.f, 0.f));
//
//		//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
//		//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
//		//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//		//// Cubes
//		//glBindVertexArray(0);
//		////glTranslatef(2, 2, -2);
//		//glRotatef(90, 0, 1, 0);
//		//glPointSize(10);		// Swap the buffers
//		//obj.Draw(0.2f, 0.1f, 0.2f, 1.0f);
//		//glBegin(GL_POINTS);
//		//glVertex3f(0, 0,0);
//		//glEnd();		
//		glutMainLoop();
//	return 0;
//}
//
//// Loads a cubemap texture from 6 individual texture faces
//// Order should be:
//// +X (right)
//// -X (left)
//// +Y (top)
//// -Y (bottom)
//// +Z (front) 
//// -Z (back)
//GLuint loadCubemap(vector<const GLchar*> faces)
//{
//	GLuint textureID;
//	glGenTextures(1, &textureID);
//
//	int width, height;
//	unsigned char* image;
//
//	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//	for (GLuint i = 0; i < faces.size(); i++)
//	{
//		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
//		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//		SOIL_free_image_data(image);
//	}
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
//
//	return textureID;
//}
//
//
//// This function loads a texture from file. Note: texture loading functions like these are usually 
//// managed by a 'Resource Manager' that manages all resources (like textures, models, audio). 
//// For learning purposes we'll just define it as a utility function.
//GLuint loadTexture(GLchar* path)
//{
//	//Generate texture ID and load texture data 
//	GLuint textureID;
//	glGenTextures(1, &textureID);
//	int width, height;
//	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
//	// Assign texture to ID
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//
//	// Parameters
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	SOIL_free_image_data(image);
//	return textureID;
//}
//
//#pragma region "User input"
//
//
//#pragma endregion