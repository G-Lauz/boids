#!/bin/bash
docker run --name boids -e DISPLAY=:1 -v /tmp/.X11-unix:/tmp/.X11-unix --network host --user 1000 --rm -it boids:latest
