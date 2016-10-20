/**
 * @file    main.c
 * @brief   Raspberry PiによるLED輝度のPWM制御
 * @author  Keitetsu
 * @date    2016/10/02
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <wiringPi.h>

#define LED                 18              /*!< LEDのGPIOポート番号 */

#define LED_PWM_DIV         3               /*!< LEDのPWM周波数（約24kHz） */
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
        { "interval", required_argument, NULL, 'i' },
        { "loop",     required_argument, NULL, 'l' },
        { 0,          0,                 0,    0   }
    };

    led_pwm_div = LED_PWM_DIV;
    led_pwm_interval = LED_PWM_INTERVAL;
    led_pwm_loop = LED_PWM_LOOP;

    while((opt = getopt_long(argc, argv, "d:i:l:", longopts, &optlong_index)) != -1) {
        switch(opt) {
            case 'd':
                led_pwm_div = atoi(optarg);
                if(led_pwm_div < 0) {
                    printf("Error: invalid divisor value: %d\n",
                            led_pwm_div);
                    
                    exit(EXIT_FAILURE);
                }
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
            default:
                printf("Error: invalid argument\n");

                exit(EXIT_FAILURE);
                break;
        }
    }

    retval = wiringPiSetupGpio();
    if(retval == -1) {
        printf("Error: failed to setup Wiring Pi");

        exit(EXIT_FAILURE);
    }

    pinMode(LED, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_BAL);
    pwmSetClock(led_pwm_div);
    pwmSetRange(LED_PWM_RANGE);

    printf("divisor value: %d\n", led_pwm_div);
    printf("interval time: %d usec, loop count: %d\n", led_pwm_interval, led_pwm_loop);
    for(led_pwm_count = 0; led_pwm_count < led_pwm_loop; led_pwm_count++) {
        for(led_bright = 0; led_bright < LED_PWM_RANGE; led_bright++) {
            pwmWrite(LED, led_bright);
            usleep(led_pwm_interval);
        }
        
        for(led_bright = (LED_PWM_RANGE - 1); led_bright >= 0; led_bright--) {
            pwmWrite(LED, led_bright);
            usleep(led_pwm_interval);
        }
    }

    exit(EXIT_SUCCESS);
}

