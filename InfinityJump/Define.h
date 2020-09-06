#pragma once

// File
#define RM_TXT_FILE			"../Resources/Managers/RM.txt"
#define SM_TXT_FILE			"../Resources/Managers/SM2.txt"
#define MENUSCENE_FILE		"../Resources/Managers/MenuScene.txt"
#define PLAYSCENE_FILE		"../Resources/Managers/PlayScene.txt"

#define WORLD_GRAVITY b2Vec2(0.0, -10.0)
#define WORLD_VELOCITY_ITERATIONS 8
#define WORLD_POSITION_ITERATIONS 3

#define EPSILON 1E-6

#define MAX_NUM_PAD 10
#define PAD_SPAWNTIME 1.1f
#define PAD_VELOCITY -3.0f
#define IMPULSE_FIRSTJUMP 5.5f
#define IMPULSE_SECONDJUMP 6.0f

#define PAD_DEFAULT_X_COORD 1000.0f
#define PAD_Y_COORD_LEVEL_0 50.0f
#define PAD_Y_COORD_LEVEL_1 200.0f