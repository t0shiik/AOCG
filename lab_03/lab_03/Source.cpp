#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "GraphicObject.h"

using namespace std;
using namespace glm;

// список цветов
vec3 color_black = vec3(0, 0, 0);
vec3 color_white = vec3(1, 1, 1);
vec3 color_blue = vec3(0, 0, 1);
vec3 color_red = vec3(1, 0, 0);
vec3 color_yellow = vec3(1, 1, 0);
vec3 color_purple = vec3(1, 0, 1);
vec3 color_green = vec3(0, 1, 0);
vector<vec3> teapotColors{
	color_white,
	color_blue,
	color_red,
	color_yellow,
	color_purple,
	color_black,
	color_green
};

vec3 pos1 = vec3(-3.0, 0.0, 0.0);
vec3 pos2 = vec3(0.0, 0.0, 3.0);
vec3 pos3 = vec3(0.0, 0.0, -3.0);
vec3 pos4 = vec3(3.0, 0.0, 0.0);

GraphicObject obj_1(pos1, 0.0, color_blue);
GraphicObject obj_2(pos2, 270, color_black);
GraphicObject obj_3(pos3, 90, color_green);
GraphicObject obj_4(pos4, 180, color_red);

vector<GraphicObject> graphicObjects{
	obj_1,
	obj_2,
	obj_3,
	obj_4
};

// функция вызывается каждые 20 мс
void Simulation(int value)
{
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();

	// эта же функция будет вызвана еще раз через 20 мс
	glutTimerFunc(20, Simulation, 0);
}

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void Display(void)
{
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.15, 0.5, 0.80, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);

	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(15, 15, 15, 0, 0, 0, 0, 1, 0);

	//выводим все объекты
	for (auto& go : graphicObjects) {
		go.draw();
	}

	// смена переднего и заднего буферов
	glutSwapBuffers();
};

// Функция обработки нажатия клавиш
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", (unsigned int)key);
};

void Reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

int main(int argc, char* argv[]) {

	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// создание окна:
	// устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);

	// устанавливаем размер окна
	glutInitWindowSize(850, 500);

	// создаем окно
	glutCreateWindow("anton napisal 3 laby");

	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);

	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(Reshape);

	// устанавливаем функцию которая будет вызвана через 20 мс
	glutTimerFunc(20, Simulation, 0);

	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(KeyboardFunc);

	// основной цикл обработки сообщений ОС
	glutMainLoop();

}