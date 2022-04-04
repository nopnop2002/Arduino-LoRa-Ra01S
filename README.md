# Arduino-LoRa-Ra01S
This is an Arduino library for LoRa Communication using the radio transceiver chips [SX1262](https://www.semtech.com/products/wireless-rf/lora-core/sx1262) and [SX1268](https://www.semtech.com/products/wireless-rf/lora-core/sx1268).   

![ra01s_ra01sh](https://user-images.githubusercontent.com/6020549/161641357-a0fe292b-095e-440b-b8ae-24c58084a51d.JPG)


Ai-Thinker offers several LoRa modules.   
You can get these on AliExpress and eBay.   

|Model|Type|Interface/Core|Chip|Frequency|Foot-Pattern|IPEX-Antena|LoRa-WAN|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|Ra-01|Tranceiver|SPI|SX1278|410-525Mhz|SMD16|No|No|
|Ra-02|Tranceiver|SPI|SX1278|410-525Mhz|SMD16|Yes|No|
|Ra-01H|Tranceiver|SPI|SX1276|803-930Mhz|SMD16|No|No|
|Ra-01S|Tranceiver|SPI|**SX1268**|410-525Mhz|SMD16|No|No|
|Ra-01SH|Tranceiver|SPI|**SX1262**|803-930Mhz|SMD16|Yes|No|
|Ra-01SC|Tranceiver|SPI|LLCC68|410-525Mhz|SMD16|Yes|No|
|Ra-06|MCU|ARM Cortex M0+|SX1278|410-525Mhz|SMD20|Yes|No|
|Ra-07|MCU|ARM Cortex M0+|ASR6501|410-525Mhz|SMD18|No|Yes|
|Ra-07H|MCU|ARM Cortex M0+|ASR6501|803-930Mhz|SMD18|No|Yes|
|Ra-08|MCU|ARM Cortex M4|ASR6601|410-525Mhz|SMD18|No|Yes|
|Ra-08H|MCU|ARM Cortex M4|ASR6601|803-930Mhz|SMD18|No|Yes|


# Option with SX1262/1268
LoRa modules with SX1262/1268 have several options.   

- Using TCXO(Temperature-Compensated Crystal Oscillator)   
SX1262/1268 can use the TCXO.   
If the TCXO is used, the XTB pin is not connected.   
However, the 6th pin (DIO3) of the SX1262/1268 can be used to power the TCXO.   
Explanation for TXCO and antenna control is [here](https://github.com/beegee-tokyo/SX126x-Arduino).   
Ra-01S / Ra-01SH does not use TCXO.   

- Power supply modes   
SX1262/1268 has two power supply modes.   
One is that only LDO used in all modes.   
Another is that DC_DC+LDO used for STBY_XOSC,FS, RX and TX modes.   
Explanation for LDO and DCDC selection is [here](https://github.com/beegee-tokyo/SX126x-Arduino).   
Ra-01S / Ra-01SH use only LDO in all modes.

- Switching RF-Swich   
In general, use DIO2 to switch the RF-Switch.
However, some tranceiver use an external gpio to switch the RF-Switch.   
Ra-01S / Ra-01SH use DIO2 to switch the RF-Switch.   

You need to look at the schematic to set these options properly, but it's very esoteric.   
The default settings for this library are for Ra-01S / Ra-01SH.    
When using other than Ra-01S / Ra-01SH, you need to set them appropriately.   

I created this library based on [this](https://github.com/tinytronix/SX126x).   
But with this library, Ra-01S / Ra-01SH doesn't work.   

# Foot pattern
RA-0x(SMD16) has the same foot pattern as ESP12.   
Therefore, a pitch conversion PCB for ESP12 can be used.   

![ra01s-3](https://user-images.githubusercontent.com/6020549/161641874-32a79d5f-dbae-42f1-a8cd-d0787c238a06.JPG)
![ra01s-2](https://user-images.githubusercontent.com/6020549/161641421-e720a7da-4889-4bd4-b2c6-1f3a28518cf8.JPG)


# Wireing
|Ra-01S/SH||UNO|MEG|ESP8266|
|:-:|:-:|:-:|:-:|:-:|
|VCC|--|3.3V|3.3V|3.3V|
|GND|--|GND|GND|GND|
|SCK|--|D13(*1)|D52(*)|IO14|
|MISO|--|D12|D50|IO12|
|MOSI|--|D11(*1)|D51(*)|IO13|
|NSS|--|D5(*1)|D5(*)|IO2|
|RST|--|D6(*1)|D6(*)|IO0|
|BUSY|--|D7(*1)|D7(*)|IO16|

(*1)Level shift from 5V to 3.3V is required.   


# Installing
Download this repo as zip. Then in the Arduino IDE go to Sketch->Add library->add .zip library.   


# Software compatibility
This library can communicate with [RadioLib](https://github.com/jgromes/RadioLib).   
```
  // Set frequency: 866Mhz
  // Set bandwidth(BW): 125Khz
  // Set Spreading Factor(SF): 7
  // Set Error Cording Rate(CR): 4/5
  // Set SyncWord: 0x1424(Private Network)
  // Set Power: 10dBm
  // Set Preamble Length: 8
  // Configure the radio to NOT use a TCXO controlled by DIO3
  // Set regulator mode: DC-DC
  int state = radio.begin(866.0, 125.0, 7, 5, RADIOLIB_SX126X_SYNC_WORD_PRIVATE, 10, 8, 0.0, false);
```


# Limitation
- The SX126x chip implements FSK, but FSK is not supported in this library.   
- Interrupts is not supported in this library.   


# SX1262 and SX1278, SX1276 Comparison
[This](https://www.ebyte.com/en/new-view-info.aspx?id=303) will be helpful.   


# Using PlatformIO
```
$ git clone https://github.com/nopnop2002/Arduino-Ra01S

$ cd Arduino-Ra01S/example/Ra01S-TX/

$ pio init -b your_board

$ cp Ra01S-TX.ino src/

$ pio run -t upload && pio device monitor -b 115200
```

