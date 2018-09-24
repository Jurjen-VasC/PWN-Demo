# Raspberry Pi

For this demo setup we've choosen to use a Raspberry Pi as a central control unit.

The Raspberry Pi is a version 3 device. This is great because it allows us to run the software in containers.

## Setting up the Raspberry Pi

First download and install the latest version of Raspbian on a SD card. 
The next step is to install Docker.

### Getting the default files from Github

Development is done with version control from Github. Clone the project in the home folder of the user 'pi'.

```
cd
git clone https://github.com/mverleun/PWN-Demo.git
```

### Install PlatformIO

PlatformIO is used to build the firmware. Open a terminal session and type the following commands:

```
python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/develop/scripts/get-platformio.py)"
sudo mv ~/.local/bin/platformio /usr/local/bin
```

### Install Docker
Follow the steps as described here: [Install Docker](https://docs.docker.com/install/linux/docker-ce/debian/). Make sure to use the instruction for `armhf` where apropiate.

### Install docker-compose
`docker-compose` is a great command to make working with containers easier.

Install it using `pip`. Enter the following command:

``` bash
pip install docker-compose
sudo mv ~/.local/bin/docker-compose /usr/local/bin
```

Create a directory `/docker` which will be used to manage the containers:

``` bash
sudo mkdir /docker
sudo chown pi /docker
```

### Install Mosquitto

Inside the `/docker` directory create a subdirectory for the Mosquitto container.

``` bash
cd /docker
mkdir mosquitto
cd mosquitto
```

Use your favorite editor to create a file named `docker-compose.yml` in this directory with the following content:

``` 
version: '3'
services:
  mosquitto:
    image: panuwitp/mosquitto-arm

    container_name: mosquitto
    hostname: mosquitto.local

    ports:
     - "1883:1883"
     - "8883:8883"
     - "9001:9001"

    volumes:
     - config:/mosquitto/config/
     - logs:/mosquitto/log/
     - data:/mosquitto/data/
     - /etc/localtime:/etc/localtime:ro
     - /etc/timezone:/etc/timezone:ro

    restart: unless-stopped
volumes:
  config:
  logs:
  data:
```
 
 Once you've completed this file start the container with the command:
 
```
docker-compose up -d
```

This will start a container with settings from a default config file.
If you want to change the config use your favorite editor to modify the contents of the following file:
`/var/lib/docker/volumes/mosquitto_config/_data/mosquitto.conf`
