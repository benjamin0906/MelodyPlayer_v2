/*
 * SineGen.c
 *
 *  Created on: 2021. okt. 15.
 *      Author: Benjamin
 */

#include "types.h"
#include "BasicTIM.h"
#include "DAC.h"
#include "GPIO.h"
#include "RCC.h"
#include "DMA.h"

static const uint16 SineLookup[100] = { 2048, 2177, 2305, 2432, 2557, 2681, 2802, 2920, 3035, 3145,
		                                3252, 3353, 3450, 3541, 3626, 3705, 3777, 3843, 3901, 3952,
		                                3996, 4032, 4060, 4080, 4092, 4096, 4092, 4080, 4060, 4032,
		                                3996, 3952, 3901, 3843, 3777, 3705, 3626, 3541, 3450, 3353,
		                                3252, 3145, 3035, 2920, 2802, 2681, 2557, 2432, 2305, 2177,
		                                2048, 1919, 1791, 1664, 1539, 1415, 1294, 1176, 1061, 951,
		                                844,  743,  646,  555,  470,  391,  319,  253,  195,  144,
		                                100,  64,   36,   16,   4,    0,    4,    16,   36,   64,
		                                100,  144,  195,  253,  319,  391,  470,  555,  646,  743,
		                                844,  951,  1061, 1176, 1294, 1415, 1539, 1664, 1791, 1919};

void SineGen_Init();
void TimerInterrupt();
void SineGen_Apply(float32 Freq);

void SineGen_Init()
{
    dtBasicTimConfig config = {.MasterMode = 0, .AutoReload = 0, .Prescaler = 99, .ARPreload = 1, .UpdateDisable = 0, .UpdateSource = 0, .OnePulse = 0, .Enable = 1, .DmaTrig = 1};
    BasicTIM_Set(TIM6, config, 0);
    DMA_Set(DMA_1, Ch3, SineLookup, 0x40007408, DMA_CS6|DMA_MEMREAD|DMA_MEM_16|DMA_MEM_INC|DMA_PER_32|DMA_PRIO_VH|DMA_CIRC, 0);
}

void SineGen_Apply(float32 Freq)
{
    if(Freq != 0)
    {
        uint16 Ps = 1;
        float32 T = RCC_GetClock(APB1_Timer);
        T /= Freq*100;
        while(T/Ps > 65535) Ps++;
        BasicTIM_SetPS(TIM6, Ps-1);
        BasicTIM_SetAR(TIM6, (uint16)T/Ps);
        BasicTIM_Update(TIM6);
        DMA_Start(DMA_1, Ch3, 100);
    }
    else BasicTIM_SetAR(TIM6, (uint16)0);
}

void SineGen_Stop()
{
    BasicTIM_SetAR(TIM6, 0);
    DMA_Stop(DMA_1, Ch3);
}

