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
    stage('Build') {
      agent any
      steps {
        echo 'Starting Build'
        sh 'platformio platform update'
        dir(path: 'Firmware') {
          sh '''esphome flowmeter-1.yaml compile
ls -la controller*'''
          sh '''esphome flowmeter-2.yaml compile
ls -la controller*'''
          sh '''esphome flowmeter-3.yaml compile
ls -la controller*'''
        }

      }
    }
    stage('Test') {
      agent any
      steps {
        echo 'Starting Test'
      }
    }
    stage('Deploy') {
      steps {
        echo 'Starting Deploy'
      }
    }
  }
}