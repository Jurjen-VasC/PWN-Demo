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
ls -aR
cd Firmware
cp controller_2/.pioenvs/controller_2/firmware.bin controller_2.bin
cp controller_4/.pioenvs/controller_4/firmware.bin controller_4.bin
cp controller_6/.pioenvs/controller_6/firmware.bin controller_6.bin'''
        archiveArtifacts(artifacts: 'Firmware/*bin', onlyIfSuccessful: true)
      }
    }
  }
}