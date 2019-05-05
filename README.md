# tiny5351
A minimal Si5351 library for avr and Arduino (~1kb)

- simple library to use with avr / arduino to set frequency on Si5351 from silabs
- uses a mix of assembly and c to achieve the register settings
- takes less than 1000 bytes, so  useful with attiny13 
- If you want to use Arduino platform, just install a microcore for attiny with link time optimisation
- It use a bitbang i2c, So use PB1 (SCL) & PB2 (SDA)on attiny13 (can be changed to any pin in i2cmaster.S file in the library)
- There is an example sketch (tinypll - takes around 960 bytes of flash), just upload via an isp programmer (usbasp) and generates a signal at 10MHZ and can be adjusted a few khz upward by applyng a voltage (0-vcc) on ADC3 of the attiny13

