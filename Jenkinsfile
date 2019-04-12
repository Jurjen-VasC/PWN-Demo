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
      steps {
        sh '''cd Firmware
cp controller_1/.pioenvs/controller_1/firmware.bin controller_1.bin'''
        archiveArtifacts 'Firmware/*bin'
      }
    }
  }
}