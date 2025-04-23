#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>
using namespace std;

float cellSize = 30;
float cellAmount = 25;
bool running = true;
double lastUpdateTime = 0;

bool ItemInDeque(Vector2 item, deque<Vector2> target) {
    for(unsigned int i = 0;i<target.size();i++) {
        if(Vector2Equals(item, target[i])) {
            return true;
        }
    }
    return false;
}

bool eventTriggered(double interval) {
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Snake {
    public:
        Texture2D textureSnake;
        // deque<Vector2> body = {Vector2{6, 9}, Vector2{5,9}, Vector2{4,9}};
        deque<Vector2> body = {Vector2{6, 9}};
        Vector2 direction = {1, 0};
        Snake() {
            Image imageSnake = LoadImage("resources/android.png");
            textureSnake = LoadTextureFromImage(imageSnake);
            UnloadImage(imageSnake);
        }
        ~Snake() {
            UnloadTexture(textureSnake);
        }
        void Draw() {
            // unsigned int to match compiler expectation it is useless tho
            for(unsigned i=0; i<body.size();i++) {
                float x = body[i].x;
                float y = body[i].y;
                // the youtube guy told me to put this and idk what it means
                Rectangle segment = Rectangle{x*cellSize, y*cellSize, cellSize, cellSize};
                DrawRectangleRounded(segment, 0.5, 6, GREEN);
            }
        }
        void Update() {
            body.pop_back();
            body.push_front(Vector2Add(body[0], direction));
        }
}; 

class Food {
    public:
        Vector2 position;
        Texture2D textureFood;
        
        Food() {
            Image imageFood = LoadImage("resources/apple.png");
            textureFood = LoadTextureFromImage(imageFood);
            UnloadImage(imageFood);
            position = GenerateRandomPos();
        }
        ~Food() {
            UnloadTexture(textureFood);
        }

        void Draw() {
            DrawTexture(textureFood, position.x * cellSize, position.y * cellSize, WHITE);
        }

        Vector2 GenerateRandomPos() {
            float x = GetRandomValue(0, cellAmount - 1);
            float y = GetRandomValue(0, cellAmount - 1);
            return Vector2{x, y}; 
        }
};

class Game {
    public:
        Food food;
        Snake snake;
        int Score = 0;

        void Draw() {
            food.Draw();
            snake.Draw();
            DrawText(TextFormat("%03i", Score), 20, 20, 80, BLUE);
        }
        void Update() {
            if(running) {
                snake.Update();
                CheckCollisionWithFood();
                CheckCollisionsWithEdges();
                CheckCollisionWithTail();
            }
        }
        void CheckCollisionWithFood() {
            if(Vector2Equals(snake.body[0], food.position)) {
                snake.body.push_front(Vector2Add(snake.body[0], snake.direction));
                Score += 1;
                food.position = food.GenerateRandomPos();
            }
        }
        void CheckCollisionsWithEdges() {
            if(snake.body[0].x == cellAmount || snake.body[0].x == -1) {
                GameOver();
            }
            if(snake.body[0].y == cellAmount || snake.body[0].y == -1) {
                GameOver();
            }
        }
        void CheckCollisionWithTail() {
            deque<Vector2> BodyNoHead = snake.body;
            BodyNoHead.pop_front();
            if(ItemInDeque(snake.body[0], BodyNoHead)) {
                GameOver();
            }
        }
        void GameOver() {
            snake.body = {Vector2{6, 9}};
            Score = 0;
            running = false;
        }
};

int main() {
    Color magicmint = {170,240,209,255};
    InitWindow(cellSize*cellAmount, cellSize*cellAmount, "snaker");
    SetTargetFPS(60);

    Game game;

    while(WindowShouldClose() == false) {
        // draw
        BeginDrawing();

        if(IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {
            game.snake.direction = {0, -1};
            running = true;
        }

        if(IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {
            game.snake.direction = {0, 1};
            running = true;
        }

        if(IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {
            game.snake.direction = {-1, 0};
            running = true;
        }

        if(IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1 ) {
            game.snake.direction = {1, 0};
            running = true;
        }

        if(eventTriggered(0.2)) {
            game.Update();
        }

        ClearBackground(magicmint); 
        game.Draw();
        EndDrawing();
    }
    CloseWindow();
    CloseAudioDevice();
    return 0;
}