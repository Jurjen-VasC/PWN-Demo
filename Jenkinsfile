pipeline {
  agent {
    docker {
      image 'python:2.7'
    }

  }
  stages {
    stage('Prepare') {
      agent {
        docker {
          image 'python:2.7'
        }

      }
      steps {
        sh 'pip install esphome'
      }
    }
    stage('Compile') {
      steps {
        sh '''ls
pwd
cd Firmware
esphome flowmeter-2.yaml compile'''
      }
    }
  }
}