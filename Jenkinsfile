
pipeline {
    agent any
// docker run -it --entrypoint bash -v $(pwd):/config esphome/esphome 
    stages {
        stage('Build') {
            agent {
               docker {
                  image 'esphome/esphome'
                  args '--entrypoint bash -v .:/config'  // start interactive in esphome container
               }
	    }
            steps {
                echo 'Building..'
                sh '''
                cd Firmware
                esphome flowmeter-1.yaml compile
		'''
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
