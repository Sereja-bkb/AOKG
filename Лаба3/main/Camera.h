#pragma once

#include <Windows.h>
#include "GL/freeglut.h"
#include "math.h"

class Camera
{
	// необходимые свойства
	float x, y, z, r, fi = 45, om = 45, time;
	bool left, right, up, down, forward, backward;
public:
	// конструктор по умолчанию
	Camera(void);
	// деструктор ‐ сохранение новых параметров камеры
	~Camera(void);
	// установка признаков нажатых клавиш
	void setKey(bool left, bool right, bool up, bool down, bool forward, bool backward);
	// движение камеры в ранее выбранном направлении
	// параметр ‐ количество секунд прошедших с момента последнего вызова
	void simulate(float sec);
	// функция для установки матрицы камеры
	void apply();
};