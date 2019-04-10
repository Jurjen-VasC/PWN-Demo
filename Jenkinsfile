pipeline {
  agent {
    docker {
      image 'esphome/esphome'
      args '--entrypoint bash -v Firmware:/config'
    }

  }
  stages {
    stage('Build') {
      steps {
        echo 'Starting Build'
        sh 'esphome flowmeter-2.yaml compile'
      }
    }
  }
}