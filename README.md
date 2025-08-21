# STM32F103C8T6 driver (HUB75 display and TFmini Plus LiDAR integration)
This project controls a 64x64 RGB LED matrix panel with a HUB75 interface using an STM32F103C8T6 ("Blue Pill") and TFmini Plus LiDAR in order to measure and display velocity of moving objects.


## Featrues
- Manual control of CLK (Clock), OE (Output Enable), LAT (Latch) and address lines (A, B, C, D)
- Supports drawing single pixels as well as 3-bit colored bitmaps
- Optimized GPIO access using BSRR/BRR registers
- Framebuffer-based rendering
- Optional TFmini Plus LiDAR integration (for displaying real-time measured speed)


## How It Works
- The framebuffer is a `uint8_t framebuffer[64][64][3]` structure storing RGB values per pixel.
- Pixel values are manually shifted to the panel using GPIO operations in each row.
- CLK pulses are generated using TIM3 but GPIO output is written manually before each pulse.
- After each row:
  - RGB data is latched
  - LAT and OE signals are pulsed
  - Address lines are updated


## Hardware Requirements
- STM32F103C8T6 ("Blue Pill")
- RGB HUB75 LED panel (64x64)
- TFmini Plus LiDAR
- 5V power supply (3A recommended)
- ST-Link V2 or USB-UART for flashing 


## Pin Configuration (Example)
| Signal | STM32 Pin | GPIO Port |
|:-------|:----------|:----------|
| R1     | PA0       | GPIOA     |
| G1     | PA1       | GPIOA     |
| B1     | PA2       | GPIOA     |
| R2     | PA3       | GPIOA     |
| G2     | PA4       | GPIOA     |
| B2     | PA5       | GPIOA     |
| CLK    | PA15      | GPIOA     |
| OE     | PB0       | GPIOB     |
| D      | PB3       | GPIOB     |
| C      | PB4       | GPIOB     |
| B      | PB5       | GPIOB     |
| A      | PB6       | GPIOB     |
| LAT    | PB7       | GPIOB     |


*Remember to adjust based on your `hub75.h` definitions.*


## Project Structure
```
.
├── HUB75_D
│   ├── Core/                       # Main application code (user code + auto-generated)
│   │   ├── Inc/                    # User header files (.h) with necessary declarations and definitions
│   │   ├── Src/                    # User source files (.c) with main logic and functions
│   │   ├── Startup/                # Startup code and vector table (startup_stm32f103xx.s)
│   │
│   ├── Drivers/                    # MCU-specific low-level driver files
│   │   ├── CMSIS/                  # Cortex-M CMSIS headers and core access
│   │   ├── STM32F1xx_HAL_Driver/   # STM32 HAL libraries for the F1 family
│   │
│   ├── .mxproject                  # STM32CubeMX project metadata (for toolchain integration)
│   ├── HUB75_D.ioc                 # STM32CubeMX configuration file (pinout, clocks, peripherals)
│   ├── STM32F103C8TX_FLASH.ld      # Linker script (defines memory layout)
│   
├── README.md
```


## Basic Examples

### Displaying a pixel
```c
clear_framebuffer();        // Ensure the framebuffer is empty
set_pixel(10, 20, 1, 0, 0); // Set red pixel in x=10 y=20 position
draw_framebuffer();         // Draw pixel on the screen
```

### Displaying a bitmap
```c
clear_framebuffer();                // Ensure the framebuffer is empty
draw_rgb565_bitmap(my_own_bitmap);  // Draw given bitmap on the screen
```

### Displaying speed
```c
while (1) {
    process_speed();
}
```

#### Important Note
`draw_framebuffer()` method is desinged to be used in main `while()` loop and `draw_rgb565_bitmap()` outside of it.
Every already implemented drawing function that should be used inside of main loop has a note on it, however while implementing your own functions remember that display refresh can be and is performed during timer interruption (automatically).


## Example Photos
- Displaying current velocity
  ![Current velocity](https://github.com/alexr36/STM32F103C8T6-driver-for-HUB75-display/blob/8e6d8838c16f282d87e6c73454635641f9883fe9/photos/velocity.png)
- Displaying a traffic sign bitmap
  ![STOP traffic sign](https://github.com/alexr36/STM32F103C8T6-driver-for-HUB75-display/blob/8e6d8838c16f282d87e6c73454635641f9883fe9/photos/traffic_sign_bitmap.png)
