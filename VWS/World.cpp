#include "World.h"
//#include"Animal.h"
#include"Organisms.h"
#include<algorithm>
#include"ConsolePrinter.h"

bool operator==(const vec2d& v1, const vec2d& v2)
{
	return v1.x == v2.x && v1.y == v2.y;
}

World::World(vec2d worldsize, vec2d framepos) : worldSize(worldsize), framepos(framepos)
{
	worldboard = new species*[worldsize.x];
	for (int i = 0; i < worldsize.x; i++)
	{
		worldboard[i] = new species[worldsize.y];
		for (int j = 0; j < worldsize.y; j++)
		{
			worldboard[i][j] = FREE;
		}

	}
	exist = true;
	createOrganism(WOLF, vec2d(4, 5));
	createOrganism(SHEEP, vec2d(10, 1));
	createOrganism(FOX, vec2d(11, 11));
	createOrganism(GRASS, vec2d(19, 17));
	//organisms.push_back((new Wolf(this, vec2d(4,5))));
	//organisms.push_back((new Grass(this, vec2d(5, 5))));

	specChars = {
	{HUMAN, '$' },
	{WOLF, 'W'},
	{SHEEP, 'S'},
	{FOX, 'F'},
	{TURTLE, 'T'},
	{ANTELOPE, 'A'},
	{CYBER_SHEEP, 'C'},
	{GRASS, 'G'},
	{DANDELION, 'D'},
	{GUARANA, 'U'},
	{DEADLY_BERRY, 'E'},
	{SOS_HOGWEED, 'H'}
	};

}

bool World::createOrganism(species sp, vec2d pos)
{
	Organism* org;
	switch (sp)
	{
	case HUMAN:
		//todo
		break;
	case WOLF:
		org = new Wolf(this, pos);
		break;
	case SHEEP:
		org = new Sheep(this, pos);
		break;
	case FOX:
		org = new Fox(this, pos);
		break;
	case TURTLE:
		//todo
		break;
	case ANTELOPE:
		//todo
		break;
	case CYBER_SHEEP:
		//todo
		break;
	case GRASS:
		org = new Grass(this, pos);
		break;
	case DANDELION:
		//todo
		break;
	case GUARANA:
		//todo
		break;
	case DEADLY_BERRY:
		//todo
		break;
	case SOS_HOGWEED:
		//todo
		break;
	default :
		return false;
	}
	organisms.push_back(org);
	worldboard[org->getPos().x][org->getPos().y] = org->mySpecies;
	return true;
}

vec2d World::getRandomDirection()
{
	static unsigned int seed = 234235;
	srand(seed);
	int d = rand() % 4;
	static vec2d dir;
	switch (d) {
	case 0:
		dir.x = 0;
		dir.y = -1;
		break;
	case 1:
		dir.x = 1;
		dir.y = 0;
		break;
	case 2:
		dir.x = 0;
		dir.y = 1;
		break;
	case 3:
		dir.x = -1;
		dir.y = 0;
		break;
	}
	seed += time(NULL);
	seed %= 42792384;
	return dir;
}

void World::update()
{
	/*for (int i = 0; i < worldSize.x; i++)
	{
		for (int j = 0; j < worldSize.y; j++)
		{
			worldboard[i][j] = FREE;
		}
	}*/

	std::vector<Organism*>::iterator p;
	//p = organisms.begin();
	vec2d orgpos;
	for (Organism* o : organisms)
	{
		if (!o->isAlive())
		{
			p = std::find(organisms.begin(), organisms.end(), o);
			organisms.erase(p);
			worldboard[o->getPos().x][o->getPos().y] = FREE;
			delete o;
		}
		else
		{
			orgpos = o->getPos();
			worldboard[orgpos.x][orgpos.y] = o->mySpecies;
		}
		//if(p < organisms.end())p++;
	}
}
void World::nextRound()
{
	update();
	std::sort(organisms.begin(), organisms.end());
	std::reverse(organisms.begin(), organisms.end());
	vec2d prevpos;
	//std::vector<Organism*>::iterator p;
	size_t p = 0;
	Organism* o;
	//for (Organism* o : organisms)
	while (p < organisms.size())
	{
		o = organisms[p];
		prevpos = o->getPos();
		o->action();
		if (!(prevpos == o->getPos()))
		{
			worldboard[prevpos.x][prevpos.y] = FREE;
			worldboard[o->getPos().x][o->getPos().y] = o->mySpecies;
		}
		p++;
	}
}
void World::draw()
{
	for (Organism* o : organisms)
	{
		o->draw();
	}

	//test
	for (int i = 0; i < worldSize.x; i++)
	{
		for (int j = 0; j < worldSize.y; j++)
		{
			ConsolePrinter::goToXY(23 + i,1 + j);
			ConsolePrinter::writeChar(specChars[worldboard[i][j]]);
		}
	}
}

species World::getFieldSpecies(vec2d pos)
{
	if (pos.x >= 0 && pos.y >= 0 &&
		pos.x < worldSize.x && pos.y < worldSize.y) {
		return worldboard[pos.x][pos.y];
	}
	
	return ERR;
}

Organism* World::getOrganismOnPosition(vec2d pos)
{
	for (Organism* o : organisms)
	{
		if (pos == o->getPos()) return o;
	}
	return NULL;
}

vec2d World::getFramePos()
{
	return framepos;
}

char World::getSpecChar(species sp)
{
	return specChars[sp];
}

World::~World()
{
	organisms.clear();
	for(int i =0 ; i < worldSize.x;i++)
	{
		delete[] worldboard[i];
	}
	delete[] worldboard;
}
