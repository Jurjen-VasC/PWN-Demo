pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        echo 'Starting Build'
        sh '''#!/bin/bash
apk add --update py-pip
which pip
which virtualenv
which passed

pip install ESPHome

ls'''
      }
    }
  }
}