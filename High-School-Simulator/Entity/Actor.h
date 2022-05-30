#ifndef ACTOR_H
#define ACTOR_H


#include "ActorComponents.h"


class Actor : sf::Sprite
{
protected:
	bool deleted;

	//===COMPONENTS===//
	ActorComponents::Movement* movementComponent;
	//---COMPONENTS---//
public:
	Actor();
	Actor(const sf::Texture& texture);
	Actor(const sf::Texture& texture, const sf::IntRect& rectangle);
	virtual ~Actor();

	void add(ActorComponents::Movement* movementComponent);

	ActorComponents::Movement*& getMovementComponent();

	const bool& getDeleted() const;
	void setDeleted(bool condition);

	//===Update===//
	void updateMovement(const float& dt);
	void update(const float& dt);
	//---Update---//
};


#endif
