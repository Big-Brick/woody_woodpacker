
FROM ubuntu:16.04

ENV DEBIAN_FRONTEND noninteractive

WORKDIR /root

RUN apt-get update \
 && apt-get upgrade -y \
 && apt-get install -y --no-install-recommends \
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
 && apt clean \
 && rm -rf /var/lib/apt/lists/*

ARG CMAKE_MINOR_VERSION=3.14
ARG CMAKE_PATCH_VERSION=0
ARG CMAKE_VERSION="$CMAKE_MINOR_VERSION.$CMAKE_PATCH_VERSION"
ARG ARCH="Linux-x86_64"

RUN cd /opt \
 && wget https://cmake.org/files/v$CMAKE_MINOR_VERSION/cmake-$CMAKE_VERSION-$ARCH.tar.gz \
 && tar xf cmake-$CMAKE_VERSION-$ARCH.tar.gz \
 && rm cmake-$CMAKE_VERSION-$ARCH.tar.gz \
 && ln -sf /opt/cmake-$CMAKE_VERSION-$ARCH/bin/ccmake /usr/bin/ccmake \
 && ln -sf /opt/cmake-$CMAKE_VERSION-$ARCH/bin/cmake /usr/bin/cmake \
 && ln -sf /opt/cmake-$CMAKE_VERSION-$ARCH/bin/cpack /usr/bin/cpack \
 && ln -sf /opt/cmake-$CMAKE_VERSION-$ARCH/bin/ctest /usr/bin/ctest

ADD test.c ./

RUN gcc -o test test.c && gcc -m32 -o test32 test.c

ENTRYPOINT cmake -S /mnt -B build &&  cmake --build build && ln -s ./build/woody_woodpacker . ; bash
