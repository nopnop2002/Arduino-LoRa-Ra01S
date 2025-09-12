
#include <Ra01S.h>

#define INTERRUPT_GPIO                              3         // Digital pin 3 for external interrupt 0

//#define RF_FREQUENCY                                433000000 // Hz  center frequency
//#define RF_FREQUENCY                                866000000 // Hz  center frequency
#define RF_FREQUENCY                                915000000 // Hz  center frequency
#define TX_OUTPUT_POWER                             22        // dBm tx output power
#define LORA_BANDWIDTH                              4         // bandwidth
                                                              // 2: 31.25Khz
                                                              // 3: 62.5Khz
                                                              // 4: 125Khz
                                                              // 5: 250KHZ
                                                              // 6: 500Khz 
#define LORA_SPREADING_FACTOR                       7         // spreading factor [SF5..SF12]
#define LORA_CODINGRATE                             1         // [1: 4/5,
                                                              //  2: 4/6,
                                                              //  3: 4/7,
                                                              //  4: 4/8]

#define LORA_PREAMBLE_LENGTH                        8         // Same for Tx and Rx
#define LORA_PAYLOADLENGTH                          0         // 0: Variable length packet (explicit header)
                                                              // 1..255  Fixed length packet (implicit header)


                                                             
#if 1
/*
 * for ATmega328/2560
 * VCC    3V3/3V3
 * GND    GND/GND
 * SCK    13/52
 * MISO   12/50
 * MOSI   11/51
 * NSS     5/5
 * RST     6/6
 * BUSY    7/7
 * DIO1    3/3
 */

SX126x  lora(5,               //Port-Pin Output: SPI select
             6,               //Port-Pin Output: Reset 
             7                //Port-Pin Input:  Busy
             );
#endif // ATmega328/2560

#if 0
/*
 * for ESP8266
 * VCC    3V3
 * GND    GND
 * SCK    GPIO14
 * MISO   GPIO12
 * MOSI   GPIO13
 * NSS    GPIO2
 * RST    GPIO0
 * BUSY   GPIO16
 * DIO1   GPIO3
 */
 
SX126x  lora(2,                 //Port-Pin Output: SPI select
             0,                 //Port-Pin Output: Reset 
             16                 //Port-Pin Input:  Busy
             );
#endif // ESP8266

void gpio_isr() {
  Serial.println("Interrupt");
}

void setup() 
{
  delay(1000);
  Serial.begin(115200);

  // Initialize the interrupt pin as an input with internal pull-up resistor
  pinMode(INTERRUPT_GPIO, INPUT_PULLUP);
  // Attach the interrupt to the specified pin
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_GPIO), gpio_isr, RISING);
  
  //lora.DebugPrint(true);

  int16_t ret = lora.begin(RF_FREQUENCY,              //frequency in Hz
                           TX_OUTPUT_POWER);          //tx power in dBm
  if (ret != ERR_NONE) while(1) {delay(1);}

  lora.LoRaConfig(LORA_SPREADING_FACTOR, 
                  LORA_BANDWIDTH, 
                  LORA_CODINGRATE, 
                  LORA_PREAMBLE_LENGTH, 
                  LORA_PAYLOADLENGTH, 
                  true,               //crcOn  
                  false);             //invertIrq

  // Set up an interrupt for SPI transactions
  uint16_t irqMask = SX126X_IRQ_RX_DONE;
  uint16_t dio1Mask = SX126X_IRQ_RX_DONE;
  uint16_t dio2Mask = 0;
  uint16_t dio3Mask = 0;
  lora.SetDioIrqParams(irqMask, dio1Mask, dio2Mask, dio3Mask);
}

void loop() 
{
  uint8_t rxData[255];
  uint8_t rxLen = lora.Receive(rxData, 255);
  if ( rxLen > 0 )
  { 
    Serial.print("Receive rxLen:");
    Serial.println(rxLen);
    for(int i=0;i< rxLen;i++) {
      Serial.print(rxData[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
    for(int i=0;i< rxLen;i++) {
      if (rxData[i] > 0x19 && rxData[i] < 0x7F) {
        char myChar = rxData[i];
        Serial.print(myChar);
      } else {
        Serial.print("?");
      }
    }
    Serial.println();

    int8_t rssi, snr;
    lora.GetPacketStatus(&rssi, &snr);
    Serial.print("rssi: ");
    Serial.print(rssi, DEC);
    Serial.println(" dBm");
    Serial.print("snr: ");
    Serial.print(snr, DEC);
    Serial.println(" dB");
  }
  delay(1);
}
