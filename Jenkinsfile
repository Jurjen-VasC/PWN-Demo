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
        stash(name: 'Firmwares', includes: '*bin')
        archiveArtifacts(artifacts: 'controller_*.bin', fingerprint: true, onlyIfSuccessful: true)
        fingerprint '*bin'
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
        unstash 'Firmwares'
      }
    }
  }
}