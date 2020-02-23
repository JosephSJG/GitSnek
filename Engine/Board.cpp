#include "Board.h"

Board::Board(Graphics& gfx)
	:
	gfx ( gfx )
{
}

void Board::DrawCell(const Location& loc, Color c)
{
	gfx.DrawRectDim((loc.x + boardX )* dimension , (loc.y + boardY) * dimension ,dimension, dimension, c);
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}
bool Board::isInsideBoard(const Location& loc) const
{
	return loc.x < width - 1 
		&& loc.x > 0
		&& loc.y < height - 1
		&& loc.y > 0;
}

void Board::DrawPerimeter(Color c)
{
	for (int i = 0; i < width ; i++)
	{
		DrawCell({ i  ,0 }, c);
	}
	for (int i = 0; i < width; i++)
	{
		DrawCell({ i ,  height -1 }, c);
	}
	for (int i = 0; i < height; i++)
	{
		DrawCell({ 0,i  }, c);
	}
	for (int i = 0; i < height; i++)
	{
		DrawCell({  width -1,i  }, c);
	}
}

