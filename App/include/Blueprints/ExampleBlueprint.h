#pragma once
#include <GameObject.h>
#include <Math/Vector2.h>


class ExampleBlueprint : public GameObject
{
private:
	Vector2F startPos;


public:
	ExampleBlueprint(Vector2F startPos);


	virtual void ConstructGameObject() override;
};