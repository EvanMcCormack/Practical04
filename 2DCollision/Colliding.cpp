#include <Colliding.h>
#include <Idle.h>

#include <string>

void Colliding::idling(PlayerFSM* a)
{
	std::cout << "Colliding -> Idling" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}