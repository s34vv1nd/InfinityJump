#pragma once

// File
#define RM_TXT_FILE				"../Resources/Managers/RM.txt"
#define SM_TXT_FILE				"../Resources/Managers/SM2.txt"
#define LOADINGSCENE_FILE		"../Resources/Managers/LoadingScene.txt"
#define MENUSCENE_FILE			"../Resources/Managers/MenuScene.txt"
#define SOUNDSCENE_FILE			"../Resources/Managers/SoundScene.txt"
#define PLAYSCENE_FILE			"../Resources/Managers/PlayScene.txt"
#define PAUSESCENE_FILE			"../Resources/Managers/PauseScene.txt"
#define GAMEOVERSCENE_FILE		"../Resources/Managers/GameOverScene.txt"
#define HELPSCENE_FILE			"../Resources/Managers/HelpScene.txt"
#define CREDITSCENE_FILE		"../Resources/Managers/CreditScene.txt"
#define SELECTIONSCENE_FILE		"../Resources/Managers/SelectionScene.txt"
#define HIGHSCORE_FILE			"../Resources/Managers/HighScore.txt"

#define NUM_LOADING_STEP 9

#define WORLD_GRAVITY b2Vec2(0.0, -10.0)
#define WORLD_VELOCITY_ITERATIONS 8 
#define WORLD_POSITION_ITERATIONS 3

#define EPSILON 1E-6

#define MAX_NUM_PAD 10
#define NUM_INITIAL_PAD 5
#define PAD_SPAWNTIME 1.1f
#define PAD_SPAWNTIME_DECREASE_RATE 1.0f
#define PAD_VELOCITY_X -3.0f
#define PAD_VELOCITY_Y 0.5f
#define PAD_SPEED_INCREASE_RATE 0.1f
#define NUM_PAD_PER_INCREASE_SPEED 10
#define IMPULSE_FIRSTJUMP 5.5f
#define IMPULSE_SECONDJUMP 6.0f
#define PAD_FIRST_X_COORD 30.0f
#define PAD_DEFAULT_X_COORD 1000.0f
#define PAD_Y_COORD_LEVEL_0 100.0f
#define PAD_Y_COORD_LEVEL_1 215.0f
#define PAD_Y_COORD_LEVEL_2 330.0f
#define PAD_MOVING_Y_POINT 10
#define PAD_HITBOX_WIDTH 220.0f
#define PAD_HITBOX_HEIGHT 50.0f

#define CHARACTER_DEFAULT_X_COORD 10
#define CHARACTER_INITIAL_Y_COORD 200
#define CHARACTER_HITBOX_WIDTH 30.0f
#define CHARACTER_HITBOX_HEIGHT 90.0f

#define MAX_VOLUME 10
#define MIN_VOLUME 0