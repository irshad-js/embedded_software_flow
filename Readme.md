# Embedded software workflow
[![Code style: black](https://img.shields.io/badge/code%20style-black-000000.svg)](https://github.com/psf/black)
[![CircleCI](https://dl.circleci.com/status-badge/img/gh/irshad-js/embedded_software_flow/tree/james_grenning_tdd_exercises.svg?style=svg)](https://dl.circleci.com/status-badge/redirect/gh/irshad-js/embedded_software_flow/tree/james_grenning_tdd_exercises)


## docker commands

docker run -it -v "$(PWD):/home/app" irshadjs/software_workflow:0.2

docker run -it -v "%cd%:/home/app" irshadjs/software_workflow:0.2

use this command to make the scripts in bash, executable:

sed -i -e 's/\r$//' scriptname.sh

docker build -t irshadjs/software_workflow:0.2 .



