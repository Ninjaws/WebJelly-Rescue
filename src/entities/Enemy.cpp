#include "entities/Enemy.h"
#include "services/PlayerService.h"
#include "services/MapService.h"
#include "services/BulletService.h"
#include <cmath>

void Enemy::logic()
{
    if (health == 0)
    {
        fall();
    }
    else
    {
        detectPlayer();
        if (playerSpotted)
        {
            shoot();
        }
        else
        {
            walk();
            checkForCollision();
            animate();
        }
    }
    texture.move(velocity);
}

void Enemy::walk()
{
    if (spriteAnimation.y == Left)
    {
        velocity.x = -moveSpeed;
    }
    else
    {
        velocity.x = moveSpeed;
    }
}

void Enemy::checkForCollision()
{
    std::vector corners = getCorners();
    std::vector<std::vector<int>> colMap = MapService::getInstance().getMap().getColMap();
    hasCollided = false;

    if (colMap[corners[2].y][corners[2].x] == 0 || colMap[corners[3].y][corners[3].x] == 0) // No ground below enemy
    {
        hasCollided = true;
    }
    else if (colMap[corners[0].y][corners[0].x] == 1 || colMap[corners[1].y][corners[1].x] == 1)
    {
        hasCollided = true;
    }

    if (hasCollided)
    {
        if (spriteAnimation.y == Left)
            spriteAnimation.y = Right;
        else
            spriteAnimation.y = Left;

        velocity.x *= -1;
    }
}

std::vector<Vector2i> Enemy::getCorners()
{
    float bottom = texture.getPosition().y + texture.getSize().y + velocity.y;
    float left = texture.getPosition().x + velocity.x;
    float right = texture.getPosition().x + texture.getSize().x + velocity.x;
    float top = texture.getPosition().y + velocity.y;

    int tileSize = MapService::getInstance().getMap().getTileSize();
    Vector2i leftCenter = Vector2i((int)(left - (spriteAnimation.y == Left ? gunLeft.getSize().x * (2.0f / 3.0f) : 0.0f)) / tileSize, (int)(bottom - texture.getSize().y / 2.0) / tileSize);
    Vector2i rightCenter = Vector2i((int)(right + (spriteAnimation.y == Right ? gunRight.getSize().x * (2.0f / 3.0f) : 0.0f)) / tileSize, (int)(bottom - texture.getSize().y / 2.0) / tileSize);

    Vector2i bottomLeft(Vector2i((int)(left + 5) / tileSize, (int)bottom / tileSize));
    Vector2i bottomRight(Vector2i((int)(right - 5) / tileSize, (int)bottom / tileSize));

    std::vector<Vector2i> corners;

    corners.push_back(leftCenter);
    corners.push_back(rightCenter);

    corners.push_back(bottomLeft);
    corners.push_back(bottomRight);
    return corners;
}

void Enemy::animate()
{
    if (GetTime() - prevFrame > animationDelay || hasCollided)
    {
        spriteAnimation.x = std::fmod(spriteAnimation.x + 1, 3);

        Rectangle sourceRect = this->texture.getSourceRect();
        sourceRect.x = spriteAnimation.x * this->texture.getSize().x;
        sourceRect.y = spriteAnimation.y * this->texture.getSize().y;
        this->texture.setSourceRect(sourceRect);
        prevFrame = GetTime();
    }
}

void Enemy::drawHealthBar()
{
    float barLength = (this->texture.getSize().x / maxHealth) * health;
    DrawRectangle(this->texture.getPosition().x, this->texture.getPosition().y - 12.0f, barLength, 3, RED);
}

void Enemy::drawGun()
{
    if (this->spriteAnimation.y == Right)
    {
        DrawTexturePro(
            this->gunRight.getTexture(),
            {0, 0, this->gunRight.getSize().x, this->gunRight.getSize().y},
            {this->texture.getPosition().x + this->texture.getSize().x / 2.0f,
             this->texture.getPosition().y + this->texture.getSize().y / 2.0f,
             this->gunRight.getSize().x,
             this->gunRight.getSize().y},
            {this->gunRight.getSize().x / 3.0f, this->gunRight.getSize().y / 2.0f},
            this->gunRight.getRotation(),
            WHITE);
    }
    else if (this->spriteAnimation.y == Left)
    {
        DrawTexturePro(
            this->gunLeft.getTexture(),
            {0, 0, this->gunLeft.getSize().x, this->gunLeft.getSize().y},
            {this->texture.getPosition().x + this->texture.getSize().x / 2.0f,
             this->texture.getPosition().y + this->texture.getSize().y / 2.0f,
             this->gunLeft.getSize().x,
             this->gunLeft.getSize().y},
            {this->gunLeft.getSize().x - this->gunLeft.getSize().x / 3.0f, this->gunLeft.getSize().y / 2.0f},
            this->gunLeft.getRotation(),
            WHITE);
    }
}

void Enemy::fall()
{
    velocity.y += gravity;
}

void Enemy::detectPlayer()
{
    Player &player = PlayerService::getInstance().getPlayer();
    if (this->health > 0)
    {
        bool spotted = false;
        Vector2 playerCenter = {player.getTexture().getPosition().x + player.getTexture().getSize().x / 2.0f, player.getTexture().getPosition().y + player.getTexture().getSize().y / 2.0f};
        Vector2 enemyCenter = {texture.getPosition().x + texture.getSize().x / 2.0f, texture.getPosition().y + texture.getSize().y / 2.0f};
        if (this->spriteAnimation.y == Left && this->texture.getPosition().x - player.getTexture().getPosition().x <= spottingRange &&
            this->texture.getPosition().x - player.getTexture().getPosition().x > 55 && this->texture.getPosition().y + this->texture.getSize().y >= player.getTexture().getPosition().y)
        {
            spotted = true;
            float gunRotationLeft = atan2(playerCenter.y - enemyCenter.y,
                                          enemyCenter.x - playerCenter.x);
            float target = -gunRotationLeft * 180 / M_PI;
            this->gunLeft.setRotation(std::min(this->gunLeft.getRotation() + aimSpeed, target));
        }
        else if (spriteAnimation.y == Right && player.getTexture().getPosition().x - this->texture.getPosition().x <= spottingRange &&
                 player.getTexture().getPosition().x - this->texture.getPosition().x > 55 && this->texture.getPosition().y + this->texture.getSize().y >= player.getTexture().getPosition().y)
        {
            spotted = true;
            float gunRotationRight = atan2(playerCenter.y - enemyCenter.y,
                                           playerCenter.x - enemyCenter.x);
            float target = gunRotationRight * 180 / M_PI;
            this->gunRight.setRotation(std::max(this->gunRight.getRotation() - aimSpeed, target));
        }

        /** Don't set it again if the detection continues */
        if (spotted && !this->playerSpotted)
        {
            AssetService::getInstance().playSound(ESound::PLAYER_SPOTTED);
            this->playerSpotted = true;
            velocity.x = 0.0f;
        }
        else if (!spotted)
        {
            this->playerSpotted = false;
            /** Slowly ease the gun back to default position */
            this->gunLeft.setRotation(std::max(this->gunLeft.getRotation() - aimSpeed / 2.0f, 0.0f));
            this->gunRight.setRotation(std::min(this->gunRight.getRotation() + aimSpeed / 2.0f, 0.0f));
        }
    }
}

void Enemy::shoot()
{
    Player &player = PlayerService::getInstance().getPlayer();
    /** Stop shooting if the player is dead (and falling out of the map) */
    if (player.getHealth() > 0 && playerSpotted && GetTime() - this->lastShot >= (1 / this->shotsPerSecond))
    {

        this->lastShot = GetTime();
        // Play shooting sound
        AssetService::getInstance().playSound(ESound::SHOOT);

        float offsetDistance = this->gunLeft.getSize().x - this->gunLeft.getSize().x / 3;
        Vector2 playerCenter = {player.getTexture().getPosition().x + player.getTexture().getSize().x / 2.0f, player.getTexture().getPosition().y + player.getTexture().getSize().y / 2.0f};
        Vector2 enemyCenter = {texture.getPosition().x + texture.getSize().x / 2.0f, texture.getPosition().y + texture.getSize().y / 2.0f};

        float angleShot = atan2(playerCenter.y - enemyCenter.y,
                                playerCenter.x - enemyCenter.x);

        float offsetX = cos(angleShot) * offsetDistance;
        float offsetY = sin(angleShot) * offsetDistance;
        Vector2 bulletStartLocation = {this->texture.getPosition().x + this->texture.getSize().x / 2.0f + offsetX,
                                       this->texture.getPosition().y + this->texture.getSize().y / 2.0f + offsetY};

        BulletService::getInstance().addEnemyBullet(bulletStartLocation, angleShot);
    }
}