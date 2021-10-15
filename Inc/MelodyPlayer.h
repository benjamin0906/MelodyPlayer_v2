/*
 * MelodyPlayer.h
 *
 *  Created on: 15 May 2020
 *      Author: Bodnár Benjamin
 */

#ifndef MELODYPLAYER_MELODYPLAYER_H_
#define MELODYPLAYER_MELODYPLAYER_H_

#include "types.h"

typedef enum
{
	Pause	= 0,
	C0		= 1,
	C0_half		,
	D0			,
	D0_half		,
	E0			,
	F0			,
	F0_half		,
	G0			,
	G0_half		,
	A0			,
	A0_half		,
	B0			,
	
	C1			,
	C1_half		,
	D1			,
	D1_half		,
	E1			,
	F1			,
	F1_half		,
	G1			,
	G1_half		,
	A1			,
	A1_half		,
	B1			,
				
	C2			,
	C2_half		,
	D2			,
	D2_half		,
	E2			,
	F2			,
	F2_half		,
	G2			,
	G2_half		,
	A2			,
	A2_half		,
	B2			,
				
	C3			,
	C3_half		,
	D3			,
	D3_half		,
	E3			,
	F3			,
	F3_half		,
	G3			,
	G3_half		,
	A3			,
	A3_half		,
	B3			,
				
	C4			,
	C4_half		,
	D4			,
	D4_half		,
	E4			,
	F4			,
	F4_half		,
	G4			,
	G4_half		,
	A4			,
	A4_half		,
	B4			,
				
	C5			,
	C5_half		,
	D5			,
	D5_half		,
	E5			,
	F5			,
	F5_half		,
	G5			,
	G5_half		,
	A5			,
	A5_half		,
	B5			,
				
	C6			,
	C6_half		,
	D6			,
	D6_half		,
	E6			,
	F6			,
	F6_half		,
	G6			,
	G6_half		,
	A6			,
	A6_half		,
	B6			,
				
	C7			,
	C7_half		,
	D7			,
	D7_half		,
	E7			,
	F7			,
	F7_half		,
	G7			,
	G7_half		,
	A7			,
	A7_half		,
	B7			,
				
	C8			,
	C8_half		,
	D8			,
	D8_half		,
	E8			,
	F8			,
	F8_half		,
	G8			,
	G8_half		,
	A8			,
	A8_half		,
	B8			,
	
} dtMusicNotes;

typedef struct
{
	uint8 MusicNote;
	struct
	{
	uint8 Nominator;
	uint8 Denominator;
	} Beat;
} dtMusicNoteDesc;

typedef struct
{
	dtMusicNoteDesc *Notes;
	uint32 Length;
	uint32 beat;
} dtMelody;

extern void MelodyPlayer_Task(void);
extern void MelodyPlayer_Start(dtMelody melody);
extern void MelodyPlayer_Stop(void);

#endif /* MELODYPLAYER_MELODYPLAYER_H_ */
