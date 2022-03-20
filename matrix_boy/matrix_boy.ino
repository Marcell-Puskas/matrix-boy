#include "matrix_boy_IO.h"
#include "matrix_boy_apps.h"

#include "Tetris_game.h"
#include "ballgames.h"
#include "Egg_game.h"

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 1, 2, 6, NEO_TILE_TOP, NEO_GRB);
//matrixWidth, matrixHeight, tilesX, tilesY, pin, matrixType, ledType

//static const 
const int app_count = 7;
const int anim_speed = 25;

int bright = 2;

int selected_game = 0;

int up_timeout, down_timeout, left_timeout, right_timeout, button_timeout;
int timeout_x, timeout_y, timeout_b;
bool pause_menu;
bool gyro_mode = false;
char keychar;

void call_game(int game_index) {
    switch (game_index)
    {
        case 0:
        Snake_game();
        break;

        case 1:
        {
            Tetris T;
            T.Tetris_game();
        }
        break;

        case 2:
        {
            Breakout B;
            B.Breakout_game();
        }
        break;
        
        case 3:
        {
            Pong P;
            P.Pong_game();
        }
        break;

        case 4:
        {
            Egg E;
            E.Egg_game();
        }
        break;

        case 5:
        Brightness_selector();
        break;

        case 6:
        gyro_test();
        break;
    }
}

void setup() {
    matrix.begin();
    matrix.setBrightness(bright);
    Serial.begin(9600);
    Serial.println("MatrixBoy Running");
    pinMode(JOYB, INPUT_PULLUP);
    gyro_setup();
}

void loop() {
    switch (keychar)
    {
        case 'a':
        selected_game = (selected_game - 1 + app_count) % app_count;
        for (size_t i = 0; i < mapx; i++)
        {
            matrix.drawRGBBitmap(i, 0, (bmps[ (selected_game + 1 + app_count) % app_count ]), 8, 16);
            matrix.drawRGBBitmap(-mapx+i, 0, (bmps[selected_game]), 8, 16);
            matrix.show();
            delay(anim_speed);
        }
        break;

        case 'd':
        selected_game = (selected_game + 1 + app_count) % app_count;
        for (size_t i = 0; i < mapx; i++)
        {
            matrix.drawRGBBitmap(-i, 0, (bmps[ (selected_game - 1 + app_count) % app_count ]), 8, 16);
            matrix.drawRGBBitmap(mapx-i, 0, (bmps[selected_game]), 8, 16);
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

        //app[selected_game]();
        call_game(selected_game);
        break;
    }

    matrix.drawRGBBitmap(0, 0, (bmps[selected_game]), 8, 16);
    matrix.show();

    pause_menu = false;
    Input(true);

    delay(input_update);
}
