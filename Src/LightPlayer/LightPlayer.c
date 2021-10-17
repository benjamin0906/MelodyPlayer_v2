/*
 * LightPlayer.c
 *
 *  Created on: 2021. okt. 15.
 *      Author: Benjamin
 */

#include "types.h"
#include "GPIO.h"

static uint8 PrevNote;
static uint8 Led;

void LightPlayer_NoteStart(uint8 Note);
void LightPlayer_NoteStop(void);

void LightPlayer_NoteStart(uint8 Note)
{
    if(Note != 0)
    {
        if(PrevNote != Note)
        {
            PrevNote = Note;
            if(Led == 0) Led = 1;
            else Led = 0;
        }
        if(Led == 0) GPIO_Set(PortA_1, Set);
        else GPIO_Set(PortA_0, Set);
    }
}

void LightPlayer_NoteStop(void)
{
    GPIO_Set(PortA_0, Clear);
    GPIO_Set(PortA_1, Clear);
}
