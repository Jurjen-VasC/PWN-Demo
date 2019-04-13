pipeline {
  agent any
  stages {
    stage('Build') {
      agent {
        docker {
          image 'python:2.7'
        }
      }
      agent any
      steps {
        echo 'Starting Build'
        sh '''
	  pip install esphome
          platformio platform update
        '''
        dir(path: 'Firmware') {
          sh '''
		esphome flowmeter-1.yaml compile
		mv controller_2/.pioenvs/controller_2/firmware.bin ../controller_2.bin

		esphome flowmeter-2.yaml compile
		mv controller_4/.pioenvs/controller_4/firmware.bin ../controller_4.bin
	  '''
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
