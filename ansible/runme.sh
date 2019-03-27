#!/bin/bash

sudo apt update
sudo apt install ansible

ansible-playbook  -u pi $@ playbook.yml 
rm playbook.retry
