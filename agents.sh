#!/usr/bin/env bash
for agent in {1..100}
do
  ./bin/SimpleSend "{\"id\":$agent,\"port\":$((8000+agent)),\"location\":{\"x\":$((agent * 50)),\"y\":50,\"z\":0},\"rotation\":{\"x\":0,\"y\":0,\"z\":0}}"
done