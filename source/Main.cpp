/* ********************************************************************************* *
 * *                       SIT255 - Advanced Game Development                      * *
 * *                Assignment #1 - Develop a Software Framework                   * *
 * *                                for Agent-based Games                          * *
 * *                                                                               * *
 * *  This code is provided to students as a basic framework for the purposes of   * *
 * *  developing an agent-based game that meets the requirements of the assessment * *
 * *  guidelines. This code base does not provide all features necessary to        * *
 * *  complete the assessment task. Students must modify and extend this framework * *
 * *  to achieve the specific objectives of the task.                              * *
 * *                                                                               * *
 * *  The code is provided as-is and while significant efforts have been made to   * *
 * *  ensure that it is bug-free, this is not a guarantee. It is each student's    * *
 * *  responsibility to ensure that their final submission compiles and executes   * *
 * *  without error.                                                               * *
 * *                                                                               * *
 * *  COPYRIGHT NOTICE                                                             * *
 * *  ----------------                                                             * *
 * *  (C) [2012] - [2016] Deakin University                                        * *
 * *  All rights reserved.                                                         * *
 * *  All information contained herein is, and remains the property of Deakin      * *
 * *  University and the author (Tim Wilkin).                                      * *
 * *  Dissemination of this information or reproduction of this material is        * *
 * *  strictly forbidden unless prior written permission is obtained from Deakin   * *
 * *  University. The right to create derivative works from this material is       * *
 * *  hereby granted to students enrolled in SIT255, but only for the purposes of  * *
 * *  assessment while an enrolled student at Deakin University.                   * *
 * *                                                                               * *
 * ********************************************************************************* *
 * *  STUDENT ID: 215123867                                                        * *
 * *  STUDENT NAME: Tom Hoogstra                                                   * *
 * *  DATE:                                                                        * *
 * ********************************************************************************* *
 */



#include <iostream>
#include <fstream>
#include <string>

#include <time.h>
#include <vector>

#include "ui\WinCanvas.h"
#include "ui\WinTexture.h"
#include "ui\InputState.h"
#include "../ActorFactory.h"
#include "../EventManager.h"
#include "../PlayerMovementListener.h"
#include <ctime>
#include "../SceneManager.h"
#include "../ItemCollisionListener.h"
// Constant values used in the code - this is the whole window size including
// menu buttons and border - actual graphics canvas size is smaller!
const unsigned int	WINDOW_WIDTH = 1000;
const unsigned int	WINDOW_HEIGHT = 1000;

void registerListeners();


using namespace std;


// The main function of the program
int main()
{

	/**************************************************************************
	 *
	 *	Declare a WinCanvas object. We wouldn't normally create an object this way as
	 *  it is non-portable, but this is a very simple 'graphics canvas' interface to
	 *  the Windows Graphical Device Interface (GDI) API.
	 */

	WinCanvas wc(WINDOW_WIDTH, WINDOW_HEIGHT, L"Assignment 2");

	const char playerKeys[] = { VK_SPACE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN };
	/*
	 *  An InputState object provides an interface to the Keyboard and Mouse devices.
	 */

	InputState  ui;
	OpenUIHandler(ui);	// Initialise the input interface

	/*
		Register our Observers / Event Listeners
	*/
	registerListeners();
	ActorFactory::getInstance()->loadProperties();
	SceneManager::getInstance()->loadScene();


	const int FRAMES_PER_SECOND = 180;
	const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

	DWORD next_game_tick = GetTickCount();
	// GetTickCount() returns the current number of milliseconds
	// that have elapsed since the system was started

	int sleep_time = 0;
	
	while (wc.IsActive())
	{

		for (char cd : playerKeys) {
			// If an arrow key isn't being held down, check next key.
			if (!ui.isActive(cd)) continue;
			// Call InputEvent (Should probably call it KeyPressEvent)
			SceneManager::getInstance()->processInput(cd);
		}

		EffectManager::processEffects();
		SceneManager::getInstance()->healPlayer();
		SceneManager::getInstance()->processCollisions();
		SceneManager::getInstance()->addEnemies();
		SceneManager::getInstance()->addItems();


		wc.Clear(255, 255, 255);

		// Update all actors in our scene
		SceneManager::getInstance()->updateActors(wc);

		

		next_game_tick += SKIP_TICKS;
		sleep_time = next_game_tick - GetTickCount();
		wc.Display();

		if (sleep_time >= 0) {
			Sleep(sleep_time);
		}
		
	
	}
	/**************************************************************************/


	return 0;
}


// Registers all listeners by adding them to the Listener list in the EventManager class
void registerListeners() {
	EventManager::getInstance()->addListener(new PlayerMovementListener());
	EventManager::getInstance()->addListener(new ItemCollisionListener());
}
