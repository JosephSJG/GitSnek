#pragma once
#include "Board.h"
#include <assert.h>

class Snek
{

private:
	class Segment
	{
	public:
		void InitHead(const Location& loc);
		void InitBody(int& ColorChange);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;
		Location GetLocation() const;
	private:
		Location loc;
		Color c;
		
	};

public:
	Snek(const Location& loc);
	void MoveBy(const Location& delta_loc);
	void Grow(int& ColorChange);
	void Draw(Board& brd)const;
	const Location& GetNextHeadLocation(const Location& delta_loc)const;
	bool IsInTileExceptEnd(const Location& target)const;
	bool IsInTile(const Location& target)const;
	
	
private:
	static constexpr Color headColor = Colors::Yellow;	
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nSegmax = 100;
	Segment segments[nSegmax];
	int nSegs = 1;
	

};