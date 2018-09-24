# Wemos D1 mini with Pulse Counter

This firmware is meant to be used on a Wemos D1 Mini with a pulse device It's part of the [IoT Kit for education](https://www.iot-kit.nl) project.

I'm using it to count pulses on a watermeter using a inductive sensor. Each pulse represents 1 liter of water going through the meter.


## Connecting the hardware
Connect the hardware as not difficult, but requites a bit of DIY.
Pulses are counted on both D4 and D5. Actually we've got two counters built-in.

When using a "KSOL DC6-36V 300mA NPN GEEN 3-wire 4mm Tubular Inductieve Proximity Sensor Switch" you should use additional electronics to get the proper voltage available for the sensor and to protect the Wemos input.


| Sensor |  Function |
| --- | ---|
| Brown |+6V - +36V |
| Blue | GND |
| Black | Pulse |

D4 is for pulsecounter 1, D5 for pulsecounter 2.

Pulses are counted interrupt driven, on the rising edge of a pulse.
Once a minute the counted values are published. If publishing fails the counters are kept
and added to the next attempt.
This means that you don't loose counts, but you're interval reporting could be off.

## MQTT
If all is configured well you should receive measurements on the following topics:

```
<base_topic>/<device_id>/pulse/pulse
```

Temperature and humidity are reported as floating point values.
The JSON output contains the name of the sensor, the name of the metric reported and the value of the measurement.
