

# Microcontroller code for a sigma-delta ADC

This is code for STM32 MCUs derived from this microchip app note https://ww1.microchip.com/downloads/en/AppNotes/00700a.pdf

After the initial implementation, the code has been severely refactored to allow unit testing.



## About testing

The project has two build configurations, the normal Release/Debug and another to build and test locally (called AllTests).

The testing emulates the analog hardware and allow to test the sigma-delta algorithm locally without the associated hardware.

The next step is to integrate this configuration into a build environment, which will imply create a build environment 
over a small linux Docker (alpine).


