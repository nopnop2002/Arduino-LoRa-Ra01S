# Ping-Pong Example   
Send data from primary to secondary.   
In the secondary, the characters are converted and sent back.   

- Arduino is Primary   
When using Arduino as a secondary, use Ra01S-Pong.   
```
+-----------+           +-----------+            +-----------+           +-----------+
|           |           |           |            |           |           |           |
|  Primary  |===(SPI)==>|  SX126x   |---(LoRa)-->|  SX126x   |===(SPI)==>| Secondary |
|  Arduino  |           |           |            |           |           |           |
|           |           |           |            |           |           |           |
|           |<==(SPI)===|           |<--(LoRa)---|           |<==(SPI)===|           |
|           |           |           |            |           |           |           |
+-----------+           +-----------+            +-----------+           +-----------+
```

- Arduino is Secondary   
When using Arduino as a primary, use Ra01S-Ping.   

```
+-----------+           +-----------+            +-----------+           +-----------+
|           |           |           |            |           |           |           |
|  Primary  |===(SPI)==>|  SX126x   |---(LoRa)-->|  SX126x   |===(SPI)==>| Secondary |
|           |           |           |            |           |           |  Arduino  |
|           |           |           |            |           |           |           |
|           |<==(SPI)===|           |<--(LoRa)---|           |<==(SPI)===|           |
|           |           |           |            |           |           |           |
+-----------+           +-----------+            +-----------+           +-----------+
```

