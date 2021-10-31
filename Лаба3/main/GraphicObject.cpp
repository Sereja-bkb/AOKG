#include "GraphicObject.h"

// �����������
GraphicObject::GraphicObject(void)
{
}

// ������ ������� �������
void GraphicObject::setPosition(float x, float y, float z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

// ������ ���� �������� � �������� ������������ ��� OY
void GraphicObject::setAngle(float a)
{
	angle = a;
}

// ������ ���� ������
void GraphicObject::set�olor(float r, float g, float b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

// ������� ������
void GraphicObject::draw(void)
{
	glPushMatrix();
	glMultMatrixf(modelMatrix);
	//glTranslatef(position[0], position[1], position[2]);
	glColor3f(color[0], color[1], color[2]);
	//glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glutWireTeapot(1.0);
	glPopMatrix();
}