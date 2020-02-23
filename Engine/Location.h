#pragma once

class Location
{
public:
	void Add(const Location& value)
	{
		x += value.x;
		y += value.y;
	}
	bool operator ==(const Location& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	int x;
	int y;
};