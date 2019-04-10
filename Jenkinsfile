pipeline {
  agent any
  stages {
    stage('Prepare') {
      steps {
        isUnix()
        sh '''#!/bin/bash
which python'''
      }
    }
  }
}