pipeline {
  agent any
  stages {
    stage('Prepare') {
      steps {
        isUnix()
        sh '''#!/bin/bash
su - -c \'apk add --no-cache --virtual .build-deps g++ python3-dev\'
su - -c \'apk add --no-cache --update python3\'

pip3 install --upgrade pip setuptools

pip3 install ESPHome'''
      }
    }
  }
}