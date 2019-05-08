# Soufflerie-course-en-cours

## Logiciels
| Arduino |  Fritzing |
| :-----: | :------: |
| ![](/icone/Arduino.png)  ![]| (/icone/Fritzing.png) |

## Composants
| Arduino | Adafruit | DFRobot | SeeedStudio |
| :-----: | :------: | :-----: | :---------: 
| ![](/icone/Arduino.png) | ![](/icone/Adafruit.png)| ![](/icone/DFRobot.png) | ![](/icone/Seeed_Studio.png) |

### Arduino
| Arduino Mega  |
| :-------------: |
| ![](/composants/Arduino%20Mega.jpg) |

### Shield
| Shield Grove Mega |
| :-------------: |
| ![](/composants/SeeedStudio/Shield_Grove_Mega.jpg) |
 
### SeeedStudio
| BME280 | BMP280 | MCP9808 | Magnetique |
| :-------------: | :-------------: | :-------------: | :-------------: |
| ![](/composants/SeeedStudio/Grove_BME280.jpg) | ![](/composants/SeeedStudio/Grove_BMP280.jpg) | ![](/composants/SeeedStudio/Grove_MCP9808.JPG) | ![](/composants/SeeedStudio/Grove_Magnetic_switch.jpg) |

| Keypad | Cable Grove | NC |  NC |
| :-------------: | :-------------: | :-------------: | :-------------: |
| ![](/composants/SeeedStudio/Grove_keypad12.jpg) | ![](/composants/SeeedStudio/Grove_Cable.jpg) | NC | NC |

### Adafruit
| TFT 2.8' |
| :-------------: |
| ![](/composants/Adafruit/Adafruit_2.8_TFT_Touch_Shield.jpg) |

### DFRobot
| Capteur Force |
| :-------------: |
| ![](/composants/DFRobot/DFRobot_Weight_Sensor_Module.jpg) |

## Branchement
| Fritzing |
| :-------------: |
| ![](/icone/Fritzing.png) |

![](/fritzing/Untitled_Sketch.png)

### Shield
* Shield Grove Mega

### Analogique
* A0 : Keypad Ligne 3
* A1 : Keypad Ligne 2
* A2 : Keypad Colonne 0
* A3 : Keypad Ligne 1
* A4 : Keypad NC
* A5 : Keypad Ligne 0
* A6 : Keypad Colonne 2
* A7 : Keypad Colonne 1
* A8 : FORCE DOUT
* A9 : FORCE SCK

### Digital
* D0 : RX rs232 non utilise
* D1 : TX rs232 non utilise
* D2 : NC
* D3 : NC
* D4 : Shield TFT
* D5 : NC
* D6 : Magnetique
* D7 : NC
* D8 : Shield TFT
* D9 : Shield TFT
* D10 : Shield TFT
* D11 : Shield TFT
* D12 : Shield TFT
* D13 : Shield TFT

### I2C
* SDA : BMP280 , MCP9808
* SCL : BMP280 , MCP9808

### Alimentation
* Vin : NC
* GND : NC
* 5V : NC
* 3.3V : NC
* Vref : NC

### Divers 
* Ioref : NC
* Reset : NC