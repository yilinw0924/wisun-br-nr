#include "em_device.h"   // MUST be first!
#include "em_cmu.h"
#include "em_gpio.h"
#include "board_init.h"

// -----------------------------------------------------------------------------
// If you want board-specific pins defined here, add them later.
// Currently, UART/UART485 configs are passed via driver config structs.
// -----------------------------------------------------------------------------

void board_clock_init(void)
{
    // Enable core clocks
    CMU_ClockEnable(cmuClock_DPLL0, true);
    CMU_ClockSelectSet(cmuClock_SYSCLK, cmuSelect_HFRCODPLL);

    // Enable peripheral clocks commonly used
    CMU_ClockEnable(cmuClock_GPIO, true);

    // Enable EUSART clocks globally (instances enabled later)
    CMU_ClockEnable(cmuClock_EUSART0, true);
    CMU_ClockEnable(cmuClock_EUSART1, true);
}

void board_gpio_init(void)
{
    // Placeholder – All pins initialized by drivers later.
    // But you can force default states here if required.

    // Example: disable all pins as pull-ups
    // GPIO_PinModeSet(gpioPortA, 0, gpioModeDisabled, 0);
}

void board_init(void)
{
    board_clock_init();
    board_gpio_init();
}
