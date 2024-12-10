#ifndef GAME_H
#define GAME_H

#include "entities/Map.h"
#include "entities/Background.h"
#include "services/StateService.h"
#include "services/AudioService.h"

class Game
{
public:
    Game()
    {
        TextureWrapper wrapper1 = TextureWrapper(AssetService::getInstance().getBackground(EBackground::GAME1), {GetScreenWidth()*2.0f,(float)GetScreenHeight()}, {0,0});
        wrapper1.setSourceRect({0,0,wrapper1.getSize().x, wrapper1.getSize().y});
        TextureWrapper wrapper2 = TextureWrapper(AssetService::getInstance().getBackground(EBackground::GAME2), {864.0f,(float)GetScreenHeight()}, {wrapper1.getSize().x,0.0});
        wrapper2.setSourceRect({0,200,wrapper2.getSize().x, 200+wrapper2.getSize().y});
        TextureWrapper wrapper3 = TextureWrapper(AssetService::getInstance().getBackground(EBackground::GAME3), {1792.0f,(float)GetScreenHeight()}, {wrapper1.getSize().x+wrapper2.getSize().x,0.0});
        wrapper3.setSourceRect({64,200,64+wrapper3.getSize().x, 200+wrapper3.getSize().y});

        std::vector<TextureWrapper> wrappers;
        wrappers.push_back(wrapper1);
        wrappers.push_back(wrapper2);
        wrappers.push_back(wrapper3);
        this->background = Background(wrappers);
        this->map = Map();

        Vector2 screenSize = StateService::getInstance().getScreenSize();
        Camera2D camera = {0};
        camera.offset = (Vector2){screenSize.x / 2.0f, screenSize.y / 2.0f}; // Set offset to center
        camera.target = (Vector2){screenSize.x / 2.0f, screenSize.y / 2.0f}; // Initially at the center of the world
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
        this->camera = camera;

        AudioService::getInstance().setMusic(EMusic::GAME);
        AudioService::getInstance().playMusic();
    }
    ~Game()
    {
    }

    void logic()
    {
        this->camera.offset.x -= 1.5;
    }

    void draw()
    {
        BeginDrawing();
        BeginMode2D(this->camera);

        this->background.draw();
        this->map.draw();

        EndMode2D();
        EndDrawing();
    }

private:
    Camera2D camera;
    Background background;
    Map map;
    // Player player
    // std::vector<Enemy> enemies
    // std::vector<Create> crates
    // std::vector<PBullet> playerBullets
    // std::vector<EBullet> enemyBullets
    // std::vector<Jelly> jellies
    // std::vector<Ammo> ammo
    // std::vector<Healthpack> healthpacks
    // Powerup powerup
};

#endif