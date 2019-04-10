pipeline {
  agent {
    docker {
      image 'esphome/esphome'
      args '--entrypoint bash -v $(pwd):/config'
    }

  }
  stages {
    stage('Build') {
      steps {
        echo 'Starting Build'
      }
    }
  }
}