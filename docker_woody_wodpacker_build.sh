#!/bin/bash
docker build \
	-t woody_ubuntu \
	--build-arg UNAME=adzikovs \
	--build-arg UID=$(id -u) \
	--build-arg GID=$(id -g) \
	.
