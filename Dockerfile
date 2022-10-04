# syntax=docker/dockerfile:1
FROM ubuntu:20.04 AS base

LABEL maintainer.name="Gabriel Lauzier"
LABEL maintainer.email="gabriel.lauzier@usherbrooke.ca"

WORKDIR /tmp

USER root

COPY packages packages

RUN apt-get update -qq \
    && ln -sf /usr/share/zoneinfo/UTC /etc/localtime \
    && apt-get install -y $(cat packages) \
    && apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/cache/apt/archives/* \
    && rm -rf /var/lib/apt/lists/*

FROM base as builder

ARG JOBS=1

WORKDIR /tmp/boids
COPY . .
RUN mkdir build\
    && cd build \
    && cmake .. \
        -DCMAKE_CXX_STANDARD=17 \
        -DCMAKE_INSTALL_PREFIX=/opt/install \
    && make -j${JOBS} install

FROM base

ARG username=groot
RUN groupadd -r groot && useradd -m -d /home/${username} -s /bin/bash -g groot ${username}
ENV HOME /home/${username}

USER ${username}

WORKDIR /home/${username}

COPY --from=builder /opt/install /opt/install
COPY entrypoint.sh .

ENTRYPOINT [ "./entrypoint.sh" ]
CMD [ "/bin/bash" ]