#!/bin/bash
docker build -t boids:latest --build-arg JOBS=$(nproc) .
