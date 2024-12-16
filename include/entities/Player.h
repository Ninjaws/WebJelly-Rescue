#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "services/AssetService.h"
#include "services/MapService.h"
#include "services/InputService.h"
#include "services/GameService.h"
#include "entities/TextureWrapper.h"
#include "enums/ECorner.h"
#include "enums/ESound.h"
#include "entities/Vector2i.h"
#include "entities/PBullet.h"
#include <unordered_map>
#include <algorithm>

class Player
{
public:
	Player()
	{
		this->texture = TextureWrapper(AssetService::getInstance().getSprite(ESprite::PLAYER), {32, 32}, {200, 200});
		prevFrame = GetTime();
		spriteAnimation = {0, Right};
		this->gunRight = TextureWrapper(AssetService::getInstance().getSprite(ESprite::PLAYER_GUN_RIGHT), {58, 29}, {0, 0});
		this->gunLeft = TextureWrapper(AssetService::getInstance().getSprite(ESprite::PLAYER_GUN_LEFT), {58, 29}, {0, 0});
		this->ammo = max_ammo;
		this->prevShot = GetTime();
		this->health = max_health;
	}

	~Player()
	{
	}

	void logic()
	{
		rotateGun();
		shoot();
		movement();
		outofboundsCheck();
		consumableCollision();
	}

	void draw()
	{
		drawGun();
		DrawTextureRec(this->texture.getTexture(), this->texture.getSourceRect(), this->texture.getPosition(), gainedPowerup ? RED : WHITE);
	}

	TextureWrapper &getTexture()
	{
		return this->texture;
	}

	void setPosition(Vector2 pos)
	{
		this->texture.setPosition(pos);
	}

	int getAmmo()
	{
		return this->ammo;
	}

	uint8_t getHealth()
	{
		return this->health;
	}

	uint8_t getMaxHealth()
	{
		return this->max_health;
	}

protected:
private:
	TextureWrapper texture;
	TextureWrapper gunLeft;
	TextureWrapper gunRight;
	Vector2 velocity = {0, 0};
	float jumpPower = 7.2f;
	float moveSpeed = 5.0f;
	float gravity = 0.6f;
	float animationDelay = 0.2f; // In seconds
	double prevFrame;			 // Time since the last frame
	Vector2i spriteAnimation;	 // Keeps track of (1) Sprite cycling and (2) Player direction
	enum Direction
	{
		Down,
		Left,
		Right,
		Up
	}; // Used in conjuction with spriteAnimation, makes sure sprite direction matches with player direction

	std::vector<Vector2i> tiles;			  // Holds eight points of the player for accurate collision
	std::vector<unsigned int> timesCollision; // Holds the amount of times the player has collided with a tile, and which corner of the player is touching a tile
	bool groundCollision;					  // Keeps track of whether or not the player has collided with the ground
	bool crateTopCollision;					  // Whether the player is standing on top of a crate

	uint8_t ammo;			 // Current ammo of the player
	uint8_t max_ammo = 100;	 // Max ammo of the player
	float firingRate = 0.2f; // Delay in seconds
	double prevShot;		 // The last time the player fired a bullet
	uint8_t health;			 // Current health of the player
	uint8_t max_health = 10; // Max health of the player
	bool gainedPowerup = false;

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
		}
		else
		{
			velocity.x = 0.0f;
		}
		positionUpdates();
		handleCollision();

		if (!groundCollision)
		{
			velocity.y += gravity;
		}
		else
		{
			velocity.y = 0.0f;
		}

		if (InputService::getInstance().isKeyPressed(KEY_W) && groundCollision)
		{
			velocity.y -= jumpPower;
		}
		move(velocity);
	}

	void move(Vector2 velocity)
	{
		this->texture.move(velocity);
	}

	void animate()
	{
		if (GetTime() - prevFrame > animationDelay)
		{
			spriteAnimation.x = std::fmod(spriteAnimation.x + 1, 3);

			Rectangle sourceRect = this->texture.getSourceRect();
			sourceRect.x = spriteAnimation.x * this->texture.getSize().x;
			sourceRect.y = spriteAnimation.y * this->texture.getSize().y;
			// sourceRect.x = std::fmod(sourceRect.x, 3 * this->texture.getSize().x);
			this->texture.setSourceRect(sourceRect);
			prevFrame = GetTime();
		}
	}

	void positionUpdates()
	{
		const Vector2 pos = this->texture.getPosition();
		const Vector2 size = this->texture.getSize();
		const int tileSize = MapService::getInstance().getMap().getTileSize();

		const float bottom = pos.y + size.y + velocity.y;
		const float left = pos.x + velocity.x;
		const float right = pos.x + size.x + velocity.x;
		const float top = pos.y + velocity.y;

		Vector2i topLeft(Vector2i((int)(left + 5) / tileSize, (int)top / tileSize));   // +5 to separate top from side
		Vector2i topRight(Vector2i((int)(right - 5) / tileSize, (int)top / tileSize)); // -5 to separate top from side

		Vector2i leftTop(Vector2i((int)left / tileSize, (int)(top + 5) / tileSize));
		Vector2i leftBottom(Vector2i((int)left / tileSize, (int)(bottom - 5) / tileSize));
		Vector2i rightTop(Vector2i((int)right / tileSize, (int)(top + 5) / tileSize));
		Vector2i rightBottom(Vector2i((int)right / tileSize, (int)(bottom - 5) / tileSize));

		Vector2i bottomLeft(Vector2i((int)(left + 5) / tileSize, (int)bottom / tileSize));	 // +5 to separate bottom from side
		Vector2i bottomRight(Vector2i((int)(right - 5) / tileSize, (int)bottom / tileSize)); // -5 to separate bottom from side

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
				if (timesCollision[i] == 0 || timesCollision[i] == 1) // Topleft and Topright
				{
					velocity.y = 0;
				}
				else if (timesCollision[i] == 2 || timesCollision[i] == 3 || // Lefttop and Leftbottom
						 timesCollision[i] == 4 || timesCollision[i] == 5)	 // Righttop and Lefttop
				{
					velocity.x = 0;
				}
				else if (timesCollision[i] == 6 || timesCollision[i] == 7) // Bottomleft and Bottomright
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

	void consumableCollision()
	{
		/** Check for collisions with ammo packs */
		for (auto &ammoPack : CollectableService::getInstance().getAmmoPacks())
		{
			if (this->texture.getPosition().x + this->texture.getSize().x > ammoPack.getObject().getPosition().x &&
				this->texture.getPosition().x<ammoPack.getObject().getPosition().x + ammoPack.getObject().getSize().x && 
				this->texture.getPosition().y + this->texture.getSize().y> ammoPack.getObject().getPosition().y &&
				this->texture.getPosition().y < ammoPack.getObject().getPosition().y + ammoPack.getObject().getSize().y)
			{
				ammoPack.setPickedUp(true);
				AssetService::getInstance().playSound(ESound::AMMO_PICKUP);
				ammo += ammoPack.getAmmoAmount();
			}
		}

		/** Check for collisions with health packs */
		for (auto &healthPack : CollectableService::getInstance().getHealthPacks())
		{
			if (this->texture.getPosition().x + this->texture.getSize().x > healthPack.getObject().getPosition().x &&
				this->texture.getPosition().x<healthPack.getObject().getPosition().x + healthPack.getObject().getSize().x && 
				this->texture.getPosition().y + this->texture.getSize().y> healthPack.getObject().getPosition().y &&
				this->texture.getPosition().y < healthPack.getObject().getPosition().y + healthPack.getObject().getSize().y)
			{
				if (health < max_health)
				{
					healthPack.setPickedUp(true);
					AssetService::getInstance().playSound(ESound::HEAL_PICKUP);
					health = std::max(health + healthPack.getHealAmount(), (int)max_health);
				}
			}
		}

		/** Checks for collisions with powerups */
		for (auto &powerup : CollectableService::getInstance().getPowerups())
		{
			if (this->texture.getPosition().x + this->texture.getSize().x > powerup.getObject().getPosition().x &&
				this->texture.getPosition().x<powerup.getObject().getPosition().x + powerup.getObject().getSize().x && 
				this->texture.getPosition().y + this->texture.getSize().y> powerup.getObject().getPosition().y &&
				this->texture.getPosition().y < powerup.getObject().getPosition().y + powerup.getObject().getSize().y)
			{
				// if(health < max_health) {
				powerup.setPickedUp(true);
				AssetService::getInstance().playSound(ESound::POWERUP);
				jumpPower += powerup.getExtraJumpPower();
				gainedPowerup = true;
				// health = std::max(health+powerup.getHealAmount(),(int)max_health);
				// }
			}
		}

		/** Checks for collisions with the finish flag */
		auto &flag = CollectableService::getInstance().getFlag();
		if (this->texture.getPosition().x + this->texture.getSize().x > flag.getObject().getPosition().x &&
			this->texture.getPosition().x<flag.getObject().getPosition().x + flag.getObject().getSize().x && 
			this->texture.getPosition().y + this->texture.getSize().y> flag.getObject().getPosition().y &&
			this->texture.getPosition().y < flag.getObject().getPosition().y + flag.getObject().getSize().y)
		{
			flag.setTouched(true);
		}
	}

	void outofboundsCheck()
	{
		if (this->texture.getPosition().y > StateService::getInstance().getScreenSize().y)
		{
			this->health = 0;
			GameService::getInstance().setGameOver(true);
			AudioService::getInstance().setMusic(EMusic::GAME_OVER);
			AudioService::getInstance().playMusic();
		}
	}

	void rotateGun()
	{
		if (GameService::getInstance().getMouseWorldPos().x > this->texture.getPosition().x + (this->gunLeft.getSize().x) && spriteAnimation.y == Right)
		{
			float gunRotationRight = atan2(GameService::getInstance().getMouseWorldPos().y - (this->texture.getPosition().y + this->texture.getSize().y / 2.0),
										   GameService::getInstance().getMouseWorldPos().x - (this->texture.getPosition().x + this->texture.getSize().x / 2.0));
			this->gunRight.setRotation(gunRotationRight * 180 / M_PI);
		}
		else if (GameService::getInstance().getMouseWorldPos().x + (this->gunLeft.getSize().x / 2) < this->texture.getPosition().x && spriteAnimation.y == Left)
		{
			float gunRotationLeft = atan2(GameService::getInstance().getMouseWorldPos().y - (this->texture.getPosition().y + this->texture.getSize().y / 2.0),
										  (this->texture.getPosition().x + this->texture.getSize().x / 2.0) - GameService::getInstance().getMouseWorldPos().x);
			this->gunLeft.setRotation(-gunRotationLeft * 180 / M_PI);
		}
	}

	void drawGun()
	{
		if (GameService::getInstance().getMouseWorldPos().x > this->texture.getPosition().x + this->gunLeft.getSize().x && spriteAnimation.y == Right)
		{
			// + this->texture.getSize().x / 2.0f
			// + this->texture.getSize().y / 2.0f
			DrawTexturePro(
				this->gunRight.getTexture(),
				{0, 0, this->gunRight.getSize().x, this->gunRight.getSize().y},
				{this->texture.getPosition().x + this->texture.getSize().x / 2.0f,
				 this->texture.getPosition().y + this->texture.getSize().y / 2.0f,
				 this->gunRight.getSize().x,
				 this->gunRight.getSize().y},
				{this->gunRight.getSize().x / 2.0f, this->gunRight.getSize().y / 2.0f},
				this->gunRight.getRotation(),
				WHITE);
		}
		else if (GameService::getInstance().getMouseWorldPos().x + (this->gunLeft.getSize().x / 2) < this->texture.getPosition().x && spriteAnimation.y == Left)
		{
			DrawTexturePro(
				this->gunLeft.getTexture(),
				{0, 0, this->gunLeft.getSize().x, this->gunLeft.getSize().y},
				{this->texture.getPosition().x + this->texture.getSize().x / 2.0f,
				 this->texture.getPosition().y + this->texture.getSize().y / 2.0f,
				 this->gunLeft.getSize().x,
				 this->gunLeft.getSize().y},
				{this->gunLeft.getSize().x / 2.0f, this->gunLeft.getSize().y / 2.0f},
				this->gunLeft.getRotation(),
				WHITE);
		}
	}

	void shoot()
	{
		if (InputService::getInstance().isMouseButtonDown(MOUSE_BUTTON_LEFT) && GetTime() - prevShot > firingRate && groundCollision)
		{
			prevShot = GetTime();
			if (ammo == 0 || (GameService::getInstance().getMouseWorldPos().x > (this->texture.getPosition().x - this->gunLeft.getSize().x / 2.0f) && spriteAnimation.y == Left) ||
				(GameService::getInstance().getMouseWorldPos().x < (this->texture.getPosition().x + this->texture.getSize().x + gunLeft.getSize().x / 2.0f) && spriteAnimation.y == Right))
			{
				// Play empty gun sound
				AssetService::getInstance().playSound(ESound::NO_AMMO);
				return;
			}
			// Play shooting sound
			AssetService::getInstance().playSound(ESound::SHOOT);
			ammo--;

			Vector2 mouseWorldPos = GameService::getInstance().getMouseWorldPos();

			if (mouseWorldPos.x > this->texture.getPosition().x + (this->gunLeft.getSize().x) && spriteAnimation.y == Right ||
				mouseWorldPos.x + (this->gunLeft.getSize().x / 2) < this->texture.getPosition().x && spriteAnimation.y == Left)
			{

				float angleShot = atan2(mouseWorldPos.y - (this->texture.getPosition().y + this->texture.getSize().y / 2.0),
										mouseWorldPos.x - (this->texture.getPosition().x + this->texture.getSize().x / 2.0));

				/** Making the bullet originate from the gun's mouth */
				float offsetDistance = this->gunLeft.getSize().x / 2;
				float offsetX = cos(angleShot) * offsetDistance;
				float offsetY = sin(angleShot) * offsetDistance;
				Vector2 bulletStartLocation = {this->texture.getPosition().x + this->texture.getSize().x / 2.0f + offsetX,
											   this->texture.getPosition().y + this->texture.getSize().y / 2.0f + offsetY};

				GameService::getInstance().addPlayerBullet(PBullet(bulletStartLocation, angleShot));
			}
		}
	}
};

#endif
