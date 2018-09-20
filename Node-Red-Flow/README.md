# Node Red

Just like Mosquitto, Node Red is running in a container as well. Installing Node Red is just as easy as creating a `docker-compose` file and running the container.

### Installation steps

Inside the `/docker` directory create a subdirectory for the Node RED container.

``` bash
cd /docker
mkdir node-red
cd node-red
```

Use your favorite editor to create a file named `docker-compose.yml` in this directory with the following content:

``` 
version: '3'
services:
  node-red:
    container_name: node-red
    image: nodered/node-red-docker:rpi-v8
    hostname: node-red.local

    ports:
     - "1880:1880"

    volumes:
     - data:/data
     - /etc/localtime:/etc/localtime:ro
     - /etc/timezone:/etc/timezone:ro
    cap_add:
     - NET_ADMIN

    restart: unless-stopped

volumes:
  data:
```
 
 Once you've completed this file start the container with the command:
 
```
docker-compose up -d
```

This will start a container. Persistant data is stored in a docker volume:
`/var/lib/docker/volumes/node-red_data/_data/`


