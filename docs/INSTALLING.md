# Installing the Demo

The Demo solution consists of several components. Each component will be discussed below to maximize the chance of a succesful implementation.

## WiFi

WiFi is needed to allow the controllers to communicate with Rasperberry Pi. The Raspberry Pi is connecting via WiFi as well.

The SSID of the WiFi network is `PWN-IoT` and the passphrase `DrinkWater`.

## Raspberry Pi

When installing the Raspberry Pi you can decide to run the OS from an external USB drive instead of the built-in SD controller. This requires certain steps and not all USB drives will work. You don't have to boot from USB and can skip the next step if you want.

### USB Boot

If you want to boot from USB follow the steps
[here](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bootmodes/msd.md).
In order to get it to work I needed an USB **3** device. I also had to
disconnect all other USB devices, such as mouse and keyboard.

### Downloading Raspian

This document assumes that Raspbian Stretch Full version will be used. This version is the biggest one and also contains a GUI and recommend tools.

Download a copy from [RaspberryPi.org](https://www.raspberrypi.org/downloads/raspbian/) and write it to either a USB3 thumb drive or a SD Card.

In order to do so you can follow the official installation procedure described [here](https://www.raspberrypi.org/documentation/installation/installing-images/README.md).

### Network configuration

It is possible to configure the WiFi *before* booting the Raspberry Pi from the newly baked image. This is called a *headless* (No monitor, mouse and keyboard) configuration. The steps are described [here](https://www.raspberrypi.org/documentation/configuration/wireless/headless.md).

This is an optional step. You can also connect via ethernet or connect to the WiFi manually.

Once you've installed the software boot the Raspberry Pi. Don't be surprised if the Raspberry Pi reboots, this is normal for a first time installation.

When the system is done booting you can login in as the user `pi` with password `raspbian`. 

This is a *very* well known combination of a username and password and should be changed immediatelly.

If not connected to the network (Ethernet or WiFi) you'll have to connect now. The next steps assume that there is connectivity to the internet.

### Installing Ansible

Ansible is one of the tools often used to configure systems. This can be done remotely or locally. 
Ansible has a configuration language that is used to describe the desired state of items.
Once Ansible is running it will compare the state of the system with the desired state and resolve any differences that might be present.

It is perfect for our purpose and the so called playbooks used to prepare this system are available through Github which we will use later on.

Right now we need to install Ansible manually...

Open a terminal session and enter the following commands:

```bash
sudo apt update
sudo apt install -y ansible
```

This will take a couple of minutes

#### Github

The next step is to get some config files from github. Log in as the user 'pi' with password 'raspberry' on the console of the Raspberry pi. The type the following commands:

```bash
cd
git clone https://github.com/mverleun/PWN-Demo.git
```

This will clone the repository to the Raspberry Pi. This repository contains some config files and the firmware that can be used later.

## Ansible

Ansible is used to automate the provisioning of the Raspberry Pi as much as possible by applying 'playbooks'.
It is one of the most popular tools to do this.

By default the Raspberry Pi comes with a rather old version of ansible. The first playbook will update ansible itself.

The second playbook will install Docker. When it is done a reboot is required and since ansible runs locally it is not (yet) possible to automatically continue. It also changes the network settings.

That's why there is a third playbook. This playbook will install Docker images and start some containers. Where applicable the containers will have a default configuration.
This playbook will also install some additional software, like esphome and home-assistant.

After completing all the playbooks the Raspberry Pi has a fixed ip address and is ready to be used.

#### Step 1, Updating ansible

When logged in to the Raspberry Pi as user 'pi' open a terminal and type the following commands:

```bash
cd ~/PWN-Demo
ansible-playbook -u pi ansible.yml
```

This will update ansible to a more recent version. When ansible is updated enter the following commands:

```bash
cd ~/PWN-Demo
ansible-playbook -u pi docker.yml && reboot
```

This will install Docker and reboot the Pi. Without rebooting the next steps will fail!

The final step is to run:
```bash
cd ~/PWN-Demo
ansible-playbook -u pi software.yml
```

### Mosquitto

A very important container that runs is Mosquitto. Mosquitto is the MQTT broker. Almost all communication between the Raspberry Pi and the sensors/actuators are going via this mqtt broker.

When devices need to be configured to use mqtt you will need the following server settings:

```bash
host: 192.168.42.254
port: 1883
```

### Node RED

This GUI can be used to create workflows. By default it provides a dashboard for the demo setup, but it can be extend easily.

To configure flows open a web browser and connect to `http://192.168.42.254:1880`. The dashboard is available via `http://192.168.42.254:1880/ui`.

## Controllers

The controllers used are all Wemos D1 mini controllers.

![Wemos D1](images/Wemos-D1.jpg)

They are selected because of their built in WiFi and they are easy to connect to a PC using the builtin USB port.

Each controller has a number and a specific function. Controller 1, 3 and 5 measure the level of the water inside the tank and they also control the valves and pumps.

Controller 2, 4 and 6 measure the flow.

This can only be done if the proper sensors and/or actuators are connected.

In order to control the pumps and valves a relay board is used. The water level is measured using a HC-SR04 ultrasonic sensor.

The flow is measured using a pulse counter.

All the firmware is based on the [ESPHome](https://esphome.io) project. This allows us to create firmware without requiring real programming skills.

### Initial flashing

In order to get the controllers working you'll need a micro usb cable connected to the Raspberry Pi and the controller. Once you've got them working you can update them OTA (Over The Air) as long as they are connected to the WiFi.

Navigate to the directory containing the firmware: `cd ~/PWN-Demo/Firmware`.
First compile the software for controller 1. The configuration is inside a file called `controller_1.yaml`. Compiling it is done by entering `esphome controller_1.yaml compile` The first controller will take a long time, the toolkit required is downloaded and installed.

Notice that a directory is created named `controller_1`. Inside are the files needed to build the firmware.

Once you've build the firmware you can upload it with the command `esphome controller_1.yaml upload`.
The first time you upload the firmware you need to use a USB cable to connect the controller to the Raspberry Pi.

Al subsequent uploads can be done remotely as long as the Wifi network is available.

It is important to make sure that each controller has it's own firmware since the name of the controller is embedded in the firmware.

### Updating firmware

Whenever you change some settings of the firware you can update it over the air.
There are some restrictions to this process:

- The controller has to be connected to the same network as the Raspberry Pi.

- The name of the controller can't change. This name is retrieved from the yaml files and is used to connect to the right controller.

#### Connecting the hardware

##### Level sensor

The level is measured using a HC-SR04 device.

![HC-SR04](images/HC-SR04.jpg)

| HC-SR04 | Wemos D1 mini |
|---------|---------------|
| VCC     | +5V (!)       |
| GND     | GND           |
| Trig    | D6            |
| Echo    | D7            |

##### Relay board

The pump and valve are controlled using the following relayboard:

![4 Channel Relay](images/4-channel-relay.jpg)

| Relay shield | Wemos D1 mini | Function |
|--------------|---------------|----------|
| VCC          | 3V3           |          |
| IN 1, IN 2   | D1            | Valve    |
| IN 3         | D2            | Pump     |
| GND          | GND           |          |

Note that both IN1 and IN2 are connected to D1. This is because we need two relays with the valve. Two relays allows us to reverse polarity, which in turn will change the direction of the motor controlling the valve, resulting in a open or close motion.

##### Flow meter

The flow is measured using a YF-S201C device. 
![YF-S201C](images/YF-S201C.jpg)

This is a meter that generates pulses. By counting the pulses we know the
flow.

| Flow meter | Wemos D1 mini |
|------------|---------------|
| Red        | +5V (!)       |
| Yellow     | D4            |
| Black      | GND           |
