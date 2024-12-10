#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <unordered_map>
#include "services/AssetService.h"
#include "services/MapService.h"
#include "services/InputService.h"
#include "entities/TextureWrapper.h"
#include "enums/ECorner.h"

class Player
{
public:
	Player()
	{
		TextureWrapper wrapper = TextureWrapper(AssetService::getInstance().getSprite(ESprite::PLAYER), {32, 32}, {200, 200});
		wrapper.setSourceRect({0, 0, 32, 32});
		this->texture = wrapper;
	}
	~Player()
	{
	}

	void logic()
	{
		gravity();
		movement();
		handleCollision();
		applyVelocity();
	}

	void draw()
	{
		DrawTextureRec(this->texture.getTexture(), this->texture.getSourceRect(), this->texture.getPosition(), WHITE);
	}

	TextureWrapper &getTexture()
	{
		return this->texture;
	}

protected:
private:
	// Vector2 position;
	TextureWrapper texture;
	Vector2 velocity = {0, 0};

	std::vector<unsigned int> timesCollision; // Holds the amount of times the player has collided with a tile, and which corner of the player is touching a tile
	bool groundCollision;					  // Keeps track of whether or not the player has collided with the ground
	bool crateTopCollision;
	/**
	 * Holds the corners of the player
	 * Is used for precise collision detection
	 */
	// Keeps tracko f whether or not the player has collided with the top of the crate
	// std::unordered_map<Vector2, >

	void gravity()
	{

		// PositionUpdate();
		// Collision();

		// if (!groundCollision && !crateTopCollision)
		// {
		if (!groundCollision)
		{
			velocity.y += 0.6f;
		}
		else
		{
			velocity.y = 0.0f;
		}

		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (groundCollision == true || crateTopCollision == true))
		// {
		// 	velocity.y = -GetJumpSpeed();
		// }

		// this->texture.move(velocity);
	}

	void movement()
	{
		velocity.x = 0.0f;
		if (InputService::getInstance().isKeyDown(KEY_A)) {
			// std::cout << "Left" << std::endl;
			velocity.x -= 3.0f;
		} else if (InputService::getInstance().isKeyDown(KEY_D)) {
			velocity.x += 3.0f;
			// std::cout << "Right" << std::endl;
		}

		if(InputService::getInstance().isKeyPressed(KEY_SPACE) && groundCollision) {
			velocity.y -= 7.2f;
		}

		this->texture.move(velocity);
	}

	void handleCollision()
	{
		groundCollision = false;
		std::unordered_map<ECorner, bool> collisions = MapService::getInstance().getMap().checkForCollision(this->texture);

		if (collisions[ECorner::BOTTOM_LEFT] || collisions[ECorner::BOTTOM_RIGHT])
		{
			this->texture.move({0, -velocity.y});
			velocity.y = 0.0f;
			groundCollision = true;
		}
		if (collisions[ECorner::LEFT_TOP] && collisions[ECorner::LEFT_BOTTOM]) {
			this->texture.move({+velocity.x, 0});
			velocity.x = 0.0f;
		}
		if (collisions[ECorner::TOP_LEFT] || collisions[ECorner::TOP_RIGHT]) {
			this->texture.move({0, +velocity.y});
			velocity.y = 0.0f;
		}
		if (collisions[ECorner::RIGHT_TOP] && collisions[ECorner::RIGHT_BOTTOM]) {
			this->texture.move({-velocity.x, 0});
			velocity.x = 0.0f;
		}
	}

	void applyVelocity() {
		// std::cout << velocity.x << std::endl;
		this->texture.move(velocity);
	}

	// timesCollision.clear();

	// for (int i = 0; i < tiles.size(); i++)
	// {
	// 	if (GetColMap()[tiles[i].y][tiles[i].x] == 1)
	// 	{
	// 		timesCollision.push_back(i);
	// 	}
	// }

	// groundCollision = false;

	// if (timesCollision.size() > 0)
	// {
	// 	for (int i = 0; i < timesCollision.size(); i++)
	// 	{
	// 		if (timesCollision[i] == 0 || timesCollision[i] == 1)						//Topleft and Topright
	// 		{
	// 			velocity.y = 0;
	// 		}
	// 		else if (timesCollision[i] == 2 || timesCollision[i] == 3 ||				//Lefttop and Leftbottom
	// 			timesCollision[i] == 4 || timesCollision[i] == 5)						//Righttop and Lefttop
	// 		{
	// 			velocity.x = 0;
	// 		}
	// 		else if (timesCollision[i] == 6 || timesCollision[i] == 7)					 //Bottomleft and Bottomright
	// 		{
	// 			groundCollision = true;
	// 		}
	// 	}
	// }
	// }
};

#endif
