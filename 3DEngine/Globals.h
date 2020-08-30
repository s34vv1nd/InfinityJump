#pragma once

#define GAME_2D

#define LIMIT_FPS			30

// define variable
#define MAX_LENGTH			255

// Macro
#define PI					3.14159265f
#define HALFPI				(PI/2.0f)
#define SAFE_DEL(x)			{if(x){delete x; x = NULL;}}
#define SAFE_DEL_ARRAY(x)	{if(x){delete[] x; x = NULL;}}
#define X2GAME(x)			((1.0f*x - SCREEN_CENTER_W)/SCREEN_CENTER_W)
#define Y2GAME(y)			(-1.0f*(1.0f*y - SCREEN_CENTER_H)/SCREEN_CENTER_H)

// File
#define RM_TXT_FILE			"../Resources/Managers/RM.txt"
#define SM_TXT_FILE			"../Resources/Managers/SM2.txt"
#define RM_MUSIC_OFF		"../Resources/Managers/RM_music_off.txt"
#define SM_MUSIC_OFF		"../Resources/Managers/SM_music_off.txt"
#define RM_MENU				"../Resources/Managers/RM_menu.txt"
#define SM_MENU				"../Resources/Managers/SM_menu.txt"
#define RM_CREDIT			"../Resources/Managers/RM_credit.txt"
#define SM_CREDIT			"../Resources/Managers/SM_credit.txt"
#define RM_PLAY				"../Resources/Managers/RM_play.txt"
#define SM_PLAY				"../Resources/Managers/SM_play.txt"
#define RM_PAUSE			"../Resources/Managers/RM_pause.txt"
#define SM_PAUSE			"../Resources/Managers/SM_pause.txt"
#define RM_HELP				"../Resources/Managers/RM_help.txt"
#define SM_HELP				"../Resources/Managers/SM_help.txt"

// BUTTONS
#define BIT_MOVE_FORWARD	(1<<0)
#define BIT_MOVE_BACKWARD	(1<<1)
#define BIT_MOVE_LEFT		(1<<2)
#define BIT_MOVE_RIGHT		(1<<3)
#define BIT_ROTATE_UP		(1<<4)
#define BIT_ROTATE_DOWN		(1<<5)
#define BIT_ROTATE_LEFT		(1<<6)
#define BIT_ROTATE_RIGHT	(1<<7)
#define BIT_MOVE_UP			(1<<8)
#define BIT_MOVE_DOWN		(1<<9)

class Globals
{
public:
	static const int screenWidth = 960;
	static const int screenHeight = 600;
};