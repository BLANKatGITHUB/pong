#include<iostream>
#include<raylib.h>

using namespace std;

Color DarkSlateGrey = Color {47,79,79,255};
Color Teal = Color{0,128,128,255};

int score1=0;
int score2=0;

class Ball{
    public: float x,y,radius;
    int speedx,speedy;
    int values[2]={1,-1};

    void draw(){
        DrawCircle(x,y,radius,RED);
    }

    void update(){
        x+=speedx;
        y+=speedy;

        if(y+20 >= GetScreenHeight() || y-20 <=0){
            speedy *= -1;
        }

        if(x+20 >= GetScreenWidth() ){
            score1 += 1;
            speedx *= values[GetRandomValue(0,1)];
            speedy *= values[GetRandomValue(0,1)];
            x=GetScreenWidth()/2;
            y=GetScreenHeight()/2;
        }

        if( x-20 <= 0){
            score2 += 1;
            speedx *= values[GetRandomValue(0,1)];
            speedy *= values[GetRandomValue(0,1)];
            x=GetScreenWidth()/2;
            y=GetScreenHeight()/2;
        }

        
    }
};

class Paddle{
    protected:
    void limiter(){
        if(y >= GetScreenHeight()- height)
        y = GetScreenHeight() - height;

        if(y <= 0)
        y = 0;
    }
    public: float x,y,width,height;
    int speed;

    void draw(){
        DrawRectangle(x,y,width,height,BLUE);
    }

    void update(){
        if(IsKeyDown(KEY_UP)){
            y -= speed;
        }

        if(IsKeyDown(KEY_DOWN)){
            y += speed;
        }
        limiter();
    
    }

};

class AutoPaddle : public Paddle{
    public:
    void update(int bally){
        if(y + height/2 > bally)
        y -= speed;

        else if(y + height/2 < bally)
        y += speed;
        limiter();
        
    }

};

int main()
{   
    Ball ball;
    Paddle paddle1;
    AutoPaddle paddle2;


    // Print a message to indicate the start of the game
    cout << "Starting the new game" << endl;

    // Defining window size
    const int scr_width = 1200, scr_height = 700;

    // Opening window
    InitWindow(scr_width, scr_height, "Pong");

    // Setting target frames per second
    SetTargetFPS(60);

    //Defining ball values
    ball.speedx=6;
    ball.speedy=6;
    ball.x=scr_width/2;
    ball.y=scr_height/2;
    ball.radius=20;
    ball.draw();

    paddle2.x= scr_width - 30;
    paddle2.y=scr_height/2 - 60;
    paddle2.height=120;
    paddle2.width=20;
    paddle2.speed=7;
    paddle2.draw();

    paddle1.x=10;
    paddle1.y=scr_height/2 - 60;
    paddle1.height=120;
    paddle1.width=20;
    paddle1.speed=6;
    paddle1.draw();

    while (WindowShouldClose() == false)
    {   
        ClearBackground(DarkSlateGrey);
        // Beginning of Drawing
        BeginDrawing();

        // Draws center line
        DrawLine(scr_width / 2, 0, scr_width / 2, scr_height, GRAY);
        DrawCircle(scr_width/2,scr_height/2,100,Teal);

         ball.update();
         paddle1.update();
         paddle2.update(ball.y);

         if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{paddle1.x,paddle1.y,paddle1.width,paddle1.height}))
            ball.speedx *= -1;

         if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{paddle2.x,paddle2.y,paddle2.width,paddle2.height}))
            ball.speedx *= -1;

        ball.draw();
        paddle1.draw();
        paddle2.draw();

        DrawText(TextFormat("%d",score1),50,10,50,GREEN);
        DrawText(TextFormat("%d",score2),1100,10,50,GREEN);

        // End of Drawing
        EndDrawing();
    }

    // Closing window
    CloseWindow();
    return 0;
}

