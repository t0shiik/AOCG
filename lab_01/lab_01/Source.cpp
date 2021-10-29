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

// ������ ������
//float Colors[19] = { 1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };

// ������ ������
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
//����������, ���������� �� ������ ���������� �������
float size_of_obj = 0.5;
// ���������� ���������, ���������� �� ������������ ������ �������
bool max_size = false;

// ������� ���������� ������ 20 ��
void Simulation(int value)
{
	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();
	// ��� �� ������� ����� ������� ��� ��� ����� 20 ��
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

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay
void Display(void)
{
	// �������� ����� �����
	glClearColor(0.13, 0.5, 0.84, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);

	// ������������� ������
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 5, 7.5, 0, 0, 0, 0, 1, 0);

	// ������� ������ 
	//glColor3f(1, 1 ,Colors[count_color]);
	//glColor3f(teapotColors[index_color][0], teapotColors[index_color][1], teapotColors[index_color][2]);
	glColor3f(color_numb, 0, 0.5);
	glutWireTeapot(size_of_obj);

	// ����� ��������� � ������� �������
	glutSwapBuffers();
};

// ������� ��������� ������� ������
void KeyboardFunc(unsigned char key, int x, int y)
{

};

void Reshape(int w, int h)
{
	// ���������� ����� ������� ���������, ������ ���� ������� ����
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// ���������� ������� �������� � ���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

int main(int argc, char* argv[])
{
	// ������������� ���������� GLUT
	glutInit(&argc, argv);
	// ������������� ������� (������ ������)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// �������� ����:
	// ������������� ������� ����� ���� ����
	glutInitWindowPosition(200, 200);

	// ������������� ������ ����
	glutInitWindowSize(850, 500);

	// ������� ����
	glutCreateWindow("anton-molodec");

	// ������������� �������, ������� ����� ���������� ��� ����������� ����
	glutDisplayFunc(Display);

	// ������������� �������, ������� ����� ���������� ��� ��������� �������� ����
	glutReshapeFunc(Reshape);

	// ������������� ������� ������� ����� ������� ����� 20 ��
	glutTimerFunc(20, Simulation, 0);

	// ������������� �������, ������� ����� ���������� ��� ������� �� �������
	glutKeyboardFunc(KeyboardFunc);

	// �������� ���� ��������� ��������� ��
	glutMainLoop();

}