
pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                echo 'Building..'
                docker run --rm --net=host -v "\$(pwd)":/config esphome/esphome flow-1.yaml compile
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying....'
            }
        }
    }
}
