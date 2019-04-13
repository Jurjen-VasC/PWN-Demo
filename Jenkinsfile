pipeline {
  agent any
  stages {
    stage('Build') {
      agent {
        docker {
          image 'python:2.7'
        }

      }
      steps {
        echo 'Starting Build'
        sh '''	pip install esphome
		platformio platform update
	'''
        dir(path: 'Firmware') {
          sh '''for i in $(seq 1 6)
		do
			esphome controller_${i}.yaml compile
			mv controller_${i}/.pioenvs/controller_${i}/firmware.bin ../controller_${i}.bin
		done
	  '''
        }

        sh '''pwd
		ls -la
	'''
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
        dir(path: ' Firmware/builds/latest') {
          unstash 'Firmwares'
        }

      }
    }
  }
}