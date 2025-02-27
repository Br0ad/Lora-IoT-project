# LoraWAN-IoT-project
2 RP2040 RFM95 feathers with one connected to a DHT11.

<details>
<summary>Dependencies</summary>
  
## Adafruit Feather:
- [2 Adafruit RFM95 feathers running circuit python](https://learn.adafruit.com/feather-rp2040-rfm95/overview)

## Node Red:
- [Node Red](https://nodered.org/)
- [node-red-contrib-discord-advanced](https://github.com/Markoudstaal/node-red-contrib-discord-advanced)
- [node-red-node-serialport](https://github.com/node-red/node-red-nodes)

## Arduino:
- [IDE](https://www.arduino.cc/en/software)
- [RadioHead](https://docs.arduino.cc/libraries/radiohead/)
- [DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library)

</details>

<details>
<summary>Running</summary>

1. Setup Feathers and IDE.
2. Flash RX and TX to Feathers with Arduino IDE.
3. Import flows.json to Node Red and add bot token to any nodes with a red triangle.
4. Wire TX Feather to DHT11 or other sensor.
5. Plug in Feathers and correct COM/ACM ports in serial in if needed.
6. Click Deploy wait for output in debug console and if so click the button next to inject.
7. Done.

</details>

## Credits
**Xendyos**

**Semper**

**Litho**
