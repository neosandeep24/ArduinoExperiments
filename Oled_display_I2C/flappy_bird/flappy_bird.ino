#include <avr/pgmspace.h>
#include "U8glib.h"

//--------------------------------------------------
// OLED
//--------------------------------------------------
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);
// If using SSD1306 instead:
// U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;

//--------------------------------------------------
// Input
//--------------------------------------------------
const int BUTTON_PIN = 2;

//--------------------------------------------------
// Physics
//--------------------------------------------------
const int SCALE_FACTOR = 10;

const int GRAVITY = 5;
const int JUMP_STRENGTH = -25;

const int PIPE_WIDTH = 15 * SCALE_FACTOR;
const int PIPE_GAP = 30 * SCALE_FACTOR;
const int PIPE_SPEED = 20;
const int PIPE_SPACING = 65 * SCALE_FACTOR;

//--------------------------------------------------
// Bird
//--------------------------------------------------
const int BIRD_WIDTH_PX = 10;
const int BIRD_HEIGHT_PX = 8;

//--------------------------------------------------
// Game Variables
//--------------------------------------------------
int birdY;
int velocity = 0;

bool gameOver = false;

int score = 0;

unsigned long frameCounter = 0;
unsigned long gameOverTime = 0;

//--------------------------------------------------
// Game State
//--------------------------------------------------
enum GameState
{
    STARTSCREEN,
    HIGHSCORE,
    PLAYING
};

GameState gameState = STARTSCREEN;

//--------------------------------------------------
// Pipes
//--------------------------------------------------
struct Pipe
{
    int x;
    int height;
};

const int MAX_PIPES = 3;

Pipe pipes[MAX_PIPES];

//--------------------------------------------------
// Highscores
//--------------------------------------------------
long highscores[5] = {0};

int newHighscoreIndex = -1;

unsigned long highscoreTime = 0;

bool showBlink = true;

unsigned long lastBlinkTime = 0;

//--------------------------------------------------
// FPS
//--------------------------------------------------
const int FRAME_TIME = 40;

unsigned long lastFrameTime = 0;

//--------------------------------------------------
// Bird Bitmaps
//--------------------------------------------------

// bird frame 1 (10x8)

const uint8_t PROGMEM epd_bitmap_bird1[] =
{
0x0e,0x00,
0x15,0x00,
0x60,0x80,
0x81,0x80,
0xfc,0xc0,
0xfb,0x80,
0x71,0x00,
0x1e,0x00
};

// bird frame 2

const uint8_t PROGMEM epd_bitmap_bird2[] =
{
0x0e,0x00,
0x15,0x00,
0x70,0x80,
0xf9,0x80,
0xfc,0xc0,
0x83,0x80,
0x71,0x00,
0x1e,0x00
};

const uint8_t* epd_bitmap_allArray[] =
{
    epd_bitmap_bird1,
    epd_bitmap_bird2
};

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------

bool anyKeyPressed();

void resetGame();

int generatePipeHeight();

void movePipes();

int findFurthestPipe();

void checkCollision();

void drawGame();

void drawBird();

void drawPipes();

void drawScore();

void renderStartScreen();

void displayGameOver();

void renderHighscoreScreen();

void saveHighscores(int newScore);

//--------------------------------------------------
// Setup
//--------------------------------------------------

void setup()
{
    Serial.begin(9600);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    randomSeed(analogRead(0));

    u8g.setFont(u8g_font_6x10);

    gameState = STARTSCREEN;
}

//--------------------------------------------------
// Main Loop
//--------------------------------------------------

void loop()
{
    unsigned long currentTime = millis();

    if (currentTime - lastFrameTime < FRAME_TIME)
        return;

    lastFrameTime = currentTime;

    frameCounter++;

    switch (gameState)
    {
        //--------------------------------------------------
        // Start Screen
        //--------------------------------------------------
        case STARTSCREEN:

            u8g.firstPage();
            do
            {
                renderStartScreen();
            }
            while (u8g.nextPage());

            if (anyKeyPressed())
            {
                resetGame();
                gameState = PLAYING;
            }

        break;

        //--------------------------------------------------
        // Playing
        //--------------------------------------------------
        case PLAYING:

            if (gameOver)
            {
                if (millis() - gameOverTime > 3000)
                {
                    gameState = HIGHSCORE;
                    highscoreTime = millis();
                }

                if ((millis() - gameOverTime > 1000) &&
                    anyKeyPressed())
                {
                    resetGame();
                    gameState = PLAYING;
                }
            }
            else
            {
                if (digitalRead(BUTTON_PIN) == LOW)
                    velocity = JUMP_STRENGTH;

                velocity += GRAVITY;

                velocity = constrain(velocity, -50, 50);

                birdY += velocity;

                if (birdY < 0)
                    birdY = 0;

                movePipes();

                checkCollision();
            }

            u8g.firstPage();
            do
            {
                drawGame();
            }
            while (u8g.nextPage());

        break;

        //--------------------------------------------------
        // Highscore
        //--------------------------------------------------
        case HIGHSCORE:

            u8g.firstPage();
            do
            {
                renderHighscoreScreen();
            }
            while (u8g.nextPage());

            if (millis() - gameOverTime > 8000)
            {
                gameState = STARTSCREEN;
            }

            if (anyKeyPressed())
            {
                resetGame();
                gameState = PLAYING;
            }

        break;
    }
}

//--------------------------------------------------
// Button
//--------------------------------------------------

bool anyKeyPressed()
{
    return digitalRead(BUTTON_PIN) == LOW;
}

//--------------------------------------------------
// Reset Game
//--------------------------------------------------

void resetGame()
{
    birdY = SCREEN_HEIGHT * SCALE_FACTOR / 5;

    velocity = 0;

    score = 0;

    gameOver = false;

    pipes[0].x = SCREEN_WIDTH * SCALE_FACTOR;
    pipes[0].height = generatePipeHeight();

    for (int i = 1; i < MAX_PIPES; i++)
    {
        pipes[i].x =
            SCREEN_WIDTH * SCALE_FACTOR +
            i * PIPE_SPACING +
            random(-20, 20) * SCALE_FACTOR;

        pipes[i].height = generatePipeHeight();
    }
}

//--------------------------------------------------
// Random Pipe Height
//--------------------------------------------------

int generatePipeHeight()
{
    return random(
        10 * SCALE_FACTOR,
        SCREEN_HEIGHT * SCALE_FACTOR -
        PIPE_GAP -
        10 * SCALE_FACTOR
    );
}

//--------------------------------------------------
// Find Rightmost Pipe
//--------------------------------------------------

int findFurthestPipe()
{
    int maxX = pipes[0].x;

    for (int i = 1; i < MAX_PIPES; i++)
    {
        if (pipes[i].x > maxX)
            maxX = pipes[i].x;
    }

    return maxX;
}

//--------------------------------------------------
// Move Pipes
//--------------------------------------------------

void movePipes()
{
    int currentSpeed = PIPE_SPEED + score;

    for (int i = 0; i < MAX_PIPES; i++)
    {
        pipes[i].x -= currentSpeed;

        if (pipes[i].x < -PIPE_WIDTH)
        {
            pipes[i].x =
                findFurthestPipe() +
                PIPE_SPACING +
                random(-20, 20) * SCALE_FACTOR;

            pipes[i].height = generatePipeHeight();

            score++;
        }
    }
}

//--------------------------------------------------
// Collision Detection
//--------------------------------------------------

void checkCollision()
{
    for (int i = 0; i < MAX_PIPES; i++)
    {
        if (pipes[i].x < (15 + 2) * SCALE_FACTOR &&
            pipes[i].x + PIPE_WIDTH > (15 - 2) * SCALE_FACTOR)
        {
            if ((birdY - 2 * SCALE_FACTOR) < pipes[i].height ||
                (birdY + 2 * SCALE_FACTOR) >
                (pipes[i].height + PIPE_GAP))
            {
                gameOver = true;

                gameOverTime = millis();

                saveHighscores(score);
            }
        }
    }

    // Bird hits bottom

    if (birdY >= SCREEN_HEIGHT * SCALE_FACTOR)
    {
        gameOver = true;

        gameOverTime = millis();

        saveHighscores(score);
    }
}

//--------------------------------------------------
// Save Highscores
//--------------------------------------------------

void saveHighscores(int newScore)
{
    newHighscoreIndex = -1;

    for (int i = 0; i < 5; i++)
    {
        if (newScore > highscores[i])
        {
            for (int j = 4; j > i; j--)
            {
                highscores[j] = highscores[j - 1];
            }

            highscores[i] = newScore;

            newHighscoreIndex = i;

            break;
        }
    }
}

//--------------------------------------------------
// Draw Complete Game
//--------------------------------------------------

void drawGame()
{
    drawBird();
    drawPipes();
    drawScore();

    if (gameOver)
        displayGameOver();
}

//--------------------------------------------------
// Draw Bird
//--------------------------------------------------

void drawBird()
{
    int birdFrame = (frameCounter / 5) % 2;

    u8g.drawBitmapP(
        15 - BIRD_WIDTH_PX / 2,
        birdY / SCALE_FACTOR - BIRD_HEIGHT_PX / 2,
        2,                  // bytes per row
        8,                  // bitmap height
        epd_bitmap_allArray[birdFrame]);
}

//--------------------------------------------------
// Draw Pipes
//--------------------------------------------------

void drawPipes()
{
    for (int i = 0; i < MAX_PIPES; i++)
    {
        int pipeX = pipes[i].x / SCALE_FACTOR;

        int upperPipeHeight = pipes[i].height / SCALE_FACTOR;

        int gapHeight = PIPE_GAP / SCALE_FACTOR;

        int lowerPipeY = upperPipeHeight + gapHeight;

        int lowerPipeHeight = SCREEN_HEIGHT - lowerPipeY;

        int pipeWidth = PIPE_WIDTH / SCALE_FACTOR;

        // upper pipe

        if (upperPipeHeight > 6)
        {
            u8g.drawBox(
                pipeX,
                0,
                pipeWidth,
                upperPipeHeight - 6);

            u8g.drawBox(
                pipeX - 2,
                upperPipeHeight - 6,
                pipeWidth + 4,
                6);
        }

        // lower pipe

        u8g.drawBox(
            pipeX - 2,
            lowerPipeY,
            pipeWidth + 4,
            6);

        if (lowerPipeHeight > 6)
        {
            u8g.drawBox(
                pipeX,
                lowerPipeY + 6,
                pipeWidth,
                lowerPipeHeight - 6);
        }
    }
}

//--------------------------------------------------
// Draw Score
//--------------------------------------------------

void drawScore()
{
    char buf[8];

    itoa(score, buf, 10);

    u8g.setFont(u8g_font_6x10);

    u8g.drawStr(108, 10, buf);
}

//--------------------------------------------------
// Start Screen
//--------------------------------------------------

void renderStartScreen()
{
    u8g.setFont(u8g_font_fub14);

    u8g.drawStr(8, 24, "Ardu");

    u8g.drawStr(8, 46, "Bird");

    u8g.setFont(u8g_font_6x10);

    u8g.drawStr(18, 62, "Press Button");
}

//--------------------------------------------------
// Game Over
//--------------------------------------------------

void displayGameOver()
{
    // white box

    u8g.drawBox(
        20,
        5,
        SCREEN_WIDTH - 40,
        SCREEN_HEIGHT - 10);

    // black text inside box

    u8g.setColorIndex(0);

    u8g.setFont(u8g_font_6x10);

    u8g.drawStr(38, 18, "GAME OVER");

    u8g.drawStr(35, 30, "Your Score");

    char buf[8];

    itoa(score, buf, 10);

    int w = u8g.getStrWidth(buf);

    u8g.setFont(u8g_font_fub17);

    u8g.drawStr(64 - w / 2, 54, buf);

    // restore drawing color

    u8g.setColorIndex(1);

    u8g.setFont(u8g_font_6x10);
}

//--------------------------------------------------
// Highscore Screen
//--------------------------------------------------

void renderHighscoreScreen()
{
    u8g.setFont(u8g_font_6x10);

    u8g.drawStr(28, 10, "HIGHSCORES");

    // blinking newest score

    if (millis() - lastBlinkTime > 100)
    {
        showBlink = !showBlink;

        lastBlinkTime = millis();
    }

    char buf[20];

    for (int i = 0; i < 5; i++)
    {
        if (i == newHighscoreIndex && !showBlink)
            continue;

        sprintf(
            buf,
            "%d. %ld",
            i + 1,
            highscores[i]);

        u8g.drawStr(
            24,
            22 + i * 10,
            buf);
    }
}
