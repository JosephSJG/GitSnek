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
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
    rng(std::random_device()()),
    brd(gfx),
    snek( {2 ,2 } ),
    goal(rng, brd, snek)
{
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
    if (!GameOver)
    {
       
        if (wnd.kbd.KeyIsPressed(VK_RETURN))
        {
            EnterPressed = true;          
        }
        if (wnd.kbd.KeyIsPressed(VK_RIGHT) && delta_loc.x == 0 && KeyUnlocked)
        {
            GameStarted = true;
            KeyUnlocked = false;
            delta_loc = { 1,0 };
           
        }
        if (wnd.kbd.KeyIsPressed(VK_LEFT) && delta_loc.x == 0 && KeyUnlocked)
        {
            GameStarted = true;
            KeyUnlocked = false;
            delta_loc = { -1,0 };
        }
        if (wnd.kbd.KeyIsPressed(VK_DOWN) && delta_loc.y == 0 && KeyUnlocked)
        {
            GameStarted = true;
            KeyUnlocked = false;
            delta_loc = { 0,1 };
        }
        if (wnd.kbd.KeyIsPressed(VK_UP) && delta_loc.y == 0 && KeyUnlocked)
        {
            GameStarted = true;
            KeyUnlocked = false;
            delta_loc = { 0,-1 };
        }

        if (GameStarted)
        {
                snekMoveCounter++;
                if (snekMoveCounter >= snekMovePeriod)
                {
                    KeyUnlocked = true;

                    snekMoveCounter = 0;
                    const Location Trakhs(snek.GetNextHeadLocation(delta_loc));
                    if (!brd.isInsideBoard(Trakhs) || snek.IsInTileExceptEnd(Trakhs))
                    {
                        GameOver = true;
                    }
                    else
                    {
                        const bool eating = (Trakhs == goal.GetLocation());
                        if (eating)
                        {
                            snek.Grow(ColorChange);
                            snekMoveChangeCounter++;

                            if (snekMoveChangeCounter >= snekMoveChangePeriod)
                            {
                                snekMovePeriod--;
                                snekMoveChangeCounter = 0;
                            }
                        }
                        snek.MoveBy(delta_loc);
                        if (eating)
                        {
                            goal.Respawn(rng, brd, snek);
                        }
                    }
                }
            }
        }
    } 


void Game::ComposeFrame()
{
    if (EnterPressed)
    {
        snek.Draw(brd);
        goal.Draw(brd);
        brd.DrawPerimeter(Colors::White);
        if (GameOver)
        {
            SpriteCodex::DrawGameOver(gfx.ScreenWidth / 2 - 50, gfx.ScreenHeight / 2 - 50, gfx);
        }
    }
    else
    {
        SpriteCodex::DrawTitle(gfx.ScreenWidth / 2 - 100, gfx.ScreenHeight / 2 - 100, gfx);
    }
}
