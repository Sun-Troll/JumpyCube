/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	SoundBorderTouch(L"Sounds\\spayed.wav"),
	jumpy(Vec2(Graphics::ScreenWidth / 2.0f, Graphics::ScreenHeight / 2.0f), 10),
	playform(Vec2(Graphics::ScreenWidth / 2.0f, Graphics::ScreenHeight / 2.0f))
{
	for (Platform& p : plats)
	{
		p.Spawn();
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float frameTime = ft.FrameTime();
	if (!won)
	{
		timeSinceSpawn += frameTime;

		if (timeSinceSpawn > SpawnTime)
		{
			plats[currentPlaty].Activate();
			currentPlaty++;
			if (currentPlaty >= platformMax)
			{
				won = true;
			}
			timeSinceSpawn = 0.0f;
		}
		for (int i = std::max(0, currentPlaty - 20); i < currentPlaty; i++)
		{
			plats[i].Update(frameTime);
			plats[i].ClampScreen();
		}

		bool left = false;
		bool right = false;
		bool top = false;
		bool bottom = false;
		if (wnd.kbd.KeyIsPressed('A'))
		{
			left = true;
		}
		else if (wnd.kbd.KeyIsPressed('D'))
		{
			right = true;
		}
		if (wnd.kbd.KeyIsPressed('W'))
		{
			top = true;
		}
		else if (wnd.kbd.KeyIsPressed('S'))
		{
			bottom = true;
		}
		playform.Update(left, right, top, bottom, frameTime);

		jumpy.Jump(playform, wnd.mouse.LeftIsPressed(), Vec2(float(wnd.mouse.GetPosX()), float(wnd.mouse.GetPosY())), frameTime);

		jumpy.Update(gravity, friction, frameTime);
		jumpy.Stick(playform);
		if (jumpy.OutsideBorders(playform))
		{
			SoundBorderTouch.Play();
		}
		jumpy.Respawn(playform, frameTime);

		playform.ClampScreen();
		jumpy.ClampScreen();

		if (wnd.kbd.KeyIsPressed(VK_SPACE))
		{
			playform.Cheat();
		}
	}
}

void Game::ComposeFrame()
{
	for (int i = std::max(0, currentPlaty - 20); i < currentPlaty; i++)
	{
		plats[i].Draw(gfx);
	}
	playform.Draw(gfx);
	jumpy.DrawLives(gfx);
	jumpy.DrawJumpIn(gfx);
	jumpy.DrawBorders(gfx);
	jumpy.Draw(gfx);
}
