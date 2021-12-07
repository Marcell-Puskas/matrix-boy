#include "matrix_boy_IO.h"

const int egg_color_num = 4;
const int pad_size = 3;

const uint32_t pad_color = matrix.Color(255, 255, 255);
const uint32_t egg_colors[] = {
    0,
    matrix.Color(255, 0, 0),
    matrix.Color(255, 255, 0),
    matrix.Color(0, 255, 0),
    matrix.Color(0, 255, 255),
    matrix.Color(0, 0, 255),
};

int spawnrate, pos_pad;

extern int points, speed;
extern int intmap[mapx][mapy];
extern bool run, gameover;

void Egg_print()
{
    for(size_t cy = 0; cy < mapy; cy++)
    {
        for(size_t cx = 0; cx < mapx; cx++)
        {
            matrix.drawPixel(cx, cy, egg_colors[ intmap[cx][cy] ]);
        }   
    }
    matrix.drawLine(pos_pad, mapy -1, pos_pad + pad_size -1, mapy-1, pad_color);
    matrix.show();
}

void Egg_game()
{
    run = true;
    gameover = false;
    memset(intmap, 0, sizeof(intmap));
    pos_pad = 0;
    speed = 25;
    spawnrate = 4;
    points = 0;

    while(run)
    {
        intmap[ random(mapx) ][0] = random(1, egg_color_num);

        for(size_t rounds = 0; rounds < spawnrate && run; rounds++)
        {
            for(int cy = mapy - 2; cy >= 0; cy--)
            {
                for(size_t cx = 0; cx < mapx; cx++)
                {
                    if(intmap[cx][cy] != 0)
                    {
                        intmap[cx][cy + 1] = intmap[cx][cy];
                        intmap[cx][cy] = 0;
                    }
                }
            }

            for (size_t i = 0; i < mapx; i++)
            {
                if(intmap[i][mapy - 1] != 0)
                {
                    if(pos_pad <= i && i < pos_pad + pad_size)
                    {
                        intmap[i][mapy - 1] = 0;
                        points++;
                        speed = max(10, 15 - points);
                    }
                    else
                    {
                        run = false;
                        gameover = true;
                    }
                }
            }

            for (size_t i = 0; i < speed; i++)
            {
                Input();
                switch (keychar)
                {
                    case 'd': if(pos_pad + pad_size < mapx) pos_pad++; break;
                    case 'a': if(pos_pad > 0) pos_pad--; break;
                    case 'e': run = false;
                }
                Egg_print();
                delay(input_update);
            }
        }
    }

    if(gameover)
    {
        Serial.print("Game over, points: ");
        Serial.println(points);
        matrix.setCursor(0, 0);
        matrix.clear();
        matrix.print(points);
        matrix.show();
        delay(2000);// hardcode
    }
}
