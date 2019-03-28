#!/bin/bash

# which ansible || apt update   && apt install -y ansible

ansible-playbook  -u pi $@ playbook.yml 
rm playbook.retry
