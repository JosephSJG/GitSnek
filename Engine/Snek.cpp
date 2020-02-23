#include "Snek.h"


Snek::Snek(const Location& loc)	

{
	segments[0].InitHead(loc);
}



void Snek::MoveBy(const Location& delta_loc)
{
	for (int i = nSegs - 1; i > 0; -- i)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snek::Grow(int& ColorChange)
{
	if (nSegs < nSegmax)
	{
		segments[nSegs].InitBody(ColorChange);
		++nSegs;
	}

	
}

void Snek::Draw(Board& brd) const
{
	for (int i = 0; i < nSegs; ++i)
	{
		segments[i].Draw(brd);
	}
}

const Location& Snek::GetNextHeadLocation(const Location& delta_loc) const
{
	Location l = ( segments[0].GetLocation() );
	l.Add(delta_loc);
	return l;
}

bool Snek::IsInTileExceptEnd(const Location& target) const
{
	for (int i = 0; i < nSegs - 1; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

bool Snek::IsInTile(const Location& target) const
{
	for (int i = 0; i < nSegs - 1; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}



void Snek::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snek::headColor;
}

void Snek::Segment::InitBody(int& ColorChange)
{	

	++ColorChange;
	if (ColorChange > 3)
	{
		ColorChange = 1;
	}
	c.SetG(ColorChange * 85);
}

void Snek::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snek::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snek::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

Location Snek::Segment::GetLocation() const
{
	return loc;
}
