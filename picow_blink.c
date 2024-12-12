#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

volatile bool run = true;

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    run = false;
    return 0;
}

int main() {
    stdio_init_all();
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return -1;
    }
    
    int days = 0;
    int hours = 0;
    long minutes = 1;
    long seconds = 3;

    hours += days * 24;
    minutes += hours * 60;
    seconds += minutes * 60;

    add_alarm_in_ms(seconds * 1000, alarm_callback, NULL, false);
    
    while (run) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(250);
    }
    return 0;
}