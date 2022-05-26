#ifndef ITEM_H
#define ITEM_H


#include "../Buttons/Button.h"


namespace ItemComponent
{
	struct WorldCollision
	{
		Button* button;
		sf::FloatRect radius;
	};

	struct Inventory
	{
		// sprite.setScale(16 / this->sprite.get size x, 16/ this->sprite.get size y)
		sf::Sprite inventorySprite;
	};
}


class Item : public sf::Sprite
{
private:
	bool deleted;

	//===COMPONENTS===//
	ItemComponent::WorldCollision* collisionComponent;
	ItemComponent::Inventory* inventoryComponent;
	//---COMPONENTS---//
public:
	Item();
	Item(const sf::Texture& texture);
	Item(const sf::Texture& texture, const sf::IntRect& rectangle);
	virtual ~Item();


	void add(ItemComponent::WorldCollision* collisionComponent);
	void add(ItemComponent::Inventory* inventoryComponent);


	ItemComponent::WorldCollision*& getCollisionComponent();
	ItemComponent::Inventory*& getInventoryComponent();

	void setPosition(sf::Vector2f position);

	const bool& getDeleted() const;


	//===Update===//
	void update(const float& dt);
	//---Update---//
};


#endif // !LITEM_H



