#ifndef INPUT_H
#define INPUT_H
class Input
{
public:
	Input();
	~Input();

	void setCurrent(int result);
	int getCurrent();

private:
	int m_current;
};
#endif