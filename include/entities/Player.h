#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "enums/ECorner.h"
#include "enums/ESound.h"
#include "services/AssetService.h"
#include "entities/TextureWrapper.h"
#include "entities/Vector2i.h"
#include <unordered_map>
#include <algorithm>
#include <cstdint>

class PBullet;

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
		/** Fall out of the map when the jelly has been killed */
		if(this->health == 0) {
			fall();
			return;
		}
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

	void takeDamage(uint8_t damage) {
		this->health = std::max(health - damage, 0);
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

	void applyGravity();
	void movement();
	void move(Vector2 velocity);
	void animate();
	void positionUpdates();
	void handleCollision();
	void consumableCollision();
	void outofboundsCheck();
	void rotateGun();
	void drawGun();
	void shoot();
	void fall(); 				// Lets the player fall out of the map when he dies
};

#endif
