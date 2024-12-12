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
#include "entities/Vector2i.h"

class Player
{
public:
	Player()
	{
		TextureWrapper wrapper = TextureWrapper(AssetService::getInstance().getSprite(ESprite::PLAYER), {32, 32}, {200, 200});
		wrapper.setSourceRect({0, 0, 32, 32});
		this->texture = wrapper;
		prevFrame = GetTime();
		spriteAnimation = {0,0};
	}
	~Player()
	{
	}

	void logic()
	{
		// applyGravity();
		movement();
		// handleCollision();
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
	float animationDelay = 0.2f; // seconds
	double prevFrame;
	Vector2 spriteAnimation;					// Keeps track of (1) Sprite cycling and (2) Player direction
	enum Direction { Down, Left, Right, Up };		// Used in conjuction with spriteAnimation, makes sure sprite direction matches with player direction
	std::vector <Vector2i> tiles;				// Holds eight points of the player for accurate collision	

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
		if (InputService::getInstance().isKeyDown(KEY_A))
		{
			spriteAnimation.y = Left;
			velocity.x = -moveSpeed;
			animate();
		}
		else if (InputService::getInstance().isKeyDown(KEY_D))
		{
			spriteAnimation.y = Right;
			velocity.x = moveSpeed;
			animate();
		} else {
			velocity.x = 0.0f;
		}
		positionUpdates();
		handleCollision();

		if (!groundCollision) {
			velocity.y += gravity;
		} else {
			velocity.y = 0.0f;
		}

		if (InputService::getInstance().isKeyPressed(KEY_W) && groundCollision)
		{
			velocity.y -= jumpPower;
		}

		this->texture.move(velocity);
	}

	void animate()
	{
		if (GetTime() - prevFrame > animationDelay)
		{
			spriteAnimation.x = std::fmod(spriteAnimation.x + 1,3);

			Rectangle sourceRect = this->texture.getSourceRect();
			sourceRect.x = spriteAnimation.x * this->texture.getSize().x;
			sourceRect.y = spriteAnimation.y * this->texture.getSize().y;
			// sourceRect.x = std::fmod(sourceRect.x, 3 * this->texture.getSize().x);
			this->texture.setSourceRect(sourceRect);
			prevFrame = GetTime();
		}
	}

	void positionUpdates() {
	const Vector2 pos = this->texture.getPosition();
	const Vector2 size = this->texture.getSize();
	const int tileSize = MapService::getInstance().getMap().getTileSize();

	const float bottom = pos.y + size.y + velocity.y;
	const float left = pos.x + velocity.x;
	const float right = pos.x + size.x + velocity.x;
	const float top = pos.y + velocity.y;

	Vector2i topLeft(Vector2i((int)(left + 5) / tileSize, (int)top / tileSize));				// +5 to separate top from side
	Vector2i topRight(Vector2i((int)(right - 5) / tileSize, (int)top / tileSize));			// -5 to separate top from side

	Vector2i leftTop(Vector2i((int)left / tileSize, (int)(top + 5) / tileSize));
	Vector2i leftBottom(Vector2i((int)left / tileSize, (int)(bottom - 5) / tileSize));
	Vector2i rightTop(Vector2i((int)right / tileSize, (int)(top + 5) / tileSize));
	Vector2i rightBottom(Vector2i((int)right / tileSize, (int)(bottom - 5) / tileSize));

	Vector2i bottomLeft(Vector2i((int)(left + 5) / tileSize, (int)bottom / tileSize));		// +5 to separate bottom from side
	Vector2i bottomRight(Vector2i((int)(right - 5) / tileSize, (int)bottom / tileSize));		// -5 to separate bottom from side


	tiles.clear();

	tiles.push_back(topLeft);
	tiles.push_back(topRight);

	tiles.push_back(leftTop);
	tiles.push_back(leftBottom);
	tiles.push_back(rightTop);
	tiles.push_back(rightBottom);

	tiles.push_back(bottomLeft);
	tiles.push_back(bottomRight);
	}

	/**
	 * Stores the current position
	 * Applies the current velocity
	 * Checks for collision, and removes all velocities that are causing collisions
	 * Set the object exactly against the object it is colliding with position
	 */
	void handleCollision()
	{

		timesCollision.clear();

	for (int i = 0; i < tiles.size(); i++)
	{
		if (MapService::getInstance().getMap().getColMap()[tiles[i].y][tiles[i].x] == 1)
		{
			timesCollision.push_back(i);
		}
	}

	groundCollision = false;

	if (timesCollision.size() > 0)
	{
		for (int i = 0; i < timesCollision.size(); i++)
		{
			if (timesCollision[i] == 0 || timesCollision[i] == 1)						//Topleft and Topright
			{
				velocity.y = 0;
			}
			else if (timesCollision[i] == 2 || timesCollision[i] == 3 ||				//Lefttop and Leftbottom
				timesCollision[i] == 4 || timesCollision[i] == 5)						//Righttop and Lefttop
			{
				velocity.x = 0;
			}
			else if (timesCollision[i] == 6 || timesCollision[i] == 7)					 //Bottomleft and Bottomright
			{
				groundCollision = true;
			}
		}
	}

		// Set velocity.x based on going right or left

		// Take current position of all 4 corners
		// Apply velocity
		// Calculate the 8 points
		// Add them to a list

		// Empty vector of amount of collisions
		// Loop through the points
		// Check the collisionmap for intersection
		// If so, add item to the vector of collisions

		// Set groundcollision to false
		// Loop through collisions
		// Based on their location (TopLeft, RightTop, etc) change the velocity
		
		// Apply gravity if not on the floor
		// If jumping and on the floor, go up

		// Move using velocity

		// Vector2 tempPos = this->texture.getPosition();
		// this->texture.move(velocity);

		// groundCollision = false;
		// std::unordered_map<ECorner, bool> collisions = MapService::getInstance().getMap().checkForCollision(this->texture);

		// if (collisions[ECorner::BOTTOM_LEFT] || collisions[ECorner::BOTTOM_RIGHT])
		// {
		// 	velocity.y = 0.0f;
		// 	groundCollision = true;
		// 	this->texture.setPosition({this->texture.getPosition().x, floorf(this->texture.getPosition().y / MapService::getInstance().getMap().getTileSize()) * MapService::getInstance().getMap().getTileSize()});
		// }
		// if (collisions[ECorner::LEFT_TOP] && collisions[ECorner::LEFT_BOTTOM])
		// {
		// 	velocity.x = 0.0f;
		// 	this->texture.setPosition({ceilf(this->texture.getPosition().x / MapService::getInstance().getMap().getTileSize()) * MapService::getInstance().getMap().getTileSize(), this->texture.getPosition().y});
		// }
		// if (collisions[ECorner::TOP_LEFT] || collisions[ECorner::TOP_RIGHT])
		// {
		// 	velocity.y = 0.0f;
		// 	this->texture.setPosition({this->texture.getPosition().x, (ceilf(this->texture.getPosition().y / MapService::getInstance().getMap().getTileSize())) * MapService::getInstance().getMap().getTileSize()});
		// }
		// if (collisions[ECorner::RIGHT_TOP] && collisions[ECorner::RIGHT_BOTTOM])
		// {
		// 	velocity.x = 0.0f;
		// 	this->texture.setPosition({floorf(this->texture.getPosition().x / MapService::getInstance().getMap().getTileSize()) * MapService::getInstance().getMap().getTileSize(), this->texture.getPosition().y});
		// }
	}

	void outofboundsCheck()
	{
		if (this->texture.getPosition().y > StateService::getInstance().getScreenSize().y)
		{
			GameService::getInstance().setGameOver(true);
			AudioService::getInstance().setMusic(EMusic::GAME_OVER);
			AudioService::getInstance().playMusic();
		}
	}
};

#endif
