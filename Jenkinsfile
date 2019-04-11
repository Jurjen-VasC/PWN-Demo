pipeline {
  agent any
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
  }
}