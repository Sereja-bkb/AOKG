#include "Camera.h"

Camera::Camera()
{
	r = sqrt(444);
}

Camera::~Camera() {}

void Camera::simulate(float sec)
{
	time = sec;
}

void Camera::setKey(bool left, bool right, bool up, bool down, bool forward, bool backward)
{
	Camera::left = left;
	Camera::right = right;
	Camera::up = up;
	Camera::down = down;
	Camera::forward = forward;
	Camera::backward = backward;

	if (left)
	{
		fi = fi + 90 * time;
	}
	if (right)
	{
		fi = fi + (-90) * time;
	}
	if (up)
	{
		om = min(om + 90 * time, 90);
	}
	if (down)
	{
		if (om > 0)
		{
			om = om + (-90) * time;
		}
	}
	if (forward)
	{
		if (r > 8)
		{
			r = r + (-30) * time;
		}
	}
	if (backward)
	{
		if (r < 30)
		{
			r = r + 30 * time;
		}
	}
}

void Camera::apply()
{
	float fiR = fi * 0.017;
	float omR = om * 0.017;

	x = r * cos(fiR) * cos(omR);
	y = r * sin(omR);
	z = r * sin(fiR) * cos(omR);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
}