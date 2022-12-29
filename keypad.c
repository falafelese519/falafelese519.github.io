#include "app.h"

#define ROWS 4 //four rows
#define COLS 4 //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

#define ROW1_GPIO   3
#define ROW2_GPIO   4
#define ROW3_GPIO   6
#define ROW4_GPIO   5

#define COL1_GPIO   26
#define COL2_GPIO   27
#define COL3_GPIO   28
#define COL4_GPIO   29

#define SOLENOID_GPIO   20
#define WIFI_GPIO       25


int rowPins[ROWS] = {ROW1_GPIO, ROW2_GPIO, ROW3_GPIO, ROW4_GPIO}; //connect to the row pinouts of the keypad
int colPins[COLS] = {COL1_GPIO, COL2_GPIO, COL3_GPIO, COL4_GPIO}; //connect to the column pinouts of the keypad


char scan_kepad()
{
    int i = 0, j = 0; 

    // Re-intialize the row pins. Allows sharing these pins with other hardware.
	for (i=0; i<COLS; i++) {
		//pin_mode(rowPins[r],INPUT_PULLUP);
        gpio_pull_up(colPins[i]);
        //gpio_pull_up(rowPins[i]);
        //gpio_put(colPins[i], 0);
	}

    //gpio_put(colPins[0], 1); gpio_put(colPins[1], 1); gpio_put(colPins[2], 1); gpio_put(colPins[3], 1);

    /*

    gpio_put(colPins[0], 0); gpio_put(colPins[1], 1); gpio_put(colPins[2], 1); gpio_put(colPins[3], 1);

    if (gpio_get(rowPins[0]) == 0) { sleep_ms(100); while (gpio_get(rowPins[0]) == 0); return keys[0][0]; }
	if (gpio_get(rowPins[1]) == 0) { sleep_ms(100); while (gpio_get(rowPins[1]) == 0); return keys[1][0]; }
	if (gpio_get(rowPins[2]) == 0) { sleep_ms(100); while (gpio_get(rowPins[2]) == 0); return keys[2][0]; }
	if (gpio_get(rowPins[3]) == 0) { sleep_ms(100); while (gpio_get(rowPins[3]) == 0); return keys[3][0]; }

    gpio_put(colPins[0], 1); gpio_put(colPins[1], 0); gpio_put(colPins[2], 1); gpio_put(colPins[3], 1);

    if (gpio_get(rowPins[0]) == 0) { sleep_ms(100); while (gpio_get(rowPins[0]) == 0); return keys[0][1]; }
	if (gpio_get(rowPins[1]) == 0) { sleep_ms(100); while (gpio_get(rowPins[1]) == 0); return keys[1][1]; }
	if (gpio_get(rowPins[2]) == 0) { sleep_ms(100); while (gpio_get(rowPins[2]) == 0); return keys[2][1]; }
	if (gpio_get(rowPins[3]) == 0) { sleep_ms(100); while (gpio_get(rowPins[3]) == 0); return keys[3][1]; }

    gpio_put(colPins[0], 1); gpio_put(colPins[1], 1); gpio_put(colPins[2], 0); gpio_put(colPins[3], 1);

    if (gpio_get(rowPins[0]) == 0) { sleep_ms(100); while (gpio_get(rowPins[0]) == 0); return keys[0][2]; }
	if (gpio_get(rowPins[1]) == 0) { sleep_ms(100); while (gpio_get(rowPins[1]) == 0); return keys[1][2]; }
	if (gpio_get(rowPins[2]) == 0) { sleep_ms(100); while (gpio_get(rowPins[2]) == 0); return keys[2][2]; }
	if (gpio_get(rowPins[3]) == 0) { sleep_ms(100); while (gpio_get(rowPins[3]) == 0); return keys[3][2]; }

    gpio_put(colPins[0], 1); gpio_put(colPins[1], 1); gpio_put(colPins[2], 1); gpio_put(colPins[3], 0);

    if (gpio_get(rowPins[0]) == 0) { sleep_ms(100); while (gpio_get(rowPins[0]) == 0); return keys[0][3]; }
	if (gpio_get(rowPins[1]) == 0) { sleep_ms(100); while (gpio_get(rowPins[1]) == 0); return keys[1][3]; }
	if (gpio_get(rowPins[2]) == 0) { sleep_ms(100); while (gpio_get(rowPins[2]) == 0); return keys[2][3]; }
	if (gpio_get(rowPins[3]) == 0) { sleep_ms(100); while (gpio_get(rowPins[3]) == 0); return keys[3][3]; }

    return '!';

    */

    
    for(i = 0; i < ROWS; i++)
    {
        

        gpio_put(rowPins[0], 1); gpio_put(rowPins[1], 1); gpio_put(rowPins[2], 1); gpio_put(rowPins[3], 1);
        //gpio_pull_up(colPins[0]); gpio_pull_up(colPins[1]); gpio_pull_up(colPins[2]); gpio_pull_up(colPins[3]);
        //gpio_set_dir(rowPins[i], GPIO_OUT);
        gpio_put(rowPins[i], 0);

        for(j = 0; j < COLS; j++)
        {
            

            //gpio_pull_up(rowPins[j]);


            if(!gpio_get(colPins[j]))
            {
                sleep_ms(100);
                printf("i = %d j = %d \n", i, j);
                return keys[i][j];
            }
        }

       
        //gpio_set_dir(rowPins[i], GPIO_IN);
    }

    return '!'; 
}

void init_keypad()
{

    for(int i = 0; i < ROWS; i++)
    {
        gpio_init(rowPins[i]);
        gpio_init(colPins[i]);
    }

    gpio_set_dir(colPins[0], GPIO_IN); 
    gpio_set_dir(colPins[1], GPIO_IN);
    gpio_set_dir(colPins[2], GPIO_IN); 
    gpio_set_dir(colPins[3], GPIO_IN);

    gpio_set_dir(rowPins[0], GPIO_OUT); 
    gpio_set_dir(rowPins[1], GPIO_OUT); 
    gpio_set_dir(rowPins[2], GPIO_OUT);  
    gpio_set_dir(rowPins[3], GPIO_OUT); 

    gpio_put(rowPins[0], 1);
    gpio_put(rowPins[1], 1);
    gpio_put(rowPins[2], 1);
    gpio_put(rowPins[3], 1);


}

char* get_input(char* str)
{
    int i = 0; 
    for(i = 0; i < 4; i++)
    {
        str[i] = scan_kepad();
        sleep_ms(250);
    }
}