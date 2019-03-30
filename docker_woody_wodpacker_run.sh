#!/bin/bash
docker run \
	--cap-add=SYS_PTRACE \
	--security-opt seccomp=unconfined \
	-ti -d \
	-v $PWD:/local/workspace \
	--name woody_container \
	woody_ubuntu 

