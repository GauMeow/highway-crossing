#include "Extension.h"
#include <math.h>
//#include <string>
using namespace std;
void renderBitmapString(float x, float y, float z, void* font, string s) {
	glRasterPos3f(x, y, z);
	for (int i = 0; i < s.size(); ++i) {
		glutBitmapCharacter(font, s[i]);
	}
}
void TakeTexture(float r, float g, float b, float x1, float y1, float x2, float y2, float v1_x, float v1_y, float v1_z, float v2_x, float v2_y, float v2_z, float v3_x, float v3_y, float v3_z, float v4_x, float v4_y, float v4_z)
{
	x1 *= 32; y1 *= 32;
	x2 *= 32; y2 *= 32;
	glColor3f(r, g, b);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(x1/ 2048, y1/ 2048);
	glVertex3f(v1_x, v1_y, v1_z);
	glTexCoord2f(x1/ 2048, y2/ 2048);
	glVertex3f(v2_x, v2_y, v2_z);
	glTexCoord2f(x2 / 2048, y2/ 2048);
	glVertex3f(v3_x, v3_y, v3_z);
	glTexCoord2f(x2/ 2048, y1/ 2048);
	glVertex3f(v4_x, v4_y, v4_z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void DrawMainMenu(int SelectedButton)
{
	//renderBitmapString(0, 0, 0, GLUT_BITMAP_TIMES_ROMAN_24, "PLAYaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	float PlayButtonColor = 1, HelpButtonColor = 1, SettingButtonColor = 1, InfoButtonColor = 1;
	if (SelectedButton == 1) PlayButtonColor = 0.9;
	if (SelectedButton == 2) HelpButtonColor = 0.9;
	if (SelectedButton == 3) SettingButtonColor = 0.9;
	if (SelectedButton == 4) InfoButtonColor = 0.9;
	TakeTexture(
		1,1,1,
		32,23,43,25,
		-5, 0, 3,
		-5, 0, 5,
		5, 0, 5,
		5, 0, 3
	);
	TakeTexture( //Play button
		PlayButtonColor, PlayButtonColor, PlayButtonColor,
		2, 10, 7, 12,
		-2.5, 0, 0.5,
		-2.5, 0, 2.5,
		2.5, 0, 2.5,
		2.5, 0, 0.5
	);
	TakeTexture( //Help button
		HelpButtonColor, HelpButtonColor, HelpButtonColor,
		2, 13, 7, 15,
		-2.5, 0, -2,
		-2.5, 0, 0,
		2.5, 0, 0,
		2.5, 0, -2
	);
	TakeTexture( //Setting button
		SettingButtonColor, SettingButtonColor, SettingButtonColor,
		8, 10, 10, 12,
		-3, 0, -4.5,
		-3, 0, -3,
		-1.5, 0, -3,
		-1.5, 0, -4.5
	);
	TakeTexture( //Info button
		InfoButtonColor, InfoButtonColor, InfoButtonColor,
		11, 10, 13, 12,
		1.5, 0, -4.5,
		1.5, 0, -3,
		3, 0, -3,
		3, 0, -4.5
	);
	TakeTexture(
		1, 1, 1,
		10,10,11,11,
		-2.5, 0, -0.5,
		-2.5, 0, 1.5,
		2.5, 0, 1.5,
		2.5, 0, -0.5
	);
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
	glutSwapBuffers();
}
void DrawHelpMenu()
{
	glColor3f(0, 0, 0);
	//renderBitmapString(-2, 0, 2, GLUT_BITMAP_TIMES_ROMAN_24, "W,A,S,D to move");
	//renderBitmapString(-2, 0, 1, GLUT_BITMAP_TIMES_ROMAN_24, "You will win if you reach 2222 points.");
	//renderBitmapString(-2, 0, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Press any key to exit");
	TakeTexture(1, 1, 1, //How to play
		20, 4, 28, 6,
		-4, 0, 3.5,
		-4, 0, 5.5,
		4, 0, 5.5,
		4, 0, 3.5);
	TakeTexture(1, 1, 1, //Screen
		2, 20, 18, 29,
		-8.5, 0.1, -5.5,
		-8.5, 0.1, 3.5,
		8.5, 0.1, 3.5,
		8.5, 0.1, -5.5);
	TakeTexture(1, 1, 1, // WASD to ...
		30, 4, 42, 12,
		-6, 0, -5,
		-6, 0, 3,
		6, 0, 3,
		6, 0, -5);
	glutSwapBuffers();
}
void DrawSettingMenu(int SelectedButton, int FullScreenStatus, int SoundOnStatus, int ColorIndex)
{
	glColor3f(0, 0, 0);
	//renderBitmapString(0, 0, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Setting");
	TakeTexture(1,1,1, //Setting
		20, 1, 28, 3,
		-4, 0, 3,
		-4, 0, 5,
		4, 0, 5,
		4, 0, 3);
	if (SelectedButton == 1)
		TakeTexture(0.9, 0.9, 0.9, //Fullscreen?
			18, 12, 30, 15,
			-7, 0, -0.5,
			-7, 0, 2.5,
			5, 0, 2.5,
			5, 0, -0.5);
	else
		TakeTexture(1, 1, 1, //Fullscreen?
			18, 12, 30, 15,
			-7, 0, -0.5,
			-7, 0, 2.5,
			5, 0, 2.5,
			5, 0, -0.5);
	if (FullScreenStatus == 0)
		TakeTexture(1, 1, 1, //|X|
			16, 13, 17, 14,
			6, 0, 0.5,
			6, 0, 1.5,
			7, 0, 1.5,
			7, 0, 0.5);
	else
		TakeTexture(1, 1, 1, //|v|
			16, 14, 17, 15,
			6, 0, 0.5,
			6, 0, 1.5,
			7, 0, 1.5,
			7, 0, 0.5);
	if (SoundOnStatus == 0)
	if (SelectedButton == 2)
		TakeTexture(0.9, 0.9, 0.9, //SoundIconMUTE
			11, 13, 13, 15,
			-4, 0, -1.5,
			-4, 0, -3.5,
			-2, 0, -3.5,
			-2, 0, -1.5);
	else
		TakeTexture(1, 1, 1, //SoundIconMUTE
			11, 13, 13, 15,
			-4, 0, -1.5,
			-4, 0, -3.5,
			-2, 0, -3.5,
			-2, 0, -1.5);
	if (SoundOnStatus == 1)
		if (SelectedButton == 2)
			TakeTexture(0.9, 0.9, 0.9, //SoundIcon
				8, 13, 10, 15,
				-4, 0, -1.5,
				-4, 0, -3.5,
				-2, 0, -3.5,
				-2, 0, -1.5);
		else
			TakeTexture(1, 1, 1, //SoundIcon
				8, 13, 10, 15,
				-4, 0, -1.5,
				-4, 0, -3.5,
				-2, 0, -3.5,
				-2, 0, -1.5);
	float x1[8] = { 0,0,2,4,6,8,10,12 }, y1[8] = { 0,36,36,36,36,36,36,36 }, x2[8] = { 0,2,4,6,8,10,12,14 }, y2[8] = { 0,38,38,38,38,38,38,38 };

	if (SelectedButton == 3)
		TakeTexture(0.9, 0.9, 0.9, //Color
			x1[ColorIndex], y1[ColorIndex], x2[ColorIndex], y2[ColorIndex],
			2, 0, -1.5,
			2, 0, -3.5,
			4, 0, -3.5,
			4, 0, -1.5);
	else
		TakeTexture(1, 1, 1, //Color
			x1[ColorIndex], y1[ColorIndex], x2[ColorIndex], y2[ColorIndex],
			2, 0, -1.5,
			2, 0, -3.5,
			4, 0, -3.5,
			4, 0, -1.5);
	glutSwapBuffers();
}
void DrawInfoMenu()
{
	glColor3f(0, 0, 0);
	//renderBitmapString(-1, 0, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Group 3 - I1922");
	TakeTexture(1, 1, 1, //Screen
		2, 20, 18, 29,
		-6.5, 0.1, -3.5,
		-6.5, 0.1, 3.5,
		6.5, 0.1, 3.5,
		6.5, 0.1, -3.5);
	TakeTexture(1, 1, 1, // Made by group 3
		32, 26, 43, 31,
		-5.5, 0, -2.5,
		-5.5, 0, 2.5,
		5.5, 0, 2.5,
		5.5, 0, -2.5);
	
	glutSwapBuffers();
}
void DrawPauseMenu()
{
	glColor3f(0, 0, 0);
	TakeTexture(1, 1, 1, //Paused
		20, 7, 28, 9,
		-4, 0, 3.5,
		-4, 0, 5.5,
		4, 0, 5.5,
		4, 0, 3.5);
	TakeTexture(1, 1, 1, //Screen
		2, 20, 18, 29,
		-8.5, 0, -5.5,
		-8.5, 0, 3.5,
		8.5, 0, 3.5,
		8.5, 0, -5.5);
	TakeTexture(1, 1, 1,
		19, 26, 31, 29,
		-5.5, -0.1, -2.5,
		-5.5, -0.1, 0.5,
		6.5, -0.1, 0.5,
		6.5, -0.1, -2.5);
	glutSwapBuffers();
}
void DrawLevelMenu(int SelectedLevelButton, int UnlockedLevel)
{
	float buttcolor1 = 1, buttcolor2 = 1, buttcolor3 = 1;
	glColor3f(0, 0, 0);
	TakeTexture(
		1, 1, 1,
		29, 1, 37, 3,
		-5, 0, 3,
		-5, 0, 5,
		5, 0, 5,
		5, 0, 3
	);
	if (UnlockedLevel >= 1)
	{
		if (SelectedLevelButton == 1) buttcolor1 = 0.9; else buttcolor1 = 1;
		TakeTexture(
			buttcolor1, buttcolor1, buttcolor1,
			14, 10, 16, 12,
			-7, 0, -1,
			-7, 0, 1,
			-5, 0, 1,
			-5, 0, -1
		);
	}
	if (UnlockedLevel >= 2)
	{
		if (SelectedLevelButton == 2) buttcolor2 = 0.9; else buttcolor2 = 1;
		TakeTexture(
			buttcolor2, buttcolor2, buttcolor2,
			14, 7, 16, 9,
			-1, 0, -1,
			-1, 0, 1,
			1, 0, 1,
			1, 0, -1
		);
	}
	if (UnlockedLevel >= 3) 
	{
		if (SelectedLevelButton == 3) buttcolor3 = 0.9; else buttcolor2 = 1;
		TakeTexture(
			buttcolor3, buttcolor3, buttcolor3,
			17, 7, 19, 9,
			5, 0, -1,
			5, 0, 1,
			7, 0, 1,
			7, 0, -1
		);
	}
	glutSwapBuffers();
}
void DrawWinMenu()
{
	glColor3f(0, 0, 0);
	TakeTexture(1, 1, 1, //Congrats!
		19, 18, 27, 20,
		-4, 0, 3.5,
		-4, 0, 5.5,
		4, 0, 5.5,
		4, 0, 3.5);
	TakeTexture(1, 1, 1, //Screen
		2, 20, 18, 29,
		-8.5, 0, -5.5,
		-8.5, 0, 3.5,
		8.5, 0, 3.5,
		8.5, 0, -5.5);
	TakeTexture(1, 1, 1, //poof
		20, 21, 24, 25,
		-7.9, -0.1, -5,
		-7.9, -0.1, -1,
		-3.9, -0.1, -1,
		-3.9, -0.1, -5
	);
	TakeTexture(1, 1, 1, //poof2
		25, 21, 29, 25,
		3.9, -0.1, -5,
		3.9, -0.1, -1,
		7.9, -0.1, -1,
		7.9, -0.1, -5
	);
	TakeTexture(1, 1, 1, //enter
		32, 20, 41, 22,
		-4, -0.1, -1,
		-4, -0.1, 1,
		4, -0.1, 1,
		4, -0.1, -1
	);
	glutSwapBuffers();
}

void DrawLoseMenu()
{
	glColor3f(0, 0, 0);
	TakeTexture(1, 1, 1, //Congrats!
		19, 16, 27, 18,
		-4, 0, 3.5,
		-4, 0, 5.5,
		4, 0, 5.5,
		4, 0, 3.5);
	TakeTexture(1, 1, 1, //Screen
		2, 20, 18, 29,
		-8.5, 0, -5.5,
		-8.5, 0, 3.5,
		8.5, 0, 3.5,
		8.5, 0, -5.5);
	TakeTexture(1, 1, 1, //poof
		31, 15, 37, 19,
		-7.9, -0.1, -5,
		-7.9, -0.1, -1,
		-1.9, -0.1, -1,
		-1.9, -0.1, -5
	);
	TakeTexture(1, 1, 1, //poof2
		38, 15, 43, 19,
		2.9, -0.1, -5,
		2.9, -0.1, -1,
		7.9, -0.1, -1,
		7.9, -0.1, -5
	);
	TakeTexture(1, 1, 1, //enter
		32, 20, 41, 22,
		-4, -0.1, -1,
		-4, -0.1, 1,
		4, -0.1, 1,
		4, -0.1, -1
	);
	glutSwapBuffers();
}
void DrawCar(float x, float y, float z, float angle1, float angle2, float r, float g, float b)
{
	/*
	glBegin(GL_LINES);

	glColor3f(1, 0, 0);
	glVertex3f(x, y, z);
	glVertex3f(x + 20, y, z);

	glColor3f(0, 1, 0);
	glVertex3f(x, y, z);
	glVertex3f(x, y + 20, z);

	glColor3f(0, 0, 1);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z + 20);
	glEnd();*/
	//glBegin(GL_LINES);
	//glVertex3f(x, y, z);
	//glVertex3f(x + 100*sin(angle1) * cos(angle2), y + 100*sin(angle2), z + 100*cos(angle1) * cos(angle2));
	//glColor3f(1, 0, 0);
	//glVertex3f(x, y, z);
	//glVertex3f(x + 7 * sin(angle1) * cos(angle2), y + sin(angle2), z + 7 * cos(angle1) * cos(angle2));
	//
	//glColor3f(0, 1, 0);
	//glVertex3f(x, y, z);
	//glVertex3f(x + 3 * sin(angle1 + M_PI_2) * cos(angle2), y + sin(angle2), z + 3 * cos(angle1 + M_PI_2) * cos(angle2));

	//glEnd();
	
	float vectices[] =
	{
		0,0,0,
		1,4,0,//a1
		5,4,0,//b2
		5,0,0,//c3
		5,0,8,//d4
		1,0,8,//e5
		1,0,0,//f6
		5,2,8,//g7
		1,2,8,//h8
		5,2,6,//i9
		1,2,6,//j10
		5,4,4,//k11
		1,4,4,//l12
		5,0,4,//13
		1,0,4,//14
		5,0,6,//15
		1,0,6,//16

	};
	vector<float> texture_vectices =
	{
		
		0,288,
		128,288,
		128,224,
		0,224,
		
		128,192,
		128,64,
		0,64,
		0,192,

		160,288,
		288,288,
		288,224,
		160,224,
		

		352,256,
		384,256,
		384,224,
		352,224,

		352,256,
		384,256,
		384,224,
		352,224,

		352,256,
		384,256,
		384,224,
		352,224,

		160,192,
		288,192,
		288,64,
		160,64,

		384,64,
		384,192,
		320,128,
		320,64,

		416,64,
		416,128,
		480,128,
		480,64,

		288,192,
		288,64,
		160,64,
		160,192,

		384,64,
		384,192,
		320,128,
		320,64,

		416,128,
		480,128,
		480,64,
		416,64,
		
		0,0,0,0,0,0,0,0,
	};
	vector<int> quads = 
	{
		8,7,4,5,
		1,6,3,2,
		12,11,9,10,
		1,2,11,12,
		8,7,9,10,//trên trước
		5,4,3,6, //đáy
		
		
		11,2,3,13, //bánh sau trái
		13,11,9,15, //thân giữa trái
		4,7,9,15, // bánh trước trái
		1,6,14,12, //bánh sau phải
		14,12,10,16, //thân giữa phải
		8,10,16,5 //bánh trước phải
		/*2,3,4,7,
		9,11,2,3,
		6,1,12,10,
		8,5,6,1,*/
	};
/*	vector<int> triangles
	{
		
		//3,2,11,9,7,4,-1//bcdgik
		////faljhe
	};*/
	float adx = 0; float ady = 0;
	int m = abs(x)*100 + abs(z)*100;
	if (m % 4 == 2)
	{
		ady = 1536;
	}
	else if (m % 4 == 1)
	{
		adx = 512;
		ady = 1024;
	}
	//cout << _debug(addx) << '\n';
	glEnable(GL_TEXTURE_2D);
	glColor3f(r,g,b);
	glPushMatrix();
	glTranslatef(x, y-1, z);
	glRotatef(angle1 * 180 / M_PI, 0, 1, 0);
	glRotatef(angle2 * 180 / M_PI, 0, 0, 1);
	glPushMatrix();
	//cout << _debug(angle1) << '\n';
	//glScalef(0.5, 0.5, 0.5);
	//glScalef(0.5, 0.5, 0.5);
	glTranslatef(-3, 0, -4);
	//glRotatef(angle1 * 180 / M_PI, 0, 1, 0);
	glBegin(GL_QUADS);
	for (int i = 0, j = 0; i < (int)quads.size(); ++i,++j)
	{
		glColor3f(r, g, b);
		glTexCoord2f((texture_vectices[j * 2]+adx) / 2048, (texture_vectices[j * 2 + 1]+ady) / 2048.0);
		glVertex3f(vectices[quads[i] * 3], vectices[quads[i] * 3 + 1], vectices[quads[i] * 3 + 2]);
	}
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	/*glBegin(GL_TRIANGLES);
	for (int i = 0; i < (int)triangles.size(); ++i)
	{
		glColor3f(i / 25.0, i / 25.0, i / 25.0);
		glVertex3f(vectices[triangles[i] * 3], vectices[triangles[i] * 3 + 1], vectices[triangles[i] * 3 + 2]);
	}
	glEnd();*/
}
void DrawStreet()
{
	glColor3f(1, 1, 1);
	for (int i = -1; i < 3; ++i)
	{
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0 / 2048.0, 320 / 2048.0);
		glVertex3f(-20, 0, -i * 1000);

		glTexCoord2f(0 / 2048.0, 352 / 2048.0);
		glVertex3f(-20, 0, -i * 1000 - 1000);

		glTexCoord2f(32 / 2048.0, 352 / 2048.0);
		glVertex3f(20, 0, -i * 1000 - 1000);

		glTexCoord2f(32 / 2048.0, 320 / 2048.0);
		glVertex3f(20, 0, -i * 1000);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	glColor3f(1, 1, 1);
	for (int i = 1; i <= 10; ++i)
	{
		glEnable(GL_TEXTURE_2D);
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glTexCoord2f(0 / 2048.0, 320 / 2048.0);
		glVertex3f(500, 0.01, -i * 200 + 0);

		glTexCoord2f(0 / 2048.0, 352 / 2048.0);
		glVertex3f(-500, 0.01, -i * 200 + 0);

		glTexCoord2f(32 / 2048.0, 352 / 2048.0);
		glVertex3f(-500, 0.01, -i * 200 + -50);

		glTexCoord2f(32 / 2048.0, 320 / 2048.0);
		glVertex3f(500, 0.01, -i * 200 + -50);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	}
	TakeTexture(1, 1, 1, 0, 11, 1, 12, -20, 0.02, -2220, -20, 0.02, -2230, 20, 0.02, -2230, 20, 0.02, -2220);

}
void Drawing(float x, float y, float z, float angle1, float angle2)
{
	DrawStreet();

	glLineWidth(5);
	//GLfloat light0Pos[] = { x, y, z, 1 };
	//glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);

	//cout << _debug(dddd) << '\n';
	//cout << _debug(angle1) << _debug(angle2);
	//cout << _debug(x) << _debug(y) << _debug(z) << '\n';
	//glColor3f(1, 0, 0); 


	//glPushMatrix();
			//sprintf_s(number, "%d", (i + 3) * 6 + (j + 3));
	string text = "Points:";
	int points = -z;
	if (points < 0) points = 0;
	renderBitmapString(x - 1, y+6, z, GLUT_BITMAP_TIMES_ROMAN_24, text + to_string(points));
	
//	renderBitmapString(x, y, z, GLUT_BITMAP_TIMES_ROMAN_24, text);
	//glPopMatrix();

	/*glColor3f(1, 1, 1);
	for (int i = -100; i <= 100; ++i)
	{
		glBegin(GL_LINES);
		glVertex3f(100, 0, i);
		glVertex3f(-100, 0, i);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(i, 0, 100);
		glVertex3f(i, 0, -100);
		glEnd();
	}
	for (int i = -100; i <= 100; ++i)
	{
		glBegin(GL_LINES);
		glVertex3f(100, 100, i);
		glVertex3f(-100, 100, i);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(i, 100, 100);
		glVertex3f(i, 100, -100);
		glEnd();
	}
	/*glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	for (int i = 1; i < 100; ++i)
	{
		glVertex3f(10, 0, -i);
		glVertex3f(-i, 0, 10);
	}
	glEnd();*/
	/*
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	*/

	/*glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(x + sin(angle1) * cos(angle2), y + sin(angle2), z + cos(angle1) * cos(angle2));
	glVertex3f(x + sin(angle1) * cos(angle2) + 0.5, y + sin(angle2), z + cos(angle1) * cos(angle2));

	glColor3f(0, 1, 0);
	glVertex3f(x + sin(angle1) * cos(angle2), y + sin(angle2), z + cos(angle1) * cos(angle2));
	glVertex3f(x + sin(angle1) * cos(angle2), y + sin(angle2) + 0.5, z + cos(angle1) * cos(angle2));

	glColor3f(0, 0, 1);
	glVertex3f(x + sin(angle1) * cos(angle2), y + sin(angle2), z + cos(angle1) * cos(angle2));
	glVertex3f(x + sin(angle1) * cos(angle2), y + sin(angle2), z + cos(angle1) * cos(angle2) + 0.5);
	glEnd();*/

//	glPushMatrix();
	//glScalef(1.5, 1.5, 1.5);
	
	//glPopMatrix();

	glutSwapBuffers();
}
