# Interrupt Example
The SX126x supports the following interrupts.   
This example demonstrates how to use RxDone.   
__Bit 3 cannot be used with LoRa.__   

|Bit|IRQ|Description|Modulation|
|:-:|:-:|:-:|:-:|
|0|TxDone|Packet transmission completed|All|
|1|RxDone|Packet received|All|
|2|PreambleDetected|Preamble detected|All|
|3|SyncWordValid|Valid sync word detected|FSK|
|4|HeaderValid|Valid LoRa header received|LoRa|
|5|HeaderErr|LoRa header CRC error|LoRa|
|6|CrcErr|Wrong CRC received|All|
|7|CadDone|Channel activity detection finished|LoRa|
|8|CadDetected|Channel activity detected|LoRa|
|9|Timeout|Rx or Tx timeout|All|

# Wiring
Add a wire to DIO1.
|Ra-01S/SH||UNO|MEGA|ESP8266|
|:-:|:-:|:-:|:-:|:-:|
|VCC|--|3.3V(*1)|3.3V|3.3V|
|GND|--|GND|GND|GND|
|SCK|--|D13(*2)|D52(*2)|IO14|
|MISO|--|D12|D50|IO12|
|MOSI|--|D11(*2)|D51(*2)|IO13|
|NSS|--|D5(*2)|D5(*2)|IO2|
|RST|--|D6(*2)|D6(*2)|IO0|
|BUSY|--|D7(*2)|D7(*2)|IO16|
|DIO1|--|D3(*2)|D3(*2)|IO3|
|TXEN|--|N/C|N/C|N/C|
|RXEN|--|N/C|N/C|N/C|

(*1)   
UNO's 3.3V output can only supply 50mA.   
In addition, the output current capacity of UNO-compatible devices is smaller than that of official products.   
__So this module may not work normally when supplied from the on-board 3v3.__   

(*2)   
SX126x is not 5V tolerant.   
You need level shift from 5V to 3.3V.   
I used [this](https://www.ti.com/lit/ds/symlink/txs0108e.pdf?ts=1647593549503) for a level shift.   

# How to use interrupt
irqMask sets the interrupt bits you need. You can set multiple bits.   
dioXMask sets the interrupt bits to notify DIOX. You can set multiple bits.   
The following setting enables all interrupts:   
When SX126X_IRQ_TX_DONE occurs, DIO1 turns ON.   
When SX126X_IRQ_RX_DONE occurs, DIO2 turns ON.   
When SX126X_IRQ_TIMEOUT occurs, DIO3 turns ON.   
```
    uint16_t irqMask = SX126X_IRQ_ALL;
    uint16_t dio1Mask = SX126X_IRQ_TX_DONE;
    uint16_t dio2Mask = SX126X_IRQ_RX_DONE;;
    uint16_t dio3Mask = SX126X_IRQ_TIMEOUT;
    SetDioIrqParams(irqMask, dio1Mask, dio2Mask, dio3Mask);
```

This will give the same result as above.   
```
    uint16_t irqMask = SX126X_IRQ_TX_DONE | SX126X_IRQ_RX_DONE | SX126X_IRQ_TIMEOUT;
    uint16_t dio1Mask = SX126X_IRQ_TX_DONE;
    uint16_t dio2Mask = SX126X_IRQ_RX_DONE;
    uint16_t dio3Mask = SX126X_IRQ_TIMEOUT;
    SetDioIrqParams(irqMask, dio1Mask, dio2Mask, dio3Mask);
```

The following setting enables TxDone/RxDone/Timeout interrupts and triggers them all to DIO1.   
```
    uint16_t irqMask = SX126X_IRQ_TX_DONE | SX126X_IRQ_RX_DONE | SX126X_IRQ_TIMEOUT;
    uint16_t dio1Mask = SX126X_IRQ_TX_DONE | SX126X_IRQ_RX_DONE | SX126X_IRQ_TIMEOUT;
    uint16_t dio2Mask = SX126X_IRQ_NONE;
    uint16_t dio3Mask = SX126X_IRQ_NONE;
    SetDioIrqParams(irqMask, dio1Mask, dio2Mask, dio3Mask);
```

