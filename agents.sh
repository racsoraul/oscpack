#!/usr/bin/env bash

bold=$(tput bold)
normal=$(tput sgr0)
underline=$(tput smul)
no_underline=$(tput rmul)

address=$1
number_agents=$2
x_separation=$3
z_init_position=$4

# Address argument is required
if [ -z "$address" ]
then
  echo
  echo "ERROR! Address argument is required."
  echo "USAGE: agent.sh ADDRESS [NUMBER_AGENTS] [X_SEPARATION] [Z_INIT_POSITION]"
  echo
  exit 1
fi

# Default number of agents
if [ -z "$number_agents" ]
then
 number_agents=50
fi

# Default X separation
if [ -z "$x_separation" ]
then
 x_separation=50
fi

# Default Y initial position
if [ -z "$z_init_position" ]
then
 z_init_position=50
fi

echo
echo "${underline}Script running with following values${no_underline}"
echo
echo "Number of agents:   ${bold}$number_agents${normal}"
echo "Address:            ${bold}/spawn/$address${normal}"
echo "X separation units: ${bold}$x_separation${normal}"
echo "Z initial position: ${bold}$z_init_position${normal}"
echo

for agent in $(seq 0 $((number_agents -1)))
do
  ./bin/SimpleSend "$address" "{\"id\":$agent,\"port\":$((8000+agent)),\"location\":{\"x\":$((agent * x_separation)),\"y\":50,\"z\":$z_init_position},\"rotation\":{\"x\":0,\"y\":0,\"z\":0}}"
done