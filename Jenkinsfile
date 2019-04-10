pipeline {
  agent any
  stages {
    stage('Prepare') {
      steps {
        isUnix()
        sh '''#!/bin/bash
find / -name \'python*\'
pip install ESPHome'''
      }
    }
  }
}