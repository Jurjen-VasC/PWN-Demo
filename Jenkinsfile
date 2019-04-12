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
      agent any
      steps {
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
    stage('Deliver') {
      agent any
      steps {
        sh '''cd
	  pwd'''
      }
    }
  }
}
