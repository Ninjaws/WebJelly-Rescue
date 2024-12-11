#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <unordered_map>
#include "services/AssetService.h"
#include "services/MapService.h"
#include "services/InputService.h"
#include "services/GameService.h"
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
		applyGravity();
		movement();
		handleCollision();
		outofboundsCheck();
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
	TextureWrapper texture;
	Vector2 velocity = {0, 0};
	float jumpPower = 7.2f;
	float moveSpeed = 5.0f;
	float gravity = 0.6f;

	std::vector<unsigned int> timesCollision; // Holds the amount of times the player has collided with a tile, and which corner of the player is touching a tile
	bool groundCollision;					  // Keeps track of whether or not the player has collided with the ground
	bool crateTopCollision;
	/**
	 * Holds the corners of the player
	 * Is used for precise collision detection
	 */

	void applyGravity()
	{
		if (!groundCollision)
		{
			velocity.y += gravity;
		}
		else
		{
			// velocity.y = 0.0f;
		}
	}

	void movement()
	{
		velocity.x = 0.0f;
		if (InputService::getInstance().isKeyDown(KEY_A))
		{
			velocity.x -= moveSpeed;
		}
		else if (InputService::getInstance().isKeyDown(KEY_D))
		{
			velocity.x += moveSpeed;
		}

		if (InputService::getInstance().isKeyPressed(KEY_W) && groundCollision)
		{
			velocity.y -= jumpPower;
		}
	}

	/**
	 * Stores the current position
	 * Applies the current velocity
	 * Checks for collision, and removes all velocities that are causing collisions
	 * Set the object exactly against the object it is colliding with position
	 */
	void handleCollision()
	{
		Vector2 tempPos = this->texture.getPosition();
		this->texture.move(velocity);

		groundCollision = false;
		std::unordered_map<ECorner, bool> collisions = MapService::getInstance().getMap().checkForCollision(this->texture);

		if (collisions[ECorner::BOTTOM_LEFT] || collisions[ECorner::BOTTOM_RIGHT])
		{
			velocity.y = 0.0f;
			groundCollision = true;
			this->texture.setPosition({this->texture.getPosition().x, floorf(this->texture.getPosition().y / MapService::getInstance().getMap().getTileSize()) * MapService::getInstance().getMap().getTileSize()});
		}
		if (collisions[ECorner::LEFT_TOP] && collisions[ECorner::LEFT_BOTTOM])
		{
			velocity.x = 0.0f;
			this->texture.setPosition({ceilf(this->texture.getPosition().x / MapService::getInstance().getMap().getTileSize()) * MapService::getInstance().getMap().getTileSize(), this->texture.getPosition().y});
		}
		if (collisions[ECorner::TOP_LEFT] || collisions[ECorner::TOP_RIGHT])
		{
			velocity.y = 0.0f;
			this->texture.setPosition({this->texture.getPosition().x, (ceilf(this->texture.getPosition().y / MapService::getInstance().getMap().getTileSize())) * MapService::getInstance().getMap().getTileSize()});
		}
		if (collisions[ECorner::RIGHT_TOP] && collisions[ECorner::RIGHT_BOTTOM])
		{
			velocity.x = 0.0f;
			this->texture.setPosition({floorf(this->texture.getPosition().x / MapService::getInstance().getMap().getTileSize()) * MapService::getInstance().getMap().getTileSize(), this->texture.getPosition().y});
		}
	}

	void outofboundsCheck() {
		if(this->texture.getPosition().y > StateService::getInstance().getScreenSize().y) {
			GameService::getInstance().setGameOver(true);
			AudioService::getInstance().setMusic(EMusic::GAME_OVER);
			AudioService::getInstance().playMusic();
		}
	}
};

#endif
