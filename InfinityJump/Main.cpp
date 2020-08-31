// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "../3DEngine/3DEngine.h"
#include "Game.h"
#include <time.h>

int Init ( ESContext *esContext )
{
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Singleton<Game>::GetInstance()->Init();
	return 0;
}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	Singleton<Game>::GetInstance()->Draw();
	
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	Singleton<Game>::GetInstance()->Update(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	Singleton<Game>::GetInstance()->Key(key, bIsPressed);
}

void TouchActionDown(ESContext* esContext, int x, int y)
{
	// Mouse down
	Singleton<Game>::GetInstance()->TouchActionDown(x, y);
}

void TouchActionUp(ESContext* esContext, int x, int y)
{
	// Mouse up
	Singleton<Game>::GetInstance()->TouchActionUp(x, y);
}

void TouchActionMove(ESContext* esContext, int x, int y)
{
	// Mouse move
	Singleton<Game>::GetInstance()->TouchActionMove(x, y);
}

void CleanUp()
{
	Singleton<Game>::GetInstance()->CleanUp();
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "3D Training", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);
	esRegisterMouseDownFunc(&esContext, TouchActionDown);
	esRegisterMouseUpFunc(&esContext, TouchActionUp);
	esRegisterMouseMoveFunc(&esContext, TouchActionMove);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

