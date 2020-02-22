#pragma once

class Entity
{
	enum class Direction { STOP = 0, LEFT, RIGHT, UP, DOWN }direction;

	void Move();
};

