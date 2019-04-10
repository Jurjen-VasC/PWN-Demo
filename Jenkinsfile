pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        echo 'Starting Build'
        sh '''#!/bin/bash

which pip
which virtualenv
which passed
ls /etc

virtualenv --no-site-packages ESPHome
cd esphome
pwd
pip install ESPHome'''
      }
    }
  }
}