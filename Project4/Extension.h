#include <iostream>

#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include <vector>

#include <chrono>
#include <string>
#include <mmsystem.h>

#define WIDTH 1280 
#define HEIGHT 720 
#define CAR_ROTATION_SPEED 0.01
#define CAMERA_ROTATION_SPEED 0.001
#define _debug(x) '['<< #x << ':' << x << ']'
#define _USE_MATH_DEFINES

void Camera(float x, float y, float z, float angle1, float angle2, float FARR); //Camera.cpp

void DrawCar(float x, float y, float z, float angle1, float angle2, float r, float g, float b); //Drawing.cpp

void Drawing(float x, float y, float z, float angle1, float angle2); //Drawing.cpp

void DrawMainMenu(int SelectedButton); //Drawing.cpp

void DrawHelpMenu(); //Drawing.cpp

void DrawSettingMenu(int SelectedButton, int FullScreenStatus, int SoundOnStatus, int ColorIndex); //Drawing.cpp

void DrawInfoMenu(); //Drawing.cpp

void DrawPauseMenu(); //Drawing.cpp

void DrawLevelMenu(int SelectedLevelButton, int UnlockedLevel);//Drawing.cpp

void DrawWinMenu();//Drawing.cpp

void DrawLoseMenu();//Drawing.cpp

void TakeTexture(float r, float g, float b, float x1, float y1, float x2, float y2, float v1_x, float v1_y, float v1_z, float v2_x, float v2_y, float v2_z, float v3_x, float v3_y, float v3_z, float v4_x, float v4_y, float v4_z); //Drawing.cpp


