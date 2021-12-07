#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include "matrix_boy_IO.h"
#include "matrix_boy_apps.h"

const int matrixWidth = 8;
const int matrixHeight = 8;
const int tilesX = 1;
const int tilesY = 2;
const int pin = 6;
const int matrixType = NEO_TILE_TOP;
const int ledType = NEO_GRB;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
    matrixWidth, matrixHeight, tilesX, tilesY, pin, matrixType, ledType);

//static const 
const int game_count = 6;
const int anim_speed = 25;

int bright = 2;
int selected_game = 0;

int up_timeout, down_timeout, left_timeout, right_timeout, button_timeout;
int timeout_x, timeout_y, timeout_b;
bool pause_menu;

int intmap[mapx][mapy];

char keychar;
int posx, posy, dir, selected_index, points, speed;
bool run, gameover;

void setup() {
    matrix.begin();
    matrix.setBrightness(bright);
    Serial.begin(9600);
    Serial.println("MatrixBoy Running");
}

void loop() {
    if(Serial.available())
    {
        keychar = Serial.read();
        Serial.print("Selected: ");
        Serial.println(selected_game);
    }

    switch (keychar)
    {
        case 'a':
        selected_game = (selected_game - 1 + game_count) % game_count;
        for (size_t i = 0; i < matrixWidth; i++)
        {
            matrix.drawRGBBitmap(i, 0, (bmps[ (selected_game + 1 + game_count) % game_count ]), 8, 16);
            matrix.drawRGBBitmap(-matrixWidth+i, 0, (bmps[selected_game]), 8, 16);
            matrix.show();
            delay(anim_speed);
        }
        break;

        case 'd':
        selected_game = (selected_game + 1 + game_count) % game_count;
        for (size_t i = 0; i < matrixWidth; i++)
        {
            matrix.drawRGBBitmap(-i, 0, (bmps[ (selected_game - 1 + game_count) % game_count ]), 8, 16);
            matrix.drawRGBBitmap(matrixWidth-i, 0, (bmps[selected_game]), 8, 16);
            matrix.show();
            delay(anim_speed);
        }
        break;

        case 'o':
        up_timeout = default_timeout;
        down_timeout = default_timeout;
        left_timeout = default_timeout;
        right_timeout = default_timeout;
        button_timeout = default_timeout;
        pause_menu = true;

        app[selected_game]();
        break;
    }

    keychar = NULL;

    matrix.drawRGBBitmap(0, 0, (bmps[selected_game]), 8, 16);
    matrix.show();

    /* if(analogRead(JOYX) > joy_high_threshold) keychar = 'd';
    if(analogRead(JOYX) < joy_low_threshold) keychar = 'a';
    if(digitalRead(JOYB) == 0)
    {
        if(timeout_b == 0)
        {
            keychar = 'o';
            timeout_b = restart_timeout;
        }
    }
    else timeout_b = 0; */

    pause_menu = false;
    Input(true);

    delay(10);
}
