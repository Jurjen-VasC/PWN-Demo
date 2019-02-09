# Raspberry Pi

For this demo setup we've choosen to use a Raspberry Pi as a central control unit.

The Raspberry Pi is a version 3 device. This is great because it allows us to run the software in containers.

## Setting up the Raspberry Pi

First download and install the latest version of Hasbian on a SD card.  Hasbian is a special version of Raspbian that includes Home Assistent.
Install the 32 bit version which is the recommended version at this time.

### Getting the default files from Github

Development is done with version control from Github. Clone the project in the home folder of the user 'pi'.

```
cd
git clone https://github.com/mverleun/PWN-Demo.git
```

### Install PlatformIO

PlatformIO is used to build the firmware. Open a terminal session and type the following commands:

```
sudo python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/develop/scripts/get-platformio.py)"
```

### Install esphome.io

[Esphome.io](https://esphome.io/) is the new name of firmware that's easy to use. It requires configuration but programming skills are not needed.
Installing is done according to the information on the [Getting started](https://esphome.io/guides/getting_started_command_line.html) page, which says to enter the following command:

``` bash
sudo pip install esphomeyaml
```

### Install Mosquitto

Let's install the version of Mosquitto that's bundled with Raspbian

``` bash
sudo apt update
sudo apt install mosquitto
```

This will automatically start the MQTT broker.

Next step is to add the mqtt settings to the configuration of Home Assistent. Because we don't have the propper permission use `sudo nano /home/homeassistant/.homeassistant/configuration.yaml` to open the file in an editor.

Add the following configuration snippet between the `tts:` and `cloud:` section:

```
# MQTT Config
mqtt:
  broker: 127.0.0.1
  port: 1883
  client_id: homeassistent
  discovery: true
  discovery_prefix: homeassistant
```
These settings will instruct Home Assistent to use the MQTT broker on the local system. Esphome firmware can use the topic `homeassistant/#` to announce devices which will then be auto-discovered.
