# Firmware directory
Each controller has it's own config file at this level.

The controllers share a lot of common settings, such as WiFi and MQTT settings. These are all present in the include directory.

The firmware is based on ESPHome. The yaml files will be converted into C++ code. This code is compiled and results in the firmware file.

In order to be able to compile the firmware you have to install esphome with the command `pip install esphome`

Updating is done with the command `pip install -U esphome`.

With new versions of `esphome` you might encounter changes in the yaml syntax. Please read the change log before compiling a new version.

The following table shows the most common options:

| Command | Result|
| ---|---|
| esphome yaml-file.yaml compile | Compile firmware |
| esphome yaml-file.yaml upload | Upload firmware via USB or wireless |
| esphome yaml-file.yaml run | Compile and upload firmware |
| esphome yaml-file.yaml logs | Show logs from the device |
