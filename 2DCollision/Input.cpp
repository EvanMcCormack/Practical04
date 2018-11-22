#include <Input.h>

Input::Input() 
{
	m_current = AABBToAABB;
}
Input::~Input() {}

void Input::setCurrent(collisionType a) {
	m_current = a;
}

Input::collisionType Input::getCurrent() {
	return m_current;
}
