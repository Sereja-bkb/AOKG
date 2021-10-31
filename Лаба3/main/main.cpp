#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GraphicObject.h"
#include "Camera.h"

using namespace std;

// для fps
float prevTime = 0.0f;
float crntTime = 0.0f;
unsigned int counter = 0.0f;

// МАССИВ ОБЪЕКТОВ ДЛЯ ВЫВОДА
const int graphicObjectCount = 4;
GraphicObject graphicObjects[graphicObjectCount];

GLfloat M0[16] = { -1,0,0,0, 0,1,0,0, 0,0,-1,0, 4,0,0,1 };
GLfloat M1[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, -4,0,0,1 };
GLfloat M2[16] = { 0,0,1,0, 0,1,0,0, -1,0,0,0, 0,0,-4,1 };
GLfloat M3[16] = { 0,0,-1,0, 0,1,0,0, 1,0,0,0, 0,0,4,1 };

// для fps
LARGE_INTEGER ticks, CounterStart, frequency;
LARGE_INTEGER newTick, oldTick;
LARGE_INTEGER newSimTick, oldSimTick;

// переменная класса Camera
Camera camera;

float GetSimulationTime()
{
	CounterStart = ticks;
	QueryPerformanceCounter(&ticks);
	return (float(ticks.QuadPart - CounterStart.QuadPart)) / frequency.QuadPart;
}

// функция вызывается когда процессор простаивает, т.е. максимально часто
void Simulation()
{
	// ОПРЕДЕЛЕНИЕ ВРЕМЕНИ ПРОШЕДШЕГО С МОМЕНТА ПОСЛЕДНЕЙ СИМУЛЯЦИИ В СЕКУНДАХ
	float Simulation_Time_Passed = GetSimulationTime();
	// ПЕРЕМЕЩЕНИЕ КАМЕРЫ
	bool CameraLeft = GetAsyncKeyState(VK_LEFT);
	bool CameraRight = GetAsyncKeyState(VK_RIGHT);
	bool CameraUp = GetAsyncKeyState(VK_UP);
	bool CameraDown = GetAsyncKeyState(VK_DOWN);
	bool CameraForward = GetAsyncKeyState(VK_ADD);
	bool CameraBackward = GetAsyncKeyState(VK_SUBTRACT);
	camera.setKey(CameraLeft, CameraRight,
		CameraUp, CameraDown,
		CameraForward, CameraBackward);
	camera.simulate(Simulation_Time_Passed);
	// ПЕРЕРИСОВАТЬ ОКНО
	glutPostRedisplay();
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

double thisDelta(LARGE_INTEGER& nTick, LARGE_INTEGER& oTick)
{
	return double(nTick.QuadPart - oTick.QuadPart) / frequency.QuadPart;
}

double getSimTime()
{
	oldSimTick = newSimTick;
	QueryPerformanceCounter(&newSimTick);
	return thisDelta(newSimTick, oldSimTick);
}

void outFps()
{
	QueryPerformanceCounter(&newTick);
	double delta = thisDelta(newTick, oldTick);
	if (delta > 0.5)
	{
		std::string FPS = std::to_string(counter / delta);
		std::string newTitle = FPS + " FPS";
		glutSetWindowTitle(newTitle.c_str());
		counter = 0;
		oldTick = newTick;
	}
}

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void Display(void)
{
	++counter;
	// отчищаем буфер цвета
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);

	// устанавливаем камеру
	camera.apply();

	// выводим объекты
	for (int i = 0; i < graphicObjectCount; i++) {
		graphicObjects[i].draw();
	}

	outFps();

	// смена переднего и заднего буферов
	glutSwapBuffers();
};

// Функция обработки нажатия клавиш
void KeyboardFunc(unsigned char key, int x, int y)
{
	// printf("Key code is %i\n", (unsigned int)key);
};

// инициализация библиотеки GLUT
int main(int argc, char** argv) 
{
	/*graphicObjects[0].setPosition(-2.5f, 0.0f, 0.0f);
	graphicObjects[0].setAngle(0);*/
	graphicObjects[0].setСolor(0.0, 1.0, 0.0);
	for (int i = 0; i < 16; i++) {
		graphicObjects[0].modelMatrix[i] = M0[i];
	}

	/*graphicObjects[1].setPosition(0.0f, 0.0f, 2.5f);
	graphicObjects[1].setAngle(90);*/
	graphicObjects[1].setСolor(1.0, 0.0, 0.0);
	for (int i = 0; i < 16; i++) {
		graphicObjects[1].modelMatrix[i] = M1[i];
	}

	/*graphicObjects[2].setPosition(0.0f, 0.0f, -2.5f);
	graphicObjects[2].setAngle(-90);*/
	graphicObjects[2].setСolor(1.0, 1.0, 0.0);
	for (int i = 0; i < 16; i++) {
		graphicObjects[2].modelMatrix[i] = M2[i];
	}

	/*graphicObjects[3].setPosition(2.5f, 0.0f, 0.0f);
	graphicObjects[3].setAngle(180);*/
	graphicObjects[3].setСolor(0.4, 0, 0.7);
	for (int i = 0; i < 16; i++) {
		graphicObjects[3].modelMatrix[i] = M3[i];
	}

	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// создание окна:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(600, 600);
	// 3. создаем окно
	glutCreateWindow("laba1");

	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(Reshape);

	glutIdleFunc(Simulation);

	QueryPerformanceCounter(&ticks);
	QueryPerformanceFrequency(&frequency);

	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	// glutKeyboardFunc(KeyboardFunc);
	// основной цикл обработки сообщений ОС
	glutMainLoop();
}