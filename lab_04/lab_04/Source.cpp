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

// ������ ������
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


// ������� ���������� ������ 20 ��
void Simulation()
{
	// ����������� ������� ���������
	float simulationTime = getSimulationTime();

	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();

	// ��� �� ������� ����� ������� ��� ��� ����� 20 ��
	//glutTimerFunc(20, Simulation, 0);
}

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay
void Display(void)
{
	// �������� ����� ����� � ����� �������
	glClearColor(0.15, 0.5, 0.80, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);

	// ������������� ������
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(15, 15, 15, 0, 0, 0, 0, 1, 0);

	//������� ��� �������
	for (auto& go : graphicObjects) {
		go.draw();
	}

	// ����� ��������� � ������� �������
	glutSwapBuffers();
};

// ������� ��������� ������� ������
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", key);
	// ��� �������� ������ ������ �������� ������ ������������
	//switch (static_cast<char>(key)) {
	//case 'w':
	//	camera.rotateUpDown(5.0);
	//	break;
	//case 's':
	//	camera.rotateUpDown(-5.0);
	//	break;
	//case 'a':
	//	camera.rotateLeftRight(5.0);
	//	break;
	//case 'd':
	//	camera.rotateLeftRight(-5.0);
	//	break;
	//case '+':
	//	camera.zoomInOut(0.2);
	//	break;
	//case '-':
	//	camera.zoomInOut(-0.2);
	//	break;
	//}
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

int main(int argc, char* argv[]) {

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
	glutCreateWindow("anton napisal camery");

	// ������������� �������, ������� ����� ���������� ��� ����������� ����
	glutDisplayFunc(Display);

	// ������������� �������, ������� ����� ���������� ��� ��������� �������� ����
	glutReshapeFunc(Reshape);

	// ������������� ������� ������� ����� ������� ����� 20 ��
	//glutTimerFunc(20, Simulation, 0);
	// 
	// �������, ������� ���������� ��������
	glutIdleFunc(Simulation);

	// ������������� �������, ������� ����� ���������� ��� ������� �� �������
	glutKeyboardFunc(KeyboardFunc);

	// �������� ���� ��������� ��������� ��
	glutMainLoop();

}