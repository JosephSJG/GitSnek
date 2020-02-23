#include "Goal.h"

Goal::Goal(std::mt19937& rng, const Board& brd, const Snek& snek)
{
	Respawn(rng, brd, snek);
}

void Goal::Respawn(std::mt19937& rng, const Board& brd, const Snek& snek)
{
	std::uniform_int_distribution<int> xDist(1, brd.GetGridWidth() - 2);
	std::uniform_int_distribution<int> yDist(1, brd.GetGridHeight() - 2);
	
	Location newLoc;
	do
	{
		newLoc = { xDist(rng) , yDist(rng) };
	}
	 while (snek.IsInTile(newLoc));
		loc = newLoc;
}

void Goal::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Goal::GetLocation() const
{
	return loc;
}
	
