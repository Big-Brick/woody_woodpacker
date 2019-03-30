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
	gdb \
 && apt clean \

RUN echo "layout regs" > /root/.gdbinit
RUN echo "focus cmd" >> /root/.gdbinit
RUN echo "set disassemble-flavor intel" >> /root/.gdbinit

