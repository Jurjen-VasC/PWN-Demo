pipeline {
  agent {
    docker {
      image 'python:2.7'
    }

  }
  stages {
    stage('Prepare') {
      agent any
      steps {
        sh '''pip install esphome
exit'''
      }
    }
    stage('Compile') {
      steps {
        sh 'platformio platform update'
        dir(path: 'Firmware') {
          sh 'esphome flowmeter-1.yaml compile'
          sh 'esphome flowmeter-2.yaml compile'
          sh 'esphome flowmeter-3.yaml compile'
        }

      }
    }
    stage('error') {
      agent any
      steps {
        echo 'Time to archive build result'
        sh 'ls -lRa *'
      }
    }
  }
}