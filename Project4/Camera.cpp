#include "Extension.h"
using namespace std;

void Camera(float x, float y, float z, float angle1, float angle2,float FARR)
{
	///*
	gluLookAt(
		x - FARR *sin(angle1) * cos(angle2), y - FARR *sin(angle2), z - FARR *cos(angle1) * cos(angle2),
		x, y, z,
		0, 1, 0
	);
	//*/
	/*
	gluLookAt(
		x,y,z,
		x + sin(angle1) * cos(angle2), y + sin(angle2), z + cos(angle1) * cos(angle2),
		0, 1, 0
	);
	//*/
}
