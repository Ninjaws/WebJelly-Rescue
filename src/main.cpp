#include "raylib.h"
#include <cstdio> // For printf
#include <iostream>

int main()
{
    // SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitAudioDevice();
    SetTargetFPS(60);

    InitWindow(640, 544, "Jelly Rescue");

    // Main game loop
    // Texture2D background = LoadTexture("/app/dist/Data/Textures/TitleScreenBackground.png");

    Font font1 = LoadFontEx("./dist/Data/Fonts/Reckoner_Bold.ttf", 100,0,0);
    SetTextureFilter(font1.texture, TEXTURE_FILTER_BILINEAR);
    Font font2 = LoadFont("./dist/Data/Fonts/Sansation.ttf");
    SetTextureFilter(font2.texture, TEXTURE_FILTER_BILINEAR);

    Music bg = LoadMusicStream("./dist/Data/Audio/Music/Crash_WarpRoomTheme.ogg");
    bg.looping = true;
    SetMasterVolume(1.0f);
    SetMusicVolume(bg,1.0f);

    PlayMusicStream(bg);

    Vector2 dimTitle = MeasureTextEx(font1, "Jelly rescue", 100,0);
    Vector2 dimSub = MeasureTextEx(font2, "Press Enter to continue", 30,0);
    Vector2 dimHead = MeasureTextEx(font2, "Made by Ian Vink", 20,0);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(bg);
        BeginDrawing();
        ClearBackground(BLACK);        

        DrawTextEx(font2,"Made by Ian Vink", {((float)GetScreenWidth()-dimHead.x)/1.2f, (float(GetScreenHeight()-dimHead.y)/6.0f)}, 20, 0, WHITE);
        DrawTextEx(font1, "Jelly rescue", {((float)GetScreenWidth()-dimTitle.x)/2.0f, (float(GetScreenHeight()-dimTitle.y)/2.0f)}, 100,0, {255,25,25,255});
        DrawTextEx(font2,"Press Enter to continue", {((float)GetScreenWidth()-dimSub.x)/2.0f, (float(GetScreenHeight()-dimSub.y)/1.5f)}, 30, 0, WHITE);
        EndDrawing();
    }

    // UnloadTexture(background);
    CloseWindow();
    UnloadMusicStream(bg);
    CloseAudioDevice();
    return 0;
}

// class TitleScreen {
//     public:
// Image background;
// }


// game.SetMainMusic("Data/Audio/Music/Crash_WarpRoomTheme.ogg", 50);
// 	game.SetTitleFont("Data/Fonts/Reckoner_Bold.ttf");
// 	game.SetTitleText("Jelly rescue", 100, sf::Color::Red);
// 	game.SetUnderTitleFont("Data/Fonts/Sansation.ttf");
// 	game.SetUnderTitleText(30, sf::Color::White);
// 	game.SetNameText(20, sf::Color::White);



// void TitleScreen::DrawTitleScreenBackground()
// {
// 	GetWindow().draw(titleScreenBackground);
// }

// void TitleScreen::SetTitleFont(std::string fontlocation)
// {
// 	titleFont.loadFromFile(fontlocation);
// }
// void TitleScreen::SetTitleText(std::string titletext, float textsize, sf::Color color)
// {
// 	titleText.setFont(titleFont);
// 	titleText.setPosition(GetWindow().getSize().x / 7, GetWindow().getSize().y / 3);
// 	titleText.setCharacterSize(textsize);
// 	titleText.setColor(color);
// 	titleText.setString(titletext);
// }
// void TitleScreen::SetUnderTitleFont(std::string fontlocation)
// {
// 	underTitleFont.loadFromFile(fontlocation);
// }
// void TitleScreen::SetUnderTitleText(float textsize, sf::Color color)
// {
// 	underTitleText.setFont(underTitleFont);
// 	underTitleText.setPosition(GetWindow().getSize().x / 4, GetWindow().getSize().y / 3 * 2);
// 	underTitleText.setCharacterSize(textsize);
// 	underTitleText.setColor(color);
// 	underTitleText.setString("Press Enter to continue");
// }
// void TitleScreen::SetNameText(float textsize, sf::Color color)
// {
// 	nameText.setFont(underTitleFont);
// 	nameText.setPosition(GetWindow().getSize().x / 1.5, GetWindow().getSize().y / 8);
// 	nameText.setCharacterSize(textsize);
// 	nameText.setColor(color);
// 	nameText.setString("Made by Ian Vink");
// }
// void TitleScreen::SetTitleScreenBackground(std::string texturelocation)
// {
// 	sf::Vector2f screenDimensions;
// 	screenDimensions.x = GetWindow().getSize().x;
// 	screenDimensions.y = GetWindow().getSize().y;
// 	titleScreenTexture.loadFromFile(texturelocation);
// 	titleScreenBackground.setTexture(&titleScreenTexture);
// 	titleScreenBackground.setSize(screenDimensions);
// 	std::cout << "Titlescreen background loaded" << std::endl;
// }
