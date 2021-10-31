#pragma once

#include <Windows.h>
#include "GL/freeglut.h"
#include "math.h"

class GraphicObject
{
private:
	// Позиция и угол поворота для объекта
	GLfloat position[3];
	GLfloat angle;
	// Цвет модели
	GLfloat color[3];
public:
	// Матрица модели (расположение объекта) ‐ чтоб не вычислять каждый раз
	GLfloat modelMatrix[16];
	// Конструктор
	GraphicObject(void);
	// Задать позицию объекта
	void setPosition(float x, float y, float z);
	// Задать угол поворота в градусах относительно оси OY
	void setAngle(float a);
	// Задать цвет модели
	void setСolor(float r, float g, float b);
	// Вывести объект
	void draw(void);
};