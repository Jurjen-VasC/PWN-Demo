#!/bin/bash

ansible-playbook  -u pi $@ playbook.yml 
rm playbook.retry
