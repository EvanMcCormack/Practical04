#ifndef INPUT_H
#define INPUT_H
class Input
{
public:
	Input();
	~Input();

	enum collisionType
	{
		AABBToAABB,
		AABBToCap,
		AABBToPoly,
		AABBToRay,
		CircleToAABB,
		CircleToCircle, 
		CircleToRay,
		CircleToCap,
		CircleToPoly, 
		RayToAABB,
		RayToCap,
		RayToCircle, 
		RayToPoly,
	};

	void setCurrent(collisionType a);
	collisionType getCurrent();
private:
	collisionType m_current;
};
#endif