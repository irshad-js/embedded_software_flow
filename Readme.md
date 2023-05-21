# Embedded software workflow
[![Code style: black](https://img.shields.io/badge/code%20style-black-000000.svg)](https://github.com/psf/black)


## Explanation on the first major commit on 06-May

This commit included/added the first python based model script
that modelled the logic behing a microwave/grill combo equipment.
The logic was modelled using simple flat state machine. This commit
has not yet included logic for grill functionality. Finally, this
python script is now manually capable of simulating button presses
and time events.

When there is a need to update the dockerfile's contents, a new
image needs to be built and containers spin off from them.

docker build -t irshadjs/software_workflow:0.2 .

## docker commands

docker run -it -v "$(PWD):/home/app" irshadjs/software_workflow:0.2

docker run -it -v "%cd%:/home/app" irshadjs/software_workflow:0.2

use this command to make the scripts in bash, executable:

sed -i -e 's/\r$//' scriptname.sh

## Explanation on the commit 21-May

The python based model is now complete with non gui based simulation that
can be customized based on the json scripts provided to it. The docker file
is updated and a local CI emulator script is constructed to help emulate the
behavior of CI pipelines locally.

docker image push irshadjs/software_workflow:0.2


