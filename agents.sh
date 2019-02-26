#!/usr/bin/env bash
address=$1
x_separation=$2
z_init_position=$3

# Address argument is required
if [ -z "$address" ]
then
  echo
  echo "ERROR! Address argument is required."
  echo "USAGE: agent.sh ADDRESS [X_SEPARATION] [Z_INIT_POSITION]"
  echo
  exit 1
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
echo "=== Script running with following values ==="
echo "Address: $address"
echo "X separation units: $x_separation"
echo "Z initial position: $z_init_position"
echo

for agent in {0..50}
do
  ./bin/SimpleSend "$address" "{\"id\":$agent,\"port\":$((8000+agent)),\"location\":{\"x\":$((agent * x_separation)),\"y\":50,\"z\":$z_init_position},\"rotation\":{\"x\":0,\"y\":0,\"z\":0}}"
done