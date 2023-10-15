#!/bin/bash

if ! [ -x "$(command -v docker)" ]; then
    echo "Docker is not installed. Please install Docker and try again."
    exit 1
fi

if [ "$(docker ps -q -f name=zappy_server)" ]; then
    echo "Stopping and removing existing container..."
    docker stop zappy_server && docker rm zappy_server
else
    echo "No running container named zappy_server found."
fi
