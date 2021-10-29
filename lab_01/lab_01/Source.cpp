#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

using namespace std;
using namespace glm;

// список цветов
//float Colors[19] = { 1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };

// список цветов
vec3 color_white = vec3(1, 1, 1);
vec3 color_blue = vec3(0, 0, 1);
vec3 color_red = vec3(1, 0, 0);
vec3 color_yellow = vec3(1, 1, 0);
vec3 color_purple = vec3(1, 0, 1);
//size_t index_color = 0;
double color_numb = 0;
vector<vec3> teapotColors{
	color_red,
	color_blue,
	color_red,
	color_blue,
	color_red,
	color_blue
};
auto it = teapotColors.begin();
int timer = 0;
//переменная, отвечающая за размер выводимого чайника
float size_of_obj = 0.5;
// логическая переменна, отвечающая за максимальный размер чайника
bool max_size = false;

// функция вызывается каждые 20 мс
void Simulation(int value)
{
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
	// эта же функция будет вызвана еще раз через 20 мс
	timer += 20;
	if (timer >= 50)
	{
		//if (index_color == 5)
		//	index_color = 0;
		//else
		//	++index_color;

		if (size_of_obj > 1.5)
			max_size = true;
		if (size_of_obj < 0.6)
			max_size = false;
		if (max_size)
			size_of_obj = size_of_obj - 0.05;
		else size_of_obj = size_of_obj + 0.05;

		if (max_size)
			color_numb = color_numb - 0.05;
		else color_numb = color_numb + 0.05;

		timer = 0;
	}
	glutTimerFunc(20, Simulation, 0);
}

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void Display(void)
{
	// отчищаем буфер цвета
	glClearColor(0.13, 0.5, 0.84, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);

	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 5, 7.5, 0, 0, 0, 0, 1, 0);

	// выводим объект 
	//glColor3f(1, 1 ,Colors[count_color]);
	//glColor3f(teapotColors[index_color][0], teapotColors[index_color][1], teapotColors[index_color][2]);
	glColor3f(color_numb, 0, 0.5);
	glutWireTeapot(size_of_obj);

	// смена переднего и заднего буферов
	glutSwapBuffers();
};

// Функция обработки нажатия клавиш
void KeyboardFunc(unsigned char key, int x, int y)
{

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

int main(int argc, char* argv[])
{
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
	glutCreateWindow("anton-molodec");

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