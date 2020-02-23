#pragma once
#include "Graphics.h"
#include "Location.h"


class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool isInsideBoard(const Location& loc) const;
	void DrawPerimeter(Color c);
	int boardX = ((gfx.ScreenWidth/dimension) - width)/2;
	int boardY = ((gfx.ScreenHeight / dimension) - height) / 2;

private:
	static constexpr int dimension = 20;
	static constexpr int width = 30;
	static constexpr int height = 20;
	//random change
	Graphics& gfx;



};
