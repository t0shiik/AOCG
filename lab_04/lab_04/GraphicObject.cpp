#include "GraphicObject.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

GraphicObject::GraphicObject() {};


GraphicObject::GraphicObject(vec3 pos, float a, vec3 col) {
	setPosition(pos);
	setAngle(a);
	setColor(col);
}


void GraphicObject::setPosition(vec3 pos) {
	position[0] = pos[0];
	position[1] = pos[1];
	position[2] = pos[2];
}

vec3 GraphicObject::getPosition() {
	return position;
}


void GraphicObject::setAngle(float a) {
	angle = a;
}

float GraphicObject::getAngle() {
	return angle;
}


void GraphicObject::setColor(vec3 col) {
	color[0] = col[0];
	color[1] = col[1];
	color[2] = col[2];
}

vec3 GraphicObject::getColor() {
	return color;
}

// расчет матрицы modelMatrix на основе position и angle
void GraphicObject::recalculateModelMatrix() {
	modelMatrix[0] = cos(radians(angle));
	modelMatrix[1] = 0;
	modelMatrix[2] = sin(radians(angle));
	modelMatrix[3] = 0;

	modelMatrix[4] = 0;
	modelMatrix[5] = 1;
	modelMatrix[6] = 0;
	modelMatrix[7] = 0;

	modelMatrix[8] = -sin(radians(angle));
	modelMatrix[9] = 0;
	modelMatrix[10] = cos(radians(angle));
	modelMatrix[11] = 0;

	modelMatrix[12] = position[0];
	modelMatrix[13] = position[1];
	modelMatrix[14] = position[2];
	modelMatrix[15] = 1;

}

void GraphicObject::draw() {
	glPushMatrix();
	recalculateModelMatrix();
	glMultMatrixf(modelMatrix);
	glColor3f(color[0], color[1], color[2]);
	glutWireTeapot(1.0);
	glPopMatrix();
}