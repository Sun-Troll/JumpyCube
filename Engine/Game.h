/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "JumpyCube.h"
#include "PlayerPlatform.h"
#include "Platform.h"
#include "Sound.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(float ft);
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	static constexpr int nSubframes = 10;
	static constexpr float gravity = 300.0f;
	static constexpr float friction = 4.0f;
	FrameTimer ft;
	Sound soundStart;
	Sound soundWon;
	Sound soundDead;
	Sound soundLost;
	Sound soundGainLive;
	Sound soundStickPlat;
	Sound soundStickPlayform;
	JumpyCube jumpy;
	PlayerPlatform playform;
	static constexpr int platformMax = 300;
	int currentPlaty = 0;
	int nPlatsBackCheck = 60;
	static constexpr float SpawnTime = 1.0f;
	float timeSinceSpawn = 0.0f;
	Platform plats[platformMax];
	float speedUp = 1.0f;
	static constexpr float speedUpPerPlat = 1.0f / platformMax;
	bool start = false;
	bool won = false;
	bool lost = false;
	const RectF wonLoseRect{ 150.0f, 100.0f, Vec2(float(Graphics::ScreenWidth) / 2.0f, float(Graphics::ScreenHeight) / 2.0f) };
	static constexpr Color colWon = Colors::Yellow;
	static constexpr Color colLost{ 100, 10, 10 };
	//draw win
	const Vec2 winInTopLeft{ 650.0f, 80.0f };
	static constexpr float winInWidth = 1000.0f;
	static constexpr float winInHeight = 20.0f;
	static constexpr float winInDrawChargeRatio = winInWidth / float(platformMax);
	static constexpr Color winInColBase{ 125, 125, 25 };
	static constexpr Color winInColCharge{ 250, 250, 50 };
	/********************************/
};