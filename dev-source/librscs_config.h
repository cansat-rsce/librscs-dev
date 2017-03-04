#ifndef CONFIG_H_
#define CONFIG_H_

#include <avr/io.h>


// ========================================================
// Настройки SPI - драйвера соответствующего контроллера атмеги
// (пока поддерживается только режим мастера)
// ========================================================
// Настройки пинов зависят от микроконтроллера - пины SPI модуля нужно конфигурировать руками...
#ifdef __AVR_ATmega328P__

#define RSCS_SPI_PORTX	(PORTB) // регистр PORT порта на котором висят все пины SPI
#define RSCS_SPI_DDRX	(DDRB)	// регистр DDR порта на котором висят все пины SPI
#define RSCS_SPI_MISO	(4)		// номер MISO пина
#define RSCS_SPI_MOSI	(3)		// номер MOSI пина
#define RSCS_SPI_SCK	(5)		// номер SCK пина
#define RSCS_SPI_SS 	(2)		// номер аппаратного CHIP_SELECT пина

#elif defined __AVR_ATmega128__

#define RSCS_SPI_PORTX	(PORTB)
#define RSCS_SPI_DDRX	(DDRB)
#define RSCS_SPI_MISO	(3)
#define RSCS_SPI_MOSI	(2)
#define RSCS_SPI_SCK	(1)
#define RSCS_SPI_SS		(0)

#endif

// ========================================================
// Настройки I2C - драйвера TWI контроллера атмеги
// (пока поддерживается только режим мастера)
// ========================================================
// Таймаут на I2C формируется исходя из двух параметров: длительность такта ожидания и количество этих тактов.
// Когда I2C модуль получает команду на создание какого-либо события
// его драйвер ожидает (delay) один такт ожидания, а затем проверяет -
// было ли нужное событие таки создано?. Если да - драйвер сообщает об этом пользователю.
// Если нет - модуль уходит на ожидание на еще один такт и процесс повторяется пока не будет
// исчерпано заданное количество тактов ожидания
// Длительность такта ожидания Таймаута на I2C операции (в микросекундах)
#define RSCS_I2C_TIMEOUT_US		(100)
// Количетво тактов ожидания таймаута на I2C операции
#define RSCS_I2C_TIMEOUT_CYCLES	(5)


// ========================================================
// Настройки ONE_WIRE - модуля взаимодействия по ONEWIRE шине
// ========================================================
// Регистр PORT на котором расположен пин onewire шины
#define RSCS_ONEWIRE_REG_PORT (PORTA)
// Регистр PIN на котором расположен пин onewire шины
#define RSCS_ONEWIRE_REG_PIN  (PINA)
// Регистр DDR на котором расположен пин onewire шины
#define RSCS_ONEWIRE_REG_DDR  (DDRA)
// Битовая маска, задающая тот самый пин на порту
#define RSCS_ONEWIRE_PIN_MASK (1 << 0)



// ========================================================
// Настройки модуля SD - модуля работы с SD картами
// ========================================================
// Частота SPI модуля SD карты, которую он устанавливает при вызове rscs_sd_spi_setup
#define RSCS_SDCARD_SPI_CLK_SLOW (16000)
// Частота SPI модуля SD карты, которую он устанавливает при вызове rscs_sd_spi_setup_slow
#define RSCS_SDCARD_SPI_CLK_FAST (400)



// ========================================================
// Настройки модуля SERVO - модуля управления сервомашинками
// ========================================================
// модуль SERVO всегда использует таймер 1. Если это таймер занят под другие задачи, использовать модуль SERVO не получится
// Настройки зависят от микроконтроллера - это пины, на которые выведены каналы захвата-сравнения таймера 1
#ifdef __AVR_ATmega328P__

//#define RSCS_SERVO_TIM1_A_REG_DDR	(DDRB)
//#define RSCS_SERVO_TIM1_A_PIN_MASK	(1 << 1)

//#define RSCS_SERVO_TIM1_B_REG_DDR	(DDRB)
//#define RSCS_SERVO_TIM1_B_PIN_MASK	(1 << 2)

#elif defined __AVR_ATmega128__
// TODO: Посмотреть в даташите
#endif


// ========================================================
// Настройки модуля UART
// ========================================================
// Использовать ли буферизацию
#define RSCS_UART_USEBUFFERS // Добавить код для поддержки циклических буферов в UART
#define RSCS_UART_BUFSIZE_RX 50 // размер буфера на RX
#define RSCS_UART_BUFSIZE_TX 50 // размер буфера на TX


// ========================================================
// Настройки модуля BMP280
// ========================================================
//Выбор интерфейса обмена (SPI или I2C)
#define RSCS_BMP280_IF SPI

#if RSCS_BMP280_IF == SPI
// Настройки пина CS
#define RSCS_BMP280_CSDDR DDRB
#define RSCS_BMP280_CSPORT PORTB
#define RSCS_BMP280_CSPIN 4

#endif //RSCS_BMP280_IF == SPI

#endif /* CONFIG_H_ */
