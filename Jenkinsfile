pipeline {
  agent any
  stages {
    stage('Prepare') {
      agent {
        docker {
          image 'python'
        }

      }
      steps {
        sh 'pip install esphome'
      }
    }
  }
}