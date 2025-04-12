#include <raylib.h>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

random_device rd;
mt19937 gen(rd());
vector<int> Numbers = {10, -10};
uniform_int_distribution<> dist(0, Numbers.size() -1);
int choice = dist(gen);
uniform_int_distribution<> dist1(0, Numbers.size() -1);
int choice1 = dist1(gen);

class Ball{
    public:
        float x, y;
        int speed_x, speed_y;
        int radius;
        int ScorePlayer1;
        int ScorePlayer2;
    void Draw() {
        DrawCircle(x, y, radius, WHITE);
    }
    void Update() {
        x += speed_x;
        y += speed_y;
        if(x + radius >= GetScreenWidth()) {
            ScorePlayer1 += 1;
            ClearBackground(BLACK);
            DrawCircle(1500/2, 980/2, radius, WHITE);
            x = 1500/2;
            y = 980/2;
            speed_x = Numbers[choice];
            speed_y = Numbers[choice1];
        }
        if(x - radius <= 0) {
            ScorePlayer2 += 1;
            ClearBackground(BLACK);
            DrawCircle(1500/2, 980/2, radius, WHITE);
            x = 1500/2;
            y = 980/2;
            speed_x = Numbers[choice];
            speed_y = Numbers[choice1];
        }
        if(y + radius >= GetScreenHeight() || y - radius <= 2) {
            speed_y *= -1;
        }
    }
};

Ball ball;

int main() {
    InitAudioDevice();
    Sound bounce = LoadSound("resources/bounce.wav");
    float RectangleXPlayer1 = 40;
    float RectangleYPlayer1 = 400;
    float RectangleWidthPlayer1 = 20;
    float RectangleHeightPlayer1 = 150;
    float RectangleXPlayer2 = 1450;
    float RectangleYPlayer2 = 400;
    float RectangleWidthPlayer2 = 20;
    float RectangleHeightPlayer2 = 150;
    Color bg = {170, 240, 209, 255};
    Color bg1 = {130, 250, 189, 255};
    Color Paddle = {3, 192, 60, 255};
    InitWindow(1500, 980, "Skibidi Sigma Rizzy Ultimate Omega Pong for the GOATED");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = 1500/2;
    ball.y = 980/2;
    ball.speed_x = Numbers[choice];
    ball.speed_y = Numbers[choice1];

    // Game Loop
    while(WindowShouldClose() == false) {
        // Event Handling
        if(IsKeyDown(KEY_S)) {
            RectangleYPlayer1 += 10;
            if(RectangleYPlayer1 == 790) {
                RectangleYPlayer1 -= 10;
            }
        }
        if(IsKeyDown(KEY_W)) {
            RectangleYPlayer1 -= 10;
            if(RectangleYPlayer1 == 40) {
                RectangleYPlayer1 += 10;
            }
        }
        if(IsKeyDown(KEY_DOWN)) {
            RectangleYPlayer2 += 10;
            if(RectangleYPlayer2 == 790) {
                RectangleYPlayer2 -= 10;
            }
        }
        if(IsKeyDown(KEY_UP)) {
            RectangleYPlayer2 -= 10;
            if(RectangleYPlayer2 == 40) {
                RectangleYPlayer2 += 10;
            }
        }
        // Updating Positions
        ball.Update();
        // Check for collisions
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{RectangleXPlayer1, RectangleYPlayer1, RectangleWidthPlayer1, RectangleHeightPlayer1})) {
            PlaySound(bounce);
            ball.speed_x *= -1;
            // explanation: (ball.y -)RectangleYPlayer1 + RextangleHeightPlayer1 / 2); < this line finds the middle of the paddle by dividing Rectangle Height by 2 which is the height of the paddle so it finds the middle of that, then it finds the y coordinates by adding RectangleYPlayer1 which is the position of the top of the paddle and then it finds how far the ball is from the center by subtracting ball.y fromt he original y cooridinate then divide that number by 2 to get a smaller number
            float hitPosMiddleP1 = (ball.y - (RectangleYPlayer1 + RectangleHeightPlayer1 / 2)) / (RectangleHeightPlayer1 / 2);
            cout << hitPosMiddleP1 << endl;
            // multiply the speed by the hitposition to get an (somewhat) accurate hit direction
            // ball.speed_y = hitPosMiddleP1 * 10;
            if(hitPosMiddleP1 > 0.5 || hitPosMiddleP1 < -0.5) {
                cout << "if 1\n";
                ball.speed_y = hitPosMiddleP1 * 10;
            }
            else if(hitPosMiddleP1 < 0.5 || hitPosMiddleP1 > -0.5) {
                cout << "if 2\n";
                cout << "old: " << hitPosMiddleP1 << endl;
                if(hitPosMiddleP1 < -0.3) {
                    hitPosMiddleP1 += 0.8;
                }
                else {
                    hitPosMiddleP1 += 0.5;
                }
                cout << "new: " << hitPosMiddleP1 << endl;
                ball.speed_y = hitPosMiddleP1 * 10;
            }
        }
        else if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{RectangleXPlayer2, RectangleYPlayer2, RectangleWidthPlayer2, RectangleHeightPlayer2})) {
            PlaySound(bounce);
            ball.speed_x *= -1;
            // explanation: (ball.y -)RectangleYPlayer1 + RextangleHeightPlayer1 / 2); < this line finds the middle of the paddle by dividing Rectangle Height by 2 which is the height of the paddle so it finds the middle of that, then it finds the y coordinates by adding RectangleYPlayer1 which is the position of the top of the paddle and then it finds how far the ball is from the center by subtracting ball.y fromt he original y cooridinate then divide that number by 2 to get a smaller number
            float hitPosMiddleP2 = (ball.y - (RectangleYPlayer2 + RectangleHeightPlayer2 / 2)) / (RectangleHeightPlayer2 / 2);
            cout << hitPosMiddleP2 << endl;
            // multiply the speed by the hitposition to get an (somewhat) accurate hit direction
            // ball.speed_y = hitPosMiddleP2 * 10;
            if(hitPosMiddleP2 > 0.5 || hitPosMiddleP2 < -0.5) {
                cout << "if 1\n";
                ball.speed_y = hitPosMiddleP2 * 10;
            }
            else if(hitPosMiddleP2 < 0.5 || hitPosMiddleP2 > -0.5) {
                cout << "if 2\n";
                cout << "old: " << hitPosMiddleP2 << endl;
                if(hitPosMiddleP2 < -0.3) {
                    hitPosMiddleP2 += 0.8;
                }
                else {
                    hitPosMiddleP2 += 0.5;
                }
                cout << "new: " << hitPosMiddleP2 << endl;
                ball.speed_y = hitPosMiddleP2 * 10;
            }
        }
        // Drawing
        BeginDrawing();
        ClearBackground(bg);
        DrawRectangle(1500/2, 0, 1500/2, 980, bg1);
        DrawRectangle(RectangleXPlayer1, RectangleYPlayer1, RectangleWidthPlayer1, RectangleHeightPlayer1, Paddle);
        DrawRectangle(RectangleXPlayer2, RectangleYPlayer2, RectangleWidthPlayer2, RectangleHeightPlayer2, Paddle);
        DrawRectangle(1500/2, 30, 2, 920, GREEN);
        DrawText(TextFormat("%03i", ball.ScorePlayer1), 40, 40, 80, BLUE);
        DrawText(TextFormat("%03i", ball.ScorePlayer2), 1300, 40, 80, BLUE);
        ball.Draw();
        EndDrawing();
    }
    CloseWindow();
    CloseAudioDevice();
    UnloadSound(bounce);
    return 0;
}