/*
 * MelodyPlay_Types.h
 *
 *  Created on: 15 May 2020
 *      Author: Bodnár Benjamin
 */

#ifndef MELODYPLAYER_MELODYPLAYER_TYPES_H_
#define MELODYPLAYER_MELODYPLAYER_TYPES_H_

#include "types.h"

typedef enum
{
	Idle,
	NoteChange,
	Wait,
	SilentWait,
} dtState;

#endif /* MELODYPLAYER_MELODYPLAYER_TYPES_H_ */
