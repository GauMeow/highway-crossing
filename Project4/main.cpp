#include "Extension.h"

#include <math.h>
using namespace std;




//GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//GLfloat mat_shininess[] = { 10.0 };
//GLfloat light_position1[] = { 1.0, 1.0, 1.0, 0.0 };
//GLfloat light_position2[] = { -1.0, -1.0, -1.0, 0.0 };

//GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
//GLfloat red_light[] = { 9.,0.,0.,1. };
//GLfloat blue_light[] = { 0.,0.,1.,1. };
//GLfloat white_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

struct Point {
	float x, y;
};
struct ECar {
	float x = -500, y = 1.01, z, dir = 3.0/2*M_PI, right = -0.1, r=1, g=1, b=1;
};

const int FPS = 240;//fps trong game
float FPStime = 1000000000.0 / FPS;
std::chrono::steady_clock::time_point deltaTime;

float Camera_Angle1 = M_PI, Camera_Angle2 = 0;
float FARR = 15;

float Player_Angle1 = M_PI, Player_Angle2 = 0;
float Player_x = 0, Player_y = 1.01, Player_z = 0;
float MOVING_SPEED = 0;

bool KEY_W, KEY_A, KEY_S, KEY_D, KEY_Space, KEY_LShift;
#define PLAY_STATE 0
#define MAINMENU_STATE 1
#define PAUSE_STATE 2
#define LEVEL_STATE 3
#define HELP_STATE 4
#define SETTING_STATE 5
#define INFO_STATE 6
#define WIN_STATE 7
#define LOSE_STATE 8
int state = MAINMENU_STATE; 

int SelectedButtonMainMenu = 1, SelectedButtonSettingMenu = 1, SelectedLevelButton = 1, UnlockedLevel = 1, FullScreenStatus = 0, SoundOnStatus = 1, ColorIndex = 2;
float r[8] = { 0, 0.925 , 1, 1, 0.055, 0, 0.247, 0.722 };
float g[8] = { 0, 0.11, 0.498, 0.949, 0.82, 0.659, 0.282, 0.239 };
float b[8] = { 0, 0.141, 0.153, 0, 0.271, 0.953, 0.8, 0.729};

vector<ECar> Enemy(100);

void Initialize(float EnemySpeed);
void DisplayFunc();
void ReshapeFunc(int width, int height);
void MouseMove(int x, int y);
void MouseFunc(int button, int state, int x, int y);
void KeyboardFunc(unsigned char key, int x, int y);
void KeyboardUpFunc(unsigned char key, int x, int y);
void SpecialFunc(int key, int x, int y);
void SpecialUpFunc(int key, int x, int y);
void MovePlayer();
void LoadTexture(const char* filename)
{
	GLuint texture;
	unsigned char* data;

	FILE* file;
	file = fopen(filename, "rb");

	if (file == NULL) return;
	unsigned char header[54];
	fread(header, 1, 54, file);
	int width = *(int*)&(header[0x12]);
	int height = *(int*)&(header[0x16]);

	data = (unsigned char*)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);
	fclose(file);


	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	free(data);
	//cout << texture << '\n';
	//return texture;
}
bool doOverlap(Point l1, Point r1, Point l2, Point r2)
{
	if (l1.x == r1.x || l1.y == r2.y || l2.x == r2.x || l2.y == r2.y) 
		return false;
	if (l1.x >= r2.x || l2.x >= r1.x)
		return false;
	if (l1.y <= r2.y || l2.y <= r1.y)
		return false;
	return true;
}




int main(int argc, char** argv)
{	
	//Khởi tạo
	deltaTime = std::chrono::high_resolution_clock::now();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WIDTH)/2, (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT)/2);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Highway Crossing");
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);


	//glutFullScreen();

	LoadTexture("TEXTURE.bmp");

	glClearColor(0.5, 0.65, 0.92, 1);
	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc); // ReshapeFunc được gọi khi người dùng thay đổi kích thước cửa sổ OpenGL
	glutIdleFunc(DisplayFunc); // DisplayFunc sẽ được gọi khi mọi event khác đã xong

	// Xử lý chuột
	glutSetCursor(GLUT_CURSOR_NONE);
	//glutSetCursor(GLUT_CURSOR_INHERIT);
	glutMotionFunc(MouseMove); // MouseMove được gọi khi người dùng vừa bấm nút chuột vừa di chuột
	glutPassiveMotionFunc(MouseMove); // MouseMove được gọi khi người dùng không bấm nút chuột nhưng di chuột
	glutMouseFunc(MouseFunc);

	// Xử lý bàn phím
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(KeyboardFunc); // Phím thông thường
	glutKeyboardUpFunc(KeyboardUpFunc); // Key release
	glutSpecialFunc(SpecialFunc); // Phím đặc biệt như F1-12, Insert, Mũi tên, Shift, Ctrl, ...
	glutSpecialUpFunc(SpecialUpFunc); // Special key release

	//Main
	glutMainLoop();
	return 0;
}
void MovePlayer()
{
	//cout << Player_z << '\n';
	if (Player_x + sin(Player_Angle1) * MOVING_SPEED < 16 && Player_x + sin(Player_Angle1) * MOVING_SPEED > -16) Player_x += sin(Player_Angle1) * MOVING_SPEED;
	if (Player_z + cos(Player_Angle1) * MOVING_SPEED < 2) Player_z += cos(Player_Angle1) * MOVING_SPEED;
	if (MOVING_SPEED > 0) MOVING_SPEED -= min((float)0.001, MOVING_SPEED);
	if (MOVING_SPEED < 0) MOVING_SPEED += min((float)0.001, -MOVING_SPEED);
	if (KEY_W)
	{
		if (MOVING_SPEED < 0.5) MOVING_SPEED += 0.005;
	}
	if (KEY_S)
	{
		if (MOVING_SPEED > -0.3) MOVING_SPEED -= 0.005;
	}
	if (KEY_A)
	{
		//if (KEY_W ^ KEY_S)
	//	{
			Player_Angle1 += MOVING_SPEED * 0.01;
			if (Player_Angle1 > 2 * M_PI) Player_Angle1 -= 2 * M_PI;
	//	}
		//Player_x += sin(Camera_Angle1 + M_PI_2) * MOVING_SPEED;
		//Player_z += cos(Camera_Angle1 + M_PI_2) * MOVING_SPEED;
	}
	if (KEY_D)
	{
		//if (KEY_W ^ KEY_S)
		//{
			Player_Angle1 -= MOVING_SPEED * 0.01;
			if (Player_Angle1 < 0) Player_Angle1 += 2 * M_PI;
	//	}
		//Player_x -= sin(Camera_Angle1 + M_PI_2) * MOVING_SPEED;
		//Player_z -= cos(Camera_Angle1 + M_PI_2) * MOVING_SPEED;
	}
	if (KEY_Space)
	{
		//Player_y += MOVING_SPEED;
	}
	if (KEY_LShift)
	{
		//Player_y -= MOVING_SPEED;
	}
}
void Initialize(float EnemySpeed)
{
	for (int i = 0; i < 100; ++i)
	{
		Enemy[i].right = -EnemySpeed;
	}
	for (int i = 0, j = 0; i < 100; ++i, ++j)
	{
		Enemy[i].x = ((rand() % 400)) - 200;
		Enemy[i].r = (rand() % 255 + 1) / 256.0;
		Enemy[i].g = (rand() % 255 + 1) / 256.0;
		Enemy[i].b = (rand() % 255 + 1) / 256.0;
		if (j == 5) j = 0;
		if (j >= 3) {
			Enemy[i].dir = M_PI_2; Enemy[i].right = -Enemy[i].right;
		}
		Enemy[i].z = -(i / 10 + 1) * 200 - j * 8 - 9;
	}
	Camera_Angle1 = M_PI; Camera_Angle2 = 0;
	FARR = 15;
	Player_Angle1 = M_PI; Player_Angle2 = 0;
	Player_x = 0; Player_y = 1.01; Player_z = 0;
	MOVING_SPEED = 0;
	KEY_W = 0; KEY_A = 0;  KEY_S = 0; KEY_D = 0; KEY_Space = 0;  KEY_LShift = 0;
}
float x = 0;
void DisplayFunc()
{
	std::chrono::steady_clock::time_point FPSLimit = std::chrono::high_resolution_clock::now();
	if (std::chrono::duration_cast<std::chrono::nanoseconds>(FPSLimit - deltaTime).count() < FPStime)
	{
		//cout << std::chrono::duration_cast<std::chrono::nanoseconds>(FPSLimit - deltaTime).count() <<'\n';
		return;
	}
	else
	{
		deltaTime = FPSLimit;
	}
	//Khởi tạo
	if (state == MAINMENU_STATE) //MainMenu
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		Camera(0, 0, 0, 0, M_PI_2, 10);
		DrawCar(-10, 10, 0, x, M_PI, r[ColorIndex], g[ColorIndex], b[ColorIndex]);
		DrawCar(10, 10, 0, -x, M_PI, r[ColorIndex], g[ColorIndex], b[ColorIndex]);
		x += 0.005;
		if (x > 2 * M_PI) x = 0;
		DrawMainMenu(SelectedButtonMainMenu);
	}
	if (state == HELP_STATE)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		Camera(0, 0, 0, 0, M_PI_2, 10);
		DrawHelpMenu();
	}
	if (state == SETTING_STATE)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		Camera(0, 0, 0, 0, M_PI_2, 10);
		DrawCar(-15, 15, -7, x, M_PI, r[ColorIndex], g[ColorIndex], b[ColorIndex]);
		DrawCar(15, 15, -7, -x, M_PI, r[ColorIndex], g[ColorIndex], b[ColorIndex]);
		x += 0.005;
		if (x > 2 * M_PI) x = 0;
		DrawSettingMenu(SelectedButtonSettingMenu, FullScreenStatus, SoundOnStatus, ColorIndex);
	}
	if (state == INFO_STATE)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		Camera(0, 0, 0, 0, M_PI_2, 10);
		DrawInfoMenu();
	}
	if (state == LEVEL_STATE)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		Camera(0, 0, 0, 0, M_PI_2, 10);
		DrawLevelMenu(SelectedLevelButton, UnlockedLevel);
	}
	if (state == WIN_STATE)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		Camera(0, 0, 0, 0, M_PI_2, 10);
		DrawWinMenu();
	}
	if (state == LOSE_STATE)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		Camera(0, 0, 0, 0, M_PI_2, 10);
		DrawLoseMenu();
	}
	if (state == PAUSE_STATE)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		Camera(0, 0, 0, 0, M_PI_2, 10);
		DrawPauseMenu();
	}
	if (state == PLAY_STATE) //Play
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		MovePlayer();
		Camera(Player_x, Player_y, Player_z, Camera_Angle1, Camera_Angle2, FARR);
		DrawCar(Player_x, Player_y, Player_z, Player_Angle1, Player_Angle2, r[ColorIndex], g[ColorIndex], b[ColorIndex]);
		for (int i = 0; i < 100; ++i)
		{
			Enemy[i].x += Enemy[i].right;
			if (Enemy[i].x < -200) Enemy[i].x += 400;

			if (Enemy[i].x > 200) Enemy[i].x -= 400;
			DrawCar(Enemy[i].x, Enemy[i].y, Enemy[i].z, Enemy[i].dir, 0, Enemy[i].r, Enemy[i].g, Enemy[i].b);

			Point p1, p2, c1, c2;
			p1.x = Player_x - 2; p1.y = Player_z + 4;
			p2.x = Player_x + 2; p2.y = Player_z - 4;
			c1.x = Enemy[i].x - 4; c1.y = Enemy[i].z + 2;
			c2.x = Enemy[i].x + 4; c2.y = Enemy[i].z - 2;
			/*glColor3f(1, 0, 0);
			glVertex3f(p1.x, 1, p1.y);
			glVertex3f(p2.x, 1, p2.y);
			glColor3f(1, 0, 1);
			glVertex3f(c1.x, 1, c1.y);
			glVertex3f(c2.x, 1, c2.y);
			glEnd();*/
			//glPointSize(10);
			/*
			glBegin(GL_LINES);
			glColor3f(1, 0, 0);
			glVertex3f(p1.x, 1, p1.y);
			glColor3f(0, 1, 0);
			glVertex3f(p2.x, 1, p2.y);
			glColor3f(0, 0, 1);
			glVertex3f(c1.x, 1, c1.y);
			glColor3f(1, 1, 1);
			glVertex3f(c2.x, 1, c2.y);
			glEnd();*/
			if (doOverlap(p1, p2, c1, c2) == true)
			{
				state = LOSE_STATE;
				if (SoundOnStatus == 1) sndPlaySound(TEXT("CarCrash.wav"), SND_ASYNC);
				return;
			}
		}
		Drawing(Player_x, Player_y, Player_z, Camera_Angle1, Camera_Angle2);
		if (Player_z <= -2222)
		{
			state = WIN_STATE;
			if (SoundOnStatus == 1) sndPlaySound(TEXT("Win.wav"), SND_ASYNC);
			UnlockedLevel = min(4, SelectedLevelButton + 1);
		}
	}

}
void ReshapeFunc(int width, int height)
{
	if (height == 0) height = 1;
	float ratio = width * 1.0 / height;
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glViewport(0, 0, width, height); 
	gluPerspective(60, ratio, 0.1, 200); 
	glMatrixMode(GL_MODELVIEW); 
}
int dump = 0;
void MouseMove(int x, int y)
{
	//cout << "MouseMove:" << _debug(x) << _debug(y) << '\n';
	//cout << Camera_Angle2 << '\n';
	if (state == PLAY_STATE)
	{
		++dump;
		if (dump < 2) return; else dump = 0;
		float www = glutGet(GLUT_SCREEN_WIDTH), hhh = glutGet(GLUT_SCREEN_HEIGHT);
		POINT p;
		GetCursorPos(&p);
		float speed = abs(p.x - www / 2);
		float speed2 = abs(p.y - hhh / 2);
		if (p.x < www / 2) Camera_Angle1 += CAMERA_ROTATION_SPEED * speed;
		if (p.x > www / 2) Camera_Angle1 -= CAMERA_ROTATION_SPEED * speed;
		if (p.y < hhh / 2) if (Camera_Angle2 + 0.001 * speed2 < 0) Camera_Angle2 += CAMERA_ROTATION_SPEED * speed2;
		if (p.y > hhh / 2) if (Camera_Angle2 - 0.001 * speed2 > -M_PI_2) Camera_Angle2 -= CAMERA_ROTATION_SPEED * speed2;

		if (Camera_Angle1 > 2 * M_PI) Camera_Angle1 -= 2 * M_PI;
		if (Camera_Angle1 < 0) Camera_Angle1 += 2 * M_PI;

		SetCursorPos(www / 2, hhh / 2);
	}
}
void MouseFunc(int button, int state, int x, int y)
{
	//cout << "MouseFunc:" << _debug(button) << _debug(state) << _debug(x) << _debug(y) << '\n';
	if (state == PLAY_STATE)
	{
		if (button == 3)
		{
			//scroll up
			if (FARR > 6)
				FARR -= 0.2;
		}
		if (button == 4)
		{
			//scroll down
			if (FARR < 30)
				FARR += 0.2;
		}
	}
}
void KeyboardFunc(unsigned char key, int x, int y)
{
	//cout << "KeyboardFunc:" << _debug(key) << '[' << int(key) << ']' << _debug(x) << _debug(y) << '\n';
	if (state == HELP_STATE)
	{
		state = MAINMENU_STATE;
		return;
	}
	if (state == INFO_STATE)
	{
		state = MAINMENU_STATE;
		return;
	}
	if (state == SETTING_STATE)
	{
		if (int(key) == 27) 
		{
			state = MAINMENU_STATE;
		}
		if (key == 's' || key == 'S')
		{
			if (SelectedButtonSettingMenu < 3) ++SelectedButtonSettingMenu;
		}
		if (key == 'w' || key == 'W')
		{
			if (SelectedButtonSettingMenu > 1) --SelectedButtonSettingMenu;
		}
		if (int(key) == 13)//Enter
		{
			if (SelectedButtonSettingMenu == 1) //FullscreenButton
			{
				if (FullScreenStatus == 0)
				{
					FullScreenStatus = 1;
					glutFullScreen();
				}
				else if (FullScreenStatus == 1)
				{
					FullScreenStatus = 0;
					glutReshapeWindow(WIDTH, HEIGHT);
				}
			}
			if (SelectedButtonSettingMenu == 2) //FullscreenButton
			{
				if (SoundOnStatus == 0)
				{
					SoundOnStatus = 1;
				}
				else if (SoundOnStatus == 1)
				{
					SoundOnStatus = 0;
				}
			}
			if (SelectedButtonSettingMenu == 3)
			{
				if (ColorIndex < 7) ++ColorIndex;
				else ColorIndex = 1;
			}
		}
		return;
	}
	if (state == PAUSE_STATE)
	{
		if (int(key) == 27) //ESC
		{
			state = PLAY_STATE;
		}
		if (int(key) == 13)//Enter
		{
			state = MAINMENU_STATE;;
		}
		return;
	}
	if (state == LEVEL_STATE)
	{
		if (int(key) == 27) //ESC
		{
			state = MAINMENU_STATE;
		}
		if (int(key) == 13)//Enter
		{
			if (SelectedLevelButton == 1)
			{
				Initialize(0.1);
			}
			if (SelectedLevelButton == 2)
			{
				Initialize(0.3);
			}
			if (SelectedLevelButton == 3)
			{
				Initialize(0.5);
			}
			if (SelectedLevelButton == 4)
			{
				Initialize(10);
			}
			state = PLAY_STATE;
		}
		if (key == 's' || key == 'S')
		{
			if (SelectedLevelButton < UnlockedLevel) ++SelectedLevelButton;
		}
		if (key == 'w' || key == 'W')
		{
			if (SelectedLevelButton > 1) --SelectedLevelButton;
		}
		return;
	}
	if (state == MAINMENU_STATE)
	{
		if (key == 'w' || key == 'W')
		{
			--SelectedButtonMainMenu;
			if (SelectedButtonMainMenu < 1) SelectedButtonMainMenu = 4;
		}
		if (key == 's' || key == 'S') {
			++SelectedButtonMainMenu;
			if (SelectedButtonMainMenu > 4) SelectedButtonMainMenu = 1;
		}
		if (int(key) == 13) // Enter
		{
			if (SelectedButtonMainMenu == 1)
			{
				state = LEVEL_STATE;
			}
			if (SelectedButtonMainMenu == 2)
			{
				state = HELP_STATE;
			}
			if (SelectedButtonMainMenu == 3)
			{
				state = SETTING_STATE;
			}
			if (SelectedButtonMainMenu == 4)
			{
				state = INFO_STATE;
			}
		}
		if (int(key) == 27)  //Esc
		{
			exit(0);
		}
		return;
	}
	if (state == WIN_STATE)
	{
		if (int(key) == 13) //Enter
		{
			state = LEVEL_STATE;
		}
		return;
	}
	if (state == LOSE_STATE)
	{
		if (int(key) == 13) //Enter
		{
			state = LEVEL_STATE;
		}
		return;
	}
	if (state == PLAY_STATE)
	{
		if (int(key) == 27)  //Esc
		{
			KEY_W = 0;
			KEY_A = 0;
			KEY_S = 0;
			KEY_D = 0;
			state = PAUSE_STATE;
			//exit(0);
		}
		if (key == 'w' || key == 'W') KEY_W = 1; 
		if (key == 'a' || key == 'A') KEY_A = 1;
		if (key == 's' || key == 'S') KEY_S = 1;
		if (key == 'd' || key == 'D') KEY_D = 1;
		//if (key == ' ') KEY_Space = 1;
		return;
	}
}
void KeyboardUpFunc(unsigned char key, int x, int y)
{
	//cout << "KeyboardUpFunc:" << _debug(key) << _debug(x) << _debug(y) << '\n';
	if (state == PLAY_STATE)
	{
		if (key == 'w' || key == 'W') KEY_W = 0;
		if (key == 'a' || key == 'A') KEY_A = 0;
		if (key == 's' || key == 'S') KEY_S = 0;
		if (key == 'd' || key == 'D') KEY_D = 0;
		//if (key == ' ') KEY_Space = 0;
	}
}
void SpecialFunc(int key, int x, int y)
{
	//cout << "SpecialFunc:" << _debug(key) << _debug(x) << _debug(y) << '\n';
	if (state == HELP_STATE)
	{
		state = MAINMENU_STATE;
	}
	if (state == INFO_STATE)
	{
		state = MAINMENU_STATE;
	}
//	if (state == PLAY_STATE)
	//{
		//if (key == 112) KEY_LShift = 1;
	//}
}

void SpecialUpFunc(int key, int x, int y)
{
	//cout << "SpecialUpFunc:" << _debug(key) << _debug(x) << _debug(y) << '\n';
	//if (state == PLAY_STATE)
	//{
	//	if (key == 112) {
		//	KEY_LShift = 0;
	//	}
	//}
}