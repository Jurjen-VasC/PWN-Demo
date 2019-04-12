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
mv controller_2/.pioenvs/controller_2/firmware.bin ../controller_2.bin'''
        }

        sh '''pwd
ls -la'''
      }
    }
    stage('Test') {
      agent any
      steps {
        echo 'Starting Test'
        archiveArtifacts(fingerprint: true, onlyIfSuccessful: true, artifacts: 'controller_2.bin')
      }
    }
    stage('Deploy') {
      steps {
        echo 'Starting Deploy'
      }
    }
  }
}