#pragma once
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ОДНОГО ГРАФИЧЕСКОГО ОБЪЕКТА
class GraphicObject
{
public:
	// Конструктор
	GraphicObject();
	GraphicObject(vec3 pos, float a, vec3 col);
	// Установка и получение позиции объекта
	void setPosition(vec3 pos);
	vec3 getPosition();
	// Установка и получения угла поворота в градусах
	// поворот осуществляется в горизонтальной плоскости
	// вокруг оси Oy по часовой стрелке
	void setAngle(float grad);
	float getAngle();
	// Установка текущего цвета объекта
	void setColor(vec3 col);
	vec3 getColor();
	// Вывести объект
	void draw();
private:
	// Позиция объекта в глобальной системе координат
	vec3 position;
	// Угол поворота в горизонтальной плоскости (в градусах)
	float angle;
	// Цвет модели
	vec3 color;
	// Матрица модели - чтоб не вычислять каждый раз
	GLfloat modelMatrix[16];
private:
	// расчет матрицы modelMatrix на основе position и angle
	void recalculateModelMatrix();
};