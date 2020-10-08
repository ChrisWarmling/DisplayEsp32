#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <string.h>
#include <u8g2.h>

#include "sdkconfig.h"
#include "u8g2_esp32_hal.h"

#define PIN_SDA 5
#define PIN_SCL 4

void app_main(void);
void task_test_SSD1306i2c(void *ignore);
u8g2_t u8g2; 

static const char *TAG = "ssd1306";

void task_test_SSD1306i2c(void *ignore)
{
	u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
	u8g2_esp32_hal.sda = PIN_SDA;
	u8g2_esp32_hal.scl = PIN_SCL;
	u8g2_esp32_hal_init(u8g2_esp32_hal);

	u8g2_Setup_ssd1306_i2c_128x32_univision_f(
		&u8g2,
		U8G2_R0,
		
		u8g2_esp32_i2c_byte_cb,
		u8g2_esp32_gpio_and_delay_cb); 
	u8x8_SetI2CAddress(&u8g2.u8x8, 0x78);

	u8g2_InitDisplay(&u8g2); 

	u8g2_SetPowerSave(&u8g2, 0); 
	u8g2_ClearBuffer(&u8g2);

	while (true)
	{
		u8g2_SetFont(&u8g2, u8g2_font_ncenB12_tr);
		u8g2_DrawStr(&u8g2, 50, 15, "IoT");
		u8g2_SendBuffer(&u8g2);
		u8g2_SetFont(&u8g2, u8g2_font_ncenB10_tr);
		u8g2_DrawStr(&u8g2, 30, 30, "aplicada");
		u8g2_SendBuffer(&u8g2);
		vTaskDelay(2000 / portTICK_RATE_MS);

		u8g2_ClearBuffer(&u8g2);

		u8g2_SetFont(&u8g2, u8g2_font_ncenB08_tr);
		u8g2_DrawStr(&u8g2, 20, 15, "Eng. Computacao");
		u8g2_SendBuffer(&u8g2);
		u8g2_SetFont(&u8g2, u8g2_font_ncenB12_tr);
		u8g2_DrawStr(&u8g2, 45, 30, "SATC");
		u8g2_SendBuffer(&u8g2);
		vTaskDelay(2000 / portTICK_RATE_MS);

		u8g2_ClearBuffer(&u8g2);

		u8g2_SetFont(&u8g2, u8g2_font_ncenB10_tr);
		u8g2_DrawStr(&u8g2, 30, 15, "Christian");
		u8g2_SendBuffer(&u8g2);
		u8g2_SetFont(&u8g2, u8g2_font_ncenB10_tr);
		u8g2_DrawStr(&u8g2, 30, 30, "Warmling");
		u8g2_SendBuffer(&u8g2);
		vTaskDelay(2000 / portTICK_RATE_MS);

		u8g2_ClearBuffer(&u8g2);

	};
	vTaskDelete(NULL);
}

void app_main(void)
{
	xTaskCreate(task_test_SSD1306i2c, "task_test_SSD1306i2c", 2048, NULL, 1, NULL);
}