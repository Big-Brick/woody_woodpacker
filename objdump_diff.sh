#!/bin/bash
objdump -D woody > woody.txt
objdump -D $1 > $1.txt
vimdiff woody.txt $1.txt
