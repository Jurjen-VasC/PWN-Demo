Home Assistant
==============

An Ansible Role that installs [Home Assistant](https://www.home-assistant.io/). Installation tasks are derived from the [manual installation instructions](https://www.home-assistant.io/docs/installation/raspberry-pi/).

Tested with the help of [Molecule](https://molecule.readthedocs.io/en/latest/) and [Docker](https://www.docker.com/) for:
* Debian 9 Stretch
* Debian 10 Buster
* Ubuntu 18.04
* Ubuntu 18.10
* Fedora 28
* Fedora 29
* Centos 7

Used in real life only with Raspbian (Debian 9 Stretch).

Requirements
------------

* ansible >= 2.2

Role Variables
--------------

- **hass_version**: The version of Home Assistant which will get installed. By default it is not defined and automatically gets the lastest version available during installation.
- **hass_user**: The linux user running Home Assistant. Defaults to `hass`.
- **hass_virtualenv**: The directory the virtual environment for Home Assistant gets installed to. Defaults to `/opt/hass`.
- **hass_config**: The directory the configuration for Home Assistant is stored in. Defaults to `/home/hass/.homeassistant`.
- **hass_w1** Enables One Wire for Raspberry Pis. Usefull if you connect One Wire sensors directly to your Raspberry Pi and want to add them to Home Assistant. By default it is disabled (`false`). If enabled a restart of the system is needed after the playbook has been deployed.
- **hass_bluetooth**: Enables bluetooth support for Raspberry Pis and installs necessary packages (e.g. for [EQ3 Bluetooth thermostat](https://www.home-assistant.io/components/climate.eq3btsmart/)). By default it is disabled (`false`).
- **hass_pip_packages**: List of pip packages which should be installed in addition. E.g. for [EQ3 Bluetooth thermostat](https://www.home-assistant.io/components/climate.eq3btsmart/) "python-eq3bt" is needed. By default it is not defined.
- **hass_apt_packages** List of apt packages which should be installed in addition. Might be useful if you use Home Assistant components which depend on additional packages (e.g. [FRITZ!Box Net Monitor](https://www.home-assistant.io/components/sensor.fritzbox_netmonitor/)). By default it is not defined.

Dependencies
------------

None.

Example Playbook
----------------

```yaml
- hosts: hass
  roles:
    - hass
```

```yaml
- hosts: hass
  vars:
    hass_user: "pi"
    hass_virtualenv: "/srv/hass"
    hass_w1: true
    hass_apt_packages:
      - libxslt-dev
      - libxml2-dev
      - python3-lxml
  roles:
     - hass
```

License
-------

Copyright (c) 2018 Johannes Krausmueller - ISC License

Author Information
------------------

Johannes Krausmueller (johannes@krausmueller.de)  
Website: https://www.krausmueller.de
