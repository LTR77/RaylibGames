#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <deque>
#include <chrono>
#include <thread>

const int CellSize = 40;
const int CellAmount = 30;

class Playership {
    public:
        int position_x = 1200/2;
        int position_y = 1000;
        Texture2D textureShip;

        Playership() {
            Image imagePlayer = LoadImage("resources/ship.png");
            textureShip = LoadTextureFromImage(imagePlayer);
            UnloadImage(imagePlayer);
        }

        ~Playership() {
            UnloadTexture(textureShip);
        }

        void Draw() {
            DrawTexture(textureShip, position_x, position_y, WHITE);
        }
};

class Asteroid {
    public:
        Texture2D textureAsteroid;
        std::deque<Vector2> Positions;
        float speed = 0.3f;

        Asteroid() {
            Image imageAsteroid = LoadImage("resources/asteroid.png");
            textureAsteroid = LoadTextureFromImage(imageAsteroid);
            UnloadImage(imageAsteroid);

            for(int i=0;i<7;i++) {
                Positions.push_back({(float)GetRandomValue(0, CellAmount -1), (float)GetRandomValue(-10, -5)});
            }
        }
        ~Asteroid() {
            UnloadTexture(textureAsteroid);
        }

        void DrawAsteroids() {
            for(const auto& pos : Positions) {
                DrawTexture(textureAsteroid, (int)pos.x * CellSize, (int)pos.y * CellSize, WHITE);
            }
        }
        
        void UpdateAsteroidPos() {
            for(auto& pos : Positions) {
                pos.y += speed;
            }
        }
};

class Game {
    public:
        Playership ship;
        Asteroid asteroid;

        void Draw() {
            ship.Draw();
            asteroid.DrawAsteroids();
        }
        void Update() {
            asteroid.UpdateAsteroidPos();
        }
};

int main() {
    SetTargetFPS(60);
    InitWindow(CellSize*CellAmount, CellSize*CellAmount, "game i couldnt name");

    Game game;

    while(WindowShouldClose() == false) {

        // inputs
        if(IsKeyDown(KEY_LEFT)) {
            game.ship.position_x -= 10;
        }
        if(IsKeyDown(KEY_RIGHT)) {
            game.ship.position_x += 10;
        }

        // checks
        if(game.ship.position_x <= 20) {
            game.ship.position_x += 10;
        }
        if(game.ship.position_x >= 1090) {
            game.ship.position_x -= 10;
        }

        // Update Positions
        game.Update();

        // draw
        BeginDrawing();
        ClearBackground(BLACK);
        game.Draw();
        EndDrawing();

    }
    CloseWindow();
    return 0;
}