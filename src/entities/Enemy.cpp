#include "entities/Enemy.h"
#include "services/PlayerService.h"
#include "services/MapService.h"
#include "services/BulletService.h"

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
    // Vector2i leftTop(Vector2i((int)left / tileSize, (int)(top + 5) / tileSize));
    // Vector2i leftBottom(Vector2i((int)left / tileSize, (int)(bottom - 5) / tileSize));
    Vector2i leftCenter = Vector2i((int)left / tileSize, (int)(bottom - texture.getSize().y / 2.0) / tileSize);
    // Vector2i rightTop(Vector2i((int)right / tileSize, (int)(top + 5) / tileSize));
    // Vector2i rightBottom(Vector2i((int)right / tileSize, (int)(bottom - 5) / tileSize));
    Vector2i rightCenter = Vector2i((int)right / tileSize, (int)(bottom - texture.getSize().y / 2.0) / tileSize);

    Vector2i bottomLeft(Vector2i((int)(left + 5) / tileSize, (int)bottom / tileSize));   // +5 to separate bottom from side
    Vector2i bottomRight(Vector2i((int)(right - 5) / tileSize, (int)bottom / tileSize)); // -5 to separate bottom from side

    std::vector<Vector2i> corners;

    corners.push_back(leftCenter);
    corners.push_back(rightCenter);
    // corners.push_back(leftBottom);
    // corners.push_back(rightTop);
    // corners.push_back(rightBottom);

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
        // sourceRect.x = std::fmod(sourceRect.x, 3 * this->texture.getSize().x);
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
    // playerSpotted = false;
    Player &player = PlayerService::getInstance().getPlayer();
    if (this->health > 0)
    {
        bool spotted = false;
        if (this->spriteAnimation.y == Left && this->texture.getPosition().x - player.getTexture().getPosition().x <= spottingRange &&
            this->texture.getPosition().x - player.getTexture().getPosition().x > 55 && this->texture.getPosition().y + this->texture.getSize().y >= player.getTexture().getPosition().y)
        {
            spotted = true;
        }
        else if (spriteAnimation.y == Right && player.getTexture().getPosition().x - this->texture.getPosition().x <= spottingRange &&
                 player.getTexture().getPosition().x - this->texture.getPosition().x > 55 && this->texture.getPosition().y + this->texture.getSize().y >= player.getTexture().getPosition().y)
        {
            spotted = true;
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

        if ((player.getTexture().getPosition().x > this->texture.getPosition().x + this->gunLeft.getSize().x && spriteAnimation.y == Right) ||
            (player.getTexture().getPosition().x + (this->gunLeft.getSize().x / 2) < this->texture.getPosition().x && spriteAnimation.y == Left))
        {

            float angleShot = atan2(player.getTexture().getPosition().y - (this->texture.getPosition().y + this->texture.getSize().y / 2.0),
                                    player.getTexture().getPosition().x - (this->texture.getPosition().x + this->texture.getSize().x / 2.0));

            /** Making the bullet originate from the gun's mouth */
            float offsetDistance = this->gunLeft.getSize().x - this->gunLeft.getSize().x / 3;
            float offsetX = cos(angleShot) * offsetDistance;
            float offsetY = sin(angleShot) * offsetDistance;
            Vector2 bulletStartLocation = {this->texture.getPosition().x + this->texture.getSize().x / 2.0f + offsetX,
                                           this->texture.getPosition().y + this->texture.getSize().y / 2.0f + offsetY};

            BulletService::getInstance().addEnemyBullet(bulletStartLocation, angleShot);
        }
    }
}