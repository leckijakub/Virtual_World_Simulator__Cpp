#include "Human.h"

Human::Human(World* world, vec2d pos) : Animal(world, HUMAN, pos)
{
	initiative = 4;
	strenght = 5;
	nextmove = vec2d(0, 0);
}

void Human::draw()
{

	Organism::draw();
}
bool Human::tryMultiply()
{
	return false;
}
bool Human::setNextMove(vec2d dir)
{
	if (world->getFieldSpecies(pos + dir) != ERR)
	{
		nextmove = dir;
		return true;
	}
	else return false;

}
bool Human::action()
{
	if (world->getFieldSpecies(pos + nextmove) == ERR) nextmove = vec2d(0, 0);
	if (!(nextmove == vec2d(0, 0))) return Animal::action();
	else return true;
}

bool Human::makeMove()
{
	species field = world->getFieldSpecies(pos + nextmove);

	if (field == FREE)
	{
		pos = pos + nextmove;
		return true;
	}
	else
	{
		Organism* def = world->getOrganismOnPosition(pos + nextmove);
		if (collision(*def))
		{
			pos = pos + nextmove;
			return true;
		}
		else return false;
	}
}

vec2d Human::getNextMove()
{
	return nextmove;
}

std::string Human::toString()
{
	return "Human on position X:" + std::to_string(pos.x) + " ,Y:" + std::to_string(pos.y);
}