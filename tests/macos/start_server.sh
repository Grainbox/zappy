#!/bin/bash

if ! [ -x "$(command -v docker)" ]; then
    echo "Docker is not installed. Please install Docker and try again."
    exit 1
fi

docker build -t ctn_zappy_server .

if [ "$(docker ps -q -f name=zappy_server)" ]; then
    echo "Stopping and removing existing container..."
    docker rm -f zappy_server
fi

docker run -d -p 4242:4242 --name zappy_server ctn_zappy_server
echo "Server is running on localhost:4242"
echo "To stop the server, run ./stop_server.sh"
echo "To restart the server, run ./start_server.sh"