/*
 * MelodyPlayer.c
 *
 *  Created on: 15 May 2020
 *      Author: Bodnár Benjamin
 */

#include "MelodyPlayer_Types.h"
#include "MelodyPlayer.h"
#include "SineGen.h"
#include "main.h"
#include "Utilities.h"
#include "GPIO.h"

static uint32 Bpm;
static uint32 NoteCounter;
static dtState State;
static dtMelody CurrentMelody;
static uint32 Time;
static uint32 Timeout;
static uint8 PrevNote;
static uint8 Led;

void MelodyPlayer_Task(void);
void MelodyPlayer_Start(dtMelody melody);
void MelodyPlayer_Stop(void);
float32 ChooseFreq(uint8 Note);
uint32 TimeoutFinder(void);

void MelodyPlayer_Task(void)
{
	switch(State)
	{
	case Idle:
		break;
	case NoteChange:
		if(NoteCounter < CurrentMelody.Length)
		{
			Time = GetTicks();
			SineGen_Apply(ChooseFreq(CurrentMelody.Notes[NoteCounter].MusicNote));
			Timeout = TimeoutFinder();
			NoteCounter++;
			State = Wait;

			if(PrevNote != CurrentMelody.Notes[NoteCounter].MusicNote)
			{
			    PrevNote = CurrentMelody.Notes[NoteCounter].MusicNote;
			    if(Led == 0) Led = 1;
			    else Led = 0;
			}
			if(Led == 0)
            {
                GPIO_Set(PortA_0, Clear);
                GPIO_Set(PortA_1, Set);
            }
            else
            {
                GPIO_Set(PortA_0, Set);
                GPIO_Set(PortA_1, Clear);
            }
		}
		else
		{
			State = Idle;
		}
		break;
	case Wait:
		if(IsPassed(Time, (Timeout*4)/5))
		{
			SineGen_Stop();
			State = SilentWait;
            GPIO_Set(PortA_0, Clear);
            GPIO_Set(PortA_1, Clear);
		}
		break;
	case SilentWait:
	    if(IsPassed(Time, Timeout))
        {
            State = NoteChange;
        }
	    break;
	}
}

void MelodyPlayer_Start(dtMelody melody)
{
	if(State == Idle)
	{
		State = NoteChange;
		CurrentMelody = melody;
		Bpm = 240000/CurrentMelody.beat;
		NoteCounter = 0;
	}
}

void MelodyPlayer_Stop(void)
{
    SineGen_Stop();
	State = Idle;
}

uint32 TimeoutFinder(void)
{
	float32 rythm = Bpm;
	rythm *= (float32)CurrentMelody.Notes[NoteCounter].Beat.Nominator;
	rythm /= (float32)CurrentMelody.Notes[NoteCounter].Beat.Denominator;
	if((rythm - ((uint32)rythm)) >= 0.5) rythm+=1;
	return (uint32) rythm;
}

float32 ChooseFreq(uint8 Note)
{
	float32 ret = 0;
	switch(Note)
	{
	case Pause	: ret = 0; break;
	case C0		: ret = 16.35; break;
	case C0_half: ret = 17.32; break;
	case D0		: ret = 18.35; break;
	case D0_half: ret = 19.45; break;
	case E0		: ret = 20.60; break;
	case F0		: ret = 21.83; break;
	case F0_half: ret = 23.12; break;
	case G0		: ret = 24.50; break;
	case G0_half: ret = 25.96; break;
	case A0		: ret = 27.50; break;
	case A0_half: ret = 29.14; break;
	case B0		: ret = 30.87; break;
	case C1		: ret = 32.70; break;
	case C1_half: ret = 34.65; break;
	case D1		: ret = 36.71; break;
	case D1_half: ret = 38.89; break;
	case E1		: ret = 41.20; break;
	case F1		: ret = 43.65; break;
	case F1_half: ret = 46.25; break;
	case G1		: ret = 49.00; break;
	case G1_half: ret = 51.91; break;
	case A1		: ret = 55.00; break;
	case A1_half: ret = 58.27; break;
	case B1		: ret = 61.74; break;
	
	case C2		: ret = 65.41; break;
	case C2_half: ret = 69.30; break;
	case D2		: ret = 73.42; break;
	case D2_half: ret = 77.78; break;
	case E2		: ret = 82.41; break;
	case F2		: ret = 87.31; break;
	case F2_half: ret = 92.50; break;
	case G2		: ret = 98.00; break;
	case G2_half: ret = 103.83; break;
	case A2		: ret = 110.00; break;
	case A2_half: ret = 116.54; break;
	case B2		: ret = 123.47; break;
	
	case C3		: ret = 130.81; break;
	case C3_half: ret = 138.59; break;
	case D3		: ret = 146.83; break;
	case D3_half: ret = 155.56; break;
	case E3		: ret = 164.81; break;
	case F3		: ret = 174.61; break;
	case F3_half: ret = 185.00; break;
	case G3		: ret = 196.00; break;
	case G3_half: ret = 207.65; break;
	case A3		: ret = 220.00; break;
	case A3_half: ret = 233.08; break;
	case B3		: ret = 246.94; break;
	
	case C4		: ret = 261.63; break;
	case C4_half: ret = 277.18; break;
	case D4		: ret = 293.66; break;
	case D4_half: ret = 311.13; break;
	case E4		: ret = 329.63; break;
	case F4		: ret = 349.23; break;
	case F4_half: ret = 369.99; break;
	case G4		: ret = 392.00; break;
	case G4_half: ret = 415.30; break;
	case A4		: ret = 440.00; break;
	case A4_half: ret = 466.16; break;
	case B4		: ret = 493.88; break;
	
	case C5		: ret = 523.25; break;
	case C5_half: ret = 554.37; break;
	case D5		: ret = 587.33; break;
	case D5_half: ret = 622.25; break;
	case E5		: ret = 659.25; break;
	case F5		: ret = 698.46; break;
	case F5_half: ret = 739.99; break;
	case G5		: ret = 783.99; break;
	case G5_half: ret = 830.61; break;
	case A5		: ret = 880.00; break;
	case A5_half: ret = 932.33; break;
	case B5		: ret = 987.77; break;
	
	case C6		: ret = 1046.50; break;
	case C6_half: ret = 1108.73; break;
	case D6		: ret = 1174.66; break;
	case D6_half: ret = 1244.51; break;
	case E6		: ret = 1318.51; break;
	case F6		: ret = 1396.91; break;
	case F6_half: ret = 1479.98; break;
	case G6		: ret = 1567.98; break;
	case G6_half: ret = 1661.22; break;
	case A6		: ret = 1760.00; break;
	case A6_half: ret = 1864.66; break;
	case B6		: ret = 1975.53; break;
	
	case C7		: ret = 2093.00; break;
	case C7_half: ret = 2217.46; break;
	case D7		: ret = 2349.32; break;
	case D7_half: ret = 2489.02; break;
	case E7		: ret = 2637.02; break;
	case F7		: ret = 2793.83; break;
	case F7_half: ret = 2959.96; break;
	case G7		: ret = 3135.96; break;
	case G7_half: ret = 3322.44; break;
	case A7		: ret = 3520.00; break;
	case A7_half: ret = 3729.31; break;
	case B7		: ret = 3951.07; break;
	
	case C8		: ret = 4186.01; break;
	case C8_half: ret = 4434.92; break;
	case D8		: ret = 4698.63; break;
	case D8_half: ret = 4978.03; break;
	case E8		: ret = 5274.04; break;
	case F8		: ret = 5587.65; break;
	case F8_half: ret = 5919.91; break;
	case G8		: ret = 6271.93; break;
	case G8_half: ret = 6644.88; break;
	case A8		: ret = 7040.00; break;
	case A8_half: ret = 7458.62; break;
	case B8		: ret = 7902.13; break;
	}
	return ret;
}
