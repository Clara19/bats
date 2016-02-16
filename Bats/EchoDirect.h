//#pragma once
//#include <iostream>
//class EchoDirect {
//private:
//	double sourceLevel, targetStrength, A, c ;
//public:
//	EchoDirect(double e_sourceLevel, double e_targetStrength, double e_A, double c);
//	double getAmplitude(double angle, double distance);
//};	//Front Face of the cube - vertex definition
//
//glBegin(GL_POLYGON);
//glColor3f(0.0, 1.0, 0.0);
//glVertex3f(0.0f, 0.0f, -30.0f);
//glVertex3f(0.0f, 30.0f, -30.0f);
//glVertex3f(30.0f, 30.0f, -30.0f);
//glVertex3f(30.0f, 0.0f, -30.0f);
//glEnd();
//
////Back Face of the cube - vertex definition
//glBegin(GL_POLYGON);
//glColor3f(1.0, 0.0, 0.0);
//glVertex3f(0.0f, 0.0f, 0.0f);
//glVertex3f(0.0f, 30.0f, 0.0f);
//glVertex3f(30.0f, 30.0f, 0.0f);
//glVertex3f(30.0f, 0.0f, 0.0f);
//glEnd();
//
////Right Face of the cube - vertex definition
//glBegin(GL_POLYGON);
//glColor3f(1.0, 0.3, 1.0);
//glVertex3f(30.0f, 0.0f, 0.0f);
//glVertex3f(30.0f, 30.0f, 0.0f);
//glVertex3f(30.0f, 30.0f, -30.0f);
//glVertex3f(30.0f, 0.0f, -30.0f);
//glEnd();
//
////Left Face of the cube - vertex definition
//glBegin(GL_POLYGON);
//glColor3f(0.7, 0.7, 0.2);
//glVertex3f(0.0f, 0.0f, -30.0f);
//glVertex3f(0.0f, 30.0f, -30.0f);
//glVertex3f(0.0f, 30.0f, 0.0f);
//glVertex3f(0.0f, 0.0f, 0.0f);
//glEnd();
//
////Upper Face of the cube - vertex definition
//glBegin(GL_POLYGON);
//glColor3f(0.7, 0.7, 0.7);
//glVertex3f(0.0f, 30.0f, 0.0f);
//glVertex3f(0.0f, 30.0f, -30.0f);
//glVertex3f(30.0f, 30.0f, -30.0f);
//glVertex3f(30.0f, 30.0f, 0.0f);
//glEnd();
//
////Bottom Face of the cube - vertex definition
//glBegin(GL_POLYGON);
//glColor3f(0.8, 0.2, 0.8);
//glVertex3f(0.0f, 0.0f, -30.0f);
//glVertex3f(0.0f, 0.0f, 0.0f);
//glVertex3f(30.0f, 0.0f, 0.0f);
//glVertex3f(30.0f, 0.0f, -30.0f);
//glEnd();