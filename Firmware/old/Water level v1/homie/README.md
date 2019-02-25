# Wemos D1 controller

This firmware is meant to be used on a Wemos D1. It controls a valve and a pump and it reports the level of water inside the tank.

The sensor used to report the waterlevel is a HC-SR04, the valve and the pump are controlled via relays.

## Connecting the hardware
Connect the hardware as follows:

| HC-SR04 |  Wemos D1 mini |
| --- | ---|
| VCC |+5V (!) |
| GND | GND |
| Trig | D6 |
| Echo | D7 |

| Relay shield | Wemos D1 mini | Function |
| --- | --- | --- |
| 1   | D1  | Valve |
| 2   | D2  | Pump |
| GND | GND |

## Compiling and uploading
This firmware embeds the ui_bundle to make the initial configuration easier.
In order to upload it into the SPIFFS filesystem you have to build the firmware first and then open up a terminal.

In the terminal enter the command `pio run -t uploadfs` to upload the contents of the /data directory.
Once the upload has completed upload the firmware as usual or type the command `pio run -t upload`.

It is also possible to include a file `config.json` in the directorie /data/homie with preconfigured settings before you upload the files to SPIFFS e.g.:
```
{
  "wifi":{
    "ssid":"<SSID>",
    "password": "<PASSWWORD>"
    },
  "mqtt":{
    "host":"mqtt.example.com",
    "port":1883,
    "base_topic":"devices/",
    "username": "<mqtt username>",
    "password": "<mqtt password>",
    "auth":true
  },
  "name":"Sensor X",
  "ota":{
    "enabled":true
    },
  "device_id":"wemos-x"
}
```
For MQTT you can ommit `username`, `password` and `auth` if your MQTT server doesn't requite authentication.

If you ommit `base_topic` it will default to the value "homie"

## MQTT
If all is configured well you should receive measurements on the following topics:
```
<base_topic>/<device_id>/distance/distance
<base_topic>/<device_id>/distance/json
```
The json output contains the name of the sensor, the name of the metric reported and the value of the measurement.
