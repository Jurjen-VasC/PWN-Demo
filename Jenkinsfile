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
    stage('') {
      agent any
      steps {
        archiveArtifacts(artifacts: 'firmware.bin', onlyIfSuccessful: true)
      }
    }
  }
}