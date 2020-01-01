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
	soundDead(L"Sounds\\Fart.wav"),
	soundLost(L"Sounds\\spayed.wav"),
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
	if (!won && !lost)
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
		for (int i = std::max(0, currentPlaty - nPlatsBackCheck); i < currentPlaty; i++)
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
		for (int i = std::max(0, currentPlaty - nPlatsBackCheck); i < currentPlaty; i++)
		{
			if (jumpy.StickPlats(plats[i]))
			{
				playform.SetState(PlayerPlatform::State::Free);
			}
			if (jumpy.ColRedPlat(plats[i]))
			{
				playform.SetState(PlayerPlatform::State::JumpyDead);
				soundDead.Play();
			}
		}
		jumpy.StickPlayform(playform);
		if (jumpy.OutsideBorders())
		{
			playform.SetState(PlayerPlatform::State::JumpyDead);
			soundDead.Play();
		}
		jumpy.Respawn(playform, frameTime);

		playform.ClampScreen();
		jumpy.ClampScreen();

		if (jumpy.NoLives())
		{
			lost = true;
			soundLost.Play();
		}

		if (wnd.kbd.KeyIsPressed(VK_SPACE))
		{
			playform.Cheat();
		}
	}
}

void Game::ComposeFrame()
{
	if (lost)
	{
		gfx.DrawRect(wonLoseRect, colLost);
	}
	else if (won)
	{
		gfx.DrawRect(wonLoseRect, colWon);
	}
	jumpy.DrawLives(gfx);
	jumpy.DrawJumpIn(gfx);
	jumpy.DrawRespIn(gfx);
	//draw win indicator
	gfx.DrawRect(RectF(winInTopLeft, winInWidth, winInHeight), winInColBase);
	gfx.DrawRect(RectF(winInTopLeft, winInDrawChargeRatio * float(currentPlaty),
		winInHeight), winInColCharge);
	for (int i = std::max(0, currentPlaty - nPlatsBackCheck); i < currentPlaty; i++)
	{
		plats[i].Draw(gfx);
	}
	playform.Draw(gfx);
	jumpy.DrawBorders(gfx);
	jumpy.Draw(gfx);
}
