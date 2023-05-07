# Embedded software workflow

## Explanation on the first major commit on 06-May

This commit included/added the first python based model script
that modelled the logic behing a microwave/grill combo equipment.
The logic was modelled using simple flat state machine. This commit
has not yet included logic for grill functionality. Finally, this
python script is now manually capable of simulating button presses
and time events.

When there is a need to update the dockerfile's contents, a new
image needs to be built and containers spin off from them.

docker build -t irshadjs/workflow_standard .