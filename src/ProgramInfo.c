/**
 * @file        ProgramInfo.c
 * @brief       プログラム情報の表示関数
 * @author      Keitetsu
 * @date        2016/10/22
 * @copyright   Copyright (c) 2016 Keitetsu
 * @license     This software is released under the MIT License.
 */

#include <stdio.h>

#include "ProgramInfo.h"
#include "Version.h"


void printHelp(void)
{
    printf("Usage: RasPi_LED_Firefly [OPTION...]\n");
    printf("\n");
    printf("  -d, --divisor=DIVISOR     set the divisor for PWM clock\n");
    printf("  -h, --help                give this help list\n");
    printf("  -i, --interval=INTERVAL   set the duty change interval time (usec)\n");
    printf("  -l, --loop=LOOP           set the loop count\n");
    printf("  -v, --version             print program version\n");

    return;
}


void printVersion(void)
{
    printf("Version: %s\n", VERSION);

    return;
}

