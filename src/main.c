/**
 * @file        main.c
 * @brief       Raspberry PiによるLED輝度のPWM制御
 * @author      Keitetsu
 * @date        2016/10/02
 * @copyright   Copyright (c) 2016 Keitetsu
 * @license     This software is released under the MIT License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <wiringPi.h>

#include "ProgramInfo.h"

#define LED                 18              /*!< LEDのGPIOポート番号 */

#define LED_PWM_DIV         3               /*!< LEDのPWMタイマ分周比（PWM周波数: 約24kHz） */
#define LED_PWM_RANGE       256             /*!< LEDのPWM分解能 */
#define LED_PWM_INTERVAL    4000            /*!< LEDの明暗変化間隔（デューティ比変更間隔）（マイクロ秒） */
#define LED_PWM_LOOP        10              /*!< LEDの明暗繰返し回数 */


/**
 * @brief   メイン関数
 * @retval  EXIT_SUCCESS    正常終了
 * @retval  EXIT_FAILURE    異常終了
 */
int main(int argc, char *argv[])
{
    int led_pwm_div;
    int led_pwm_interval, led_pwm_loop;
    int led_pwm_count;
    int led_bright;
    int retval;
    int opt, optlong_index;
    struct option longopts[] = {
        { "divisor",  required_argument, NULL, 'd' },
        { "help",     no_argument,       NULL, 'h' },
        { "interval", required_argument, NULL, 'i' },
        { "loop",     required_argument, NULL, 'l' },
        { "version",  no_argument,       NULL, 'v' },
        { 0,          0,                 0,    0   }
    };

    // 設定変数の初期化
    led_pwm_div = LED_PWM_DIV;
    led_pwm_interval = LED_PWM_INTERVAL;
    led_pwm_loop = LED_PWM_LOOP;

    // コマンドオプション処理
    while((opt = getopt_long(argc, argv, "d:hi:l:v", longopts, &optlong_index)) != -1) {
        switch(opt) {
            case 'd':
                led_pwm_div = atoi(optarg);
                if(led_pwm_div < 0) {
                    printf("Error: invalid divisor value: %d\n",
                            led_pwm_div);
                    
                    exit(EXIT_FAILURE);
                }
                break;
            case 'h':
                printHelp();

                exit(EXIT_SUCCESS);
                break;
            case 'i':
                led_pwm_interval = atoi(optarg);
                if(led_pwm_interval < 0) {
                    printf("Error: invalid interval time: %d usec\n",
                            led_pwm_interval);
                    
                    exit(EXIT_FAILURE);
                }
                break;
            case 'l':
                led_pwm_loop = atoi(optarg);
                if(led_pwm_loop < 0) {
                    printf("Error: invalid loop count: %d\n",
                            led_pwm_loop);

                    exit(EXIT_FAILURE);
                }
                break;
            case 'v':
                printVersion();

                exit(EXIT_SUCCESS);
                break;
            default:
                printf("Error: invalid argument\n");

                exit(EXIT_FAILURE);
                break;
        }
    }

    // WiringPiのセットアップ
    retval = wiringPiSetupGpio();
    if(retval == -1) {
        printf("Error: failed to setup WiringPi\n");

        exit(EXIT_FAILURE);
    }

    pinMode(LED, PWM_OUTPUT);           // ポート設定
    pwmSetMode(PWM_MODE_BAL);           // PWMモードの設定（バランスモード）
    pwmSetClock(led_pwm_div);           // PWMタイマ分周比の設定
    pwmSetRange(LED_PWM_RANGE);         // PWMタイマ分解能の設定

    // 設定の表示
    printf("divisor value: %d\n", led_pwm_div);
    printf("interval time: %d usec, loop count: %d\n", led_pwm_interval, led_pwm_loop);

    // LED輝度のPWM制御
    for(led_pwm_count = 0; led_pwm_count < led_pwm_loop; led_pwm_count++) {
        // 暗 -> 明
        for(led_bright = 0; led_bright < LED_PWM_RANGE; led_bright++) {
            pwmWrite(LED, led_bright);  // デューティ比の設定
            usleep(led_pwm_interval);
        }
        
        // 明 -> 暗
        for(led_bright = (LED_PWM_RANGE - 1); led_bright >= 0; led_bright--) {
            pwmWrite(LED, led_bright);
            usleep(led_pwm_interval);
        }
    }

    exit(EXIT_SUCCESS);
}

