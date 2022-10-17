# syntax=docker/dockerfile:1
FROM ubuntu:20.04 AS base

LABEL maintainer.name="Gabriel Lauzier"
LABEL maintainer.email="gabriel.lauzier@usherbrooke.ca"

COPY packages packages

RUN apt-get update -qq \
    && ln -sf /usr/share/zoneinfo/UTC /etc/localtime \
    && apt-get install -y $(cat packages) \
    && apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/cache/apt/archives/* \
    && rm -rf /var/lib/apt/lists/*
