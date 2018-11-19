#include <Idle.h>
#include <Colliding.h>

#include <string>

void Idle::handleInput() {}
void Idle::update() {}

void Idle::colliding(PlayerFSM* a)
{
	std::cout << "Idle -> Colliding" << std::endl;
	a->setCurrent(new Colliding());
	delete this;
}
