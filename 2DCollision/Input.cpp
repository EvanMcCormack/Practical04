#include <Input.h>

Input::Input() 
{
	m_current = 0;
}
Input::~Input() {}

void Input::setCurrent(int result) {
	m_current = result;
}

int Input::getCurrent() {
	return m_current;
}
