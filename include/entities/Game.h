#ifndef GAME_H
#define GAME_H

#include "entities/Map.h"
#include "entities/Background.h"
#include "services/StateService.h"
#include "services/AudioService.h"
#include "services/MapService.h"
#include "services/InputService.h"
#include "services/GameService.h"
#include "services/CollectableService.h"
#include "services/EnemyService.h"
#include "services/PlayerService.h"
#include "services/BulletService.h"
#include "entities/Text.h"
#include <sstream>
#include <iostream>

class Game
{
public:
    Game()
    {
        GameService::getInstance().resetGame();

        TextureWrapper wrapper1 = TextureWrapper(AssetService::getInstance().getBackground(EBackground::GAME1), {GetScreenWidth() * 2.0f, (float)GetScreenHeight()}, {0, 0});
        wrapper1.setSourceRect({0, 0, wrapper1.getSize().x, wrapper1.getSize().y});
        TextureWrapper wrapper2 = TextureWrapper(AssetService::getInstance().getBackground(EBackground::GAME2), {864.0f, (float)GetScreenHeight()}, {wrapper1.getSize().x, 0.0});
        wrapper2.setSourceRect({0, 200, wrapper2.getSize().x, 200 + wrapper2.getSize().y});
        TextureWrapper wrapper3 = TextureWrapper(AssetService::getInstance().getBackground(EBackground::GAME3), {1728.0f, (float)GetScreenHeight()}, {wrapper1.getSize().x + wrapper2.getSize().x, 0.0});
        wrapper3.setSourceRect({64, 200, 64 + wrapper3.getSize().x, 200 + wrapper3.getSize().y});

        std::vector<TextureWrapper> wrappers;
        wrappers.push_back(wrapper1);
        wrappers.push_back(wrapper2);
        wrappers.push_back(wrapper3);
        this->background = Background(wrappers);
        this->map = Map();
        MapService::getInstance().setMap(this->map);

        Vector2 screenSize = StateService::getInstance().getScreenSize();
        Camera2D camera = {0};
        camera.offset = (Vector2){screenSize.x / 2.0f, screenSize.y / 2.0f}; // Set offset to center
        camera.target = (Vector2){screenSize.x / 2.0f, screenSize.y / 2.0f}; // Initially at the center of the world
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
        GameService::getInstance().setCamera(camera);
        BulletService::getInstance().initBullets();
        PlayerService::getInstance().initPlayer();
        this->crosshair = TextureWrapper(AssetService::getInstance().getSprite(ESprite::CROSSHAIR), {15, 15}, {0, 0}, {0, 0, 15, 15});

        CollectableService::getInstance().initCollectables();
        std::cout << "Initting" << std::endl;

        initHud();
        initPauseScreen();
        initGameOverScreen();
        EnemyService::getInstance().initEnemies();

        InputService::getInstance().setKeysToWatch({KEY_A, KEY_W, KEY_S, KEY_D, KEY_ENTER}, {MOUSE_BUTTON_LEFT});
        AudioService::getInstance().setMusic(EMusic::GAME);
        AudioService::getInstance().playMusic();
    }

    ~Game()
    {
    }

    void logic()
    {
        this->crosshair.setPosition(InputService::getInstance().getMousePos());

        if (GameService::getInstance().isPaused())
        {
            pausedLogic();
            return;
        }
        else if (GameService::getInstance().isGameOver())
        {
            gameOverLogic();
            return;
        }

        if (InputService::getInstance().isKeyPressed(KEY_ENTER))
        {
            GameService::getInstance().setPaused(true);
            return;
        }

        BulletService::getInstance().bulletLogic();
        CollectableService::getInstance().collectableLogic();
        EnemyService::getInstance().enemyLogic();

        auto &player = PlayerService::getInstance().getPlayer();
        player.logic();
        if (player.getTexture().getPosition().x > (StateService::getInstance().getScreenSize().x / 2.0f) &&
            player.getTexture().getPosition().x + (StateService::getInstance().getScreenSize().x / 2.0f) < background.getBackgroundSize().x)
        {
            GameService::getInstance().getCamera().offset = {(StateService::getInstance().getScreenSize().x / 2.0f) + ((StateService::getInstance().getScreenSize().x / 2.0f) - player.getTexture().getPosition().x), StateService::getInstance().getScreenSize().y / 2.0f};
        }
        if (player.isFinishReached())
        {
            StateService::getInstance().setScreen(EScreen::VICTORY);
        }
    }

    void draw()
    {
        BeginDrawing();
        BeginMode2D(GameService::getInstance().getCamera());

        this->background.draw();

        BulletService::getInstance().drawBullets();
        this->map.draw();
        CollectableService::getInstance().drawCollectables();
        EnemyService::getInstance().drawEnemies();
        PlayerService::getInstance().getPlayer().draw();

        EndMode2D();

        drawHud();
        if (GameService::getInstance().isPaused())
        {
            drawPaused();
        }
        else if (GameService::getInstance().isGameOver())
        {
            drawGameOver();
        }
        else
        {
            drawCrosshair();
        }
        EndDrawing();
    }

private:
    Background background;
    Map map;
    TextureWrapper crosshair;
    std::vector<Enemy> enemies;

    std::vector<Text> pauseScreenButtons;
    int hoveredPauseScreenButton = 0;

    Text gameOverText;
    std::vector<Text> gameOverScreenButtons;
    int hoveredGameOverScreenButton = 0;

    Text hudJellyText;
    TextureWrapper hudJellyTexture;

    void initHud()
    {
        hudJellyTexture = TextureWrapper(AssetService::getInstance().getSprite(ESprite::JELLY), {32, 32}, {500, 5});
        hudJellyText = Text("0/3", EFont::SANSATION, 30, 0, RED, {hudJellyTexture.getPosition().x + hudJellyTexture.getSize().x * 1.5f, hudJellyTexture.getPosition().y + 5});
    }

    void initPauseScreen()
    {
#if defined(PLATFORM_WEB)
        const int TOP_GAP = 100;
        const int BOTTOM_GAP = 100;
        const int AMNT_OF_BUTTONS = 2;
#else
        const int TOP_GAP = 100;
        const int BOTTOM_GAP = 50;
        const int AMNT_OF_BUTTONS = 4;
#endif

        const int TOTAL_SPACE = GetScreenHeight() - (TOP_GAP + BOTTOM_GAP);
        const int SPACE_PER_ITEM = TOTAL_SPACE / AMNT_OF_BUTTONS;

        for (int i = 0; i < AMNT_OF_BUTTONS; i++)
        {
            Text txt = Text("Continue", EFont::SANSATION, 30, 0, WHITE);
            pauseScreenButtons.push_back(txt);
        }
        pauseScreenButtons[0].setColor(RED);

#if defined(PLATFORM_WEB)
        pauseScreenButtons[1].setText("Quit to Main Menu");
#else
        pauseScreenButtons[1].setText("Save Game");
        pauseScreenButtons[2].setText("Quit to Main Menu");
        pauseScreenButtons[3].setText("Quit to Desktop");
#endif

        for (int i = 0; i < AMNT_OF_BUTTONS; i++)
        {
#if defined(PLATFORM_WEB)
            pauseScreenButtons[i].setPosition({(float)(GetScreenWidth() - pauseScreenButtons[i].getDimensions().x) / 2.0f, (float)TOP_GAP + SPACE_PER_ITEM * i + SPACE_PER_ITEM / 2.0f});

#else
            pauseScreenButtons[i].setPosition({(float)(GetScreenWidth() - pauseScreenButtons[i].getDimensions().x) / 2.0f, (float)TOP_GAP + SPACE_PER_ITEM * i});

#endif
        }
    }

    void initGameOverScreen()
    {
        this->gameOverText = Text("Game Over", EFont::SANSATION, 60, 0, WHITE);
        this->gameOverText.setPosition({(float)(GetScreenWidth() - gameOverText.getDimensions().x) / 2.0f, (float)(GetScreenHeight() - gameOverText.getDimensions().y) / 3.0f});

        const int TOP_POS = GetScreenHeight() / 1.8;
        const int X_GAP = 90;
        const int AMNT_OF_BUTTONS = 2;
        const int TOTAL_SPACE = GetScreenWidth() - (X_GAP + X_GAP);
        const int SPACE_PER_ITEM = TOTAL_SPACE / AMNT_OF_BUTTONS;
        for (int i = 0; i < AMNT_OF_BUTTONS; i++)
        {
            Text txt = Text("Play Again", EFont::SANSATION, 30, 0, BLACK);
            gameOverScreenButtons.push_back(txt);
        }
        gameOverScreenButtons[0].setColor(WHITE);
        gameOverScreenButtons[1].setText("Quit to Main Menu");
        for (int i = 0; i < AMNT_OF_BUTTONS; i++)
        {
            gameOverScreenButtons[i].setPosition({(float)X_GAP + SPACE_PER_ITEM * i, (float)TOP_POS});
        }
    }

    void pausedLogic()
    {
        if (InputService::getInstance().isKeyPressed(KEY_S) || InputService::getInstance().isKeyPressed(KEY_W))
        {
            pauseScreenButtons[hoveredPauseScreenButton].setColor(WHITE);
            /** Move up or down depending on the pressed button. +4 is used so that -1 becomes 3 (the last button) */
            hoveredPauseScreenButton = ((hoveredPauseScreenButton - (InputService::getInstance().isKeyPressed(KEY_S) ? -1 : 1)) + pauseScreenButtons.size()) % pauseScreenButtons.size();
            pauseScreenButtons[hoveredPauseScreenButton].setColor(RED);
        }

        if (InputService::getInstance().isKeyPressed(KEY_ENTER))
        {

            std::string selectedButton = pauseScreenButtons[hoveredPauseScreenButton].getText();

            if (selectedButton == "Continue")
            {
                GameService::getInstance().setPaused(false);
                AudioService::getInstance().playMusic();
            }
            else if (selectedButton == "Save Game")
            {
            }
            else if (selectedButton == "Quit to Main Menu")
                StateService::getInstance().setScreen(EScreen::MAIN);
            else if (selectedButton == "Quit to Desktop")
                StateService::getInstance().setScreen(EScreen::CLOSE);
        }
    }

    void gameOverLogic()
    {
        if (InputService::getInstance().isKeyPressed(KEY_D) || InputService::getInstance().isKeyPressed(KEY_A))
        {
            gameOverScreenButtons[hoveredGameOverScreenButton].setColor(BLACK);
            /** Move up or down depending on the pressed button. +4 is used so that -1 becomes 3 (the last button) */
            hoveredGameOverScreenButton = ((hoveredGameOverScreenButton - (InputService::getInstance().isKeyPressed(KEY_D) ? -1 : 1)) + gameOverScreenButtons.size()) % gameOverScreenButtons.size();
            gameOverScreenButtons[hoveredGameOverScreenButton].setColor(WHITE);
        }

        if (InputService::getInstance().isKeyPressed(KEY_ENTER))
        {
            std::string selectedButton = gameOverScreenButtons[hoveredGameOverScreenButton].getText();

            if (selectedButton == "Play Again")
            {
                StateService::getInstance().setScreen(EScreen::GAME);
            }
            else if (selectedButton == "Quit to Main Menu")
            {
                StateService::getInstance().setScreen(EScreen::MAIN);
            }
            GameService::getInstance().setGameOver(false);
        }
    }

    void drawPaused()
    {
        // 100, 100, 255, 60
        DrawRectangle(0, 0, StateService::getInstance().getScreenSize().x, StateService::getInstance().getScreenSize().y, {0, 0, 0, 200});
        if (pauseScreenButtons.size() > 0)
        {
            for (int i = 0; i < pauseScreenButtons.size(); i++)
            {
                pauseScreenButtons[i].draw();
            }
        }
    }

    void drawGameOver()
    {
        DrawRectangle(0, 0, StateService::getInstance().getScreenSize().x, StateService::getInstance().getScreenSize().y, {100, 0, 0, 200});

        gameOverText.draw();

        for (int i = 0; i < gameOverScreenButtons.size(); i++)
        {
            gameOverScreenButtons[i].draw();
        }
    }

    void drawCrosshair()
    {
        DrawTextureEx(
            this->crosshair.getTexture(),
            {InputService::getInstance().getMousePos().x - this->crosshair.getSize().x / 2.0f, InputService::getInstance().getMousePos().y - this->crosshair.getSize().y / 2.0f},
            0,
            1.2f,
            RED);
    }

    void drawHud()
    {
        drawHudHealth();
        drawHudBullets();
        drawHudJellies();
    }

    void drawHudBullets()
    {
        Vector2i pixel_pos = Vector2i(5, 40);
        Texture2D ammoSprite = AssetService::getInstance().getSprite(ESprite::HUD_AMMO);
        Vector2i display_pos;
        for (int i = 0; i < PlayerService::getInstance().getPlayer().getAmmo(); i++)
        {
            if (i <= 49)
            {
                display_pos = Vector2i(pixel_pos.x + ammoSprite.width * i, pixel_pos.y);
            }
            if (i > 49 && i <= 99)
            {
                display_pos = Vector2i(pixel_pos.x + ammoSprite.width * (i - (50)), pixel_pos.y + ammoSprite.height);
            }
            else if (i > 99 && i <= 149)
            {
                display_pos = Vector2i(pixel_pos.x + ammoSprite.width * (i - (100)), pixel_pos.y + ammoSprite.height * 2);
            }
            else if (i > 149 && i <= 199)
            {
                display_pos = Vector2i(pixel_pos.x + ammoSprite.width * (i - (150)), pixel_pos.y + ammoSprite.height * 3);
            }
            else if (i > 199 && i <= 249)
            {
                display_pos = Vector2i(pixel_pos.x + ammoSprite.width * (i - (200)), pixel_pos.y + ammoSprite.height * 4);
            }
            DrawTexture(ammoSprite, display_pos.x, display_pos.y, WHITE);
        }
    }

    void drawHudHealth()
    {
        Vector2i pixel_pos = Vector2i(5, 5);
        Texture2D noHealthSprite = AssetService::getInstance().getSprite(ESprite::HUD_HEART_EMPTY);
        Texture2D healthSprite = AssetService::getInstance().getSprite(ESprite::HUD_HEART);
        // sVector2f coord_pos = GetWindow().mapPixelToCoords(pixel_pos);
        for (int i = 0; i < PlayerService::getInstance().getPlayer().getMaxHealth(); i++)
        {
            Vector2i pos = Vector2i(pixel_pos.x + noHealthSprite.width * i, pixel_pos.y);
            // noHealthSprite[i].setPosition(coord_pos.x + noHealthTexture.getSize().x * i, coord_pos.y);
            DrawTexture(noHealthSprite, pos.x, pos.y, WHITE);
        }
        for (int i = 0; i < PlayerService::getInstance().getPlayer().getHealth(); i++)
        {
            // healthSprite[i].setPosition(coord_pos.x + healthTexture.getSize().x * i, coord_pos.y);
            // DrawTexture(ammoSprite, display_pos.x, display_pos.y, WHITE);
            Vector2i pos = Vector2i(pixel_pos.x + healthSprite.width * i, pixel_pos.y);
            // noHealthSprite[i].setPosition(coord_pos.x + noHealthTexture.getSize().x * i, coord_pos.y);
            DrawTexture(healthSprite, pos.x, pos.y, WHITE);
        }
    }

    void drawHudJellies()
    {
        std::stringstream stream;
        stream.clear();
        stream << CollectableService::getInstance().getAmountOfJelliesFreed();
        stream << "/";
        stream << CollectableService::getInstance().getMaxAmountOfJellies();
        hudJellyText.setText(stream.str());

        DrawTexture(hudJellyTexture.getTexture(), hudJellyTexture.getPosition().x, hudJellyTexture.getPosition().y, WHITE);
        hudJellyText.draw();
    }
};

#endif