FROM ubuntu:16.04

ENV DEBIAN_FRONTEND noninteractive

RUN apt update \
 && apt upgrade -y \
 && apt install -y --no-install-recommends \
    ca-certificates            \
    software-properties-common \
    curl                       \
    wget                       \
    git                        \
    vim                        \
    file                       \
    tree                       \
    file                       \
    less                       \
    build-essential            \
    gcc-multilib               \
    nasm                       \
    valgrind                   \
	cmake \
 && apt clean \


WORKDIR /root

ARG UNAME=user
ARG UID=1000
ARG GID=1000
RUN groupadd -g $GID -o $UNAME
RUN useradd -m -u $UID -g $GID -o -s /bin/bash $UNAME

ENTRYPOINT bash
