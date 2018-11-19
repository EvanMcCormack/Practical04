#ifndef COLLIDING_H
#define COLLIDING_H

#include <State.h>

class Colliding : public State
{
public:
	Colliding() {};
	~Colliding() {};
	void idling(PlayerFSM* a);
};

#endif // !COLLIDING_H
