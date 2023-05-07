FROM ubuntu:latest

RUN \
	apt-get update && \
    apt-get clean && \
	apt-get install -y python3 && \
	apt-get install -y build-essential && \
	apt-get install -y plantuml && \
	DEBIAN_FRONTEND=noninteractive apt-get install -y gdb
	
WORKDIR /usr/base_application_home/


# First, crate the image like so: docker build -t software_workflow .
# Then, create the container like so: docker create --name custom_container custom_gcc_image
# finally, mount and run the container like so: # docker run -it --name custom_workflow_instance -v "%cd%":/usr/base_application_home/ irshadjs/workflow_standard
# ctrl+d to exit interactive
# docker restart custom_image
# The %cd% is focused on windows cmd

