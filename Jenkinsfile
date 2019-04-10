pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        echo 'Starting Build'
        sh '''#!/bin/bash
virtualenv --no-site-packages ESPHome
cd esphome
pwd
pip install ESPHome'''
      }
    }
  }
}