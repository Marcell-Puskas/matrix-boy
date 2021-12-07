#include "matrix_boy_IO.h"

extern bool run;
extern int bright;
const  int max_bright = 16;

void Brightness_selector()
{
    const uint32_t color_slide = matrix.Color(255, 255, 255);
    run = true;
    pause_menu = false;

    while(run)
    {
        Input();

        switch (keychar)
        {
            case 'w':
                if(bright < max_bright) bright++;
                break;

            case 's':
                if(bright > 1) bright--;
                break;
            
            case 'o':
                run = false;
                break;
        }

        matrix.setBrightness(bright);

        matrix.clear();
        matrix.setCursor(0, 0);
        matrix.print(bright);
        matrix.drawLine(mapx -1 , mapy - bright, mapx -1, mapy - 1, color_slide);
        matrix.show();

        delay(input_update);
    }
}