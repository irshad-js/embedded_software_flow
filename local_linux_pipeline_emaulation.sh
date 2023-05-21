#! /usr/bin/bash

RED='\033[0;31m'
NOCOLOR='\033[0m'
custom_color='\x1b[33;41;1m'
printf "${custom_color}This is the circle ci pipeline emulator for local systems${NOCOLOR}\n\n"
printf "${custom_color}Step 1: Downloading plantuml java file from source website${NOCOLOR}\n\n"
wget https://github.com/plantuml/plantuml/releases/download/v1.2023.7/plantuml-1.2023.7.jar -O plantuml.jar
printf "${custom_color}Step 2: Creating a svg based UML output diagram from the UML file${NOCOLOR}\n\n"
java -jar plantuml.jar Software\ modelling/Docs/plantuml_microwave_model.txt -svg
printf "${custom_color}Step 3: Simulating the python model using microwave json stimuli ${NOCOLOR}\n\n"
python3 Software\ modelling/python_model.py NON_GUI Software\ modelling/simulate_mw_operation_simple.json
printf "${custom_color}Step 3: Simulating the python model using grill json stimuli ${NOCOLOR}\n\n"
python3 Software\ modelling/python_model.py NON_GUI Software\ modelling/simulate_grill_operation_simple.json
printf "${custom_color}Steps completed. Shell script exiting${NOCOLOR}\n\n"
