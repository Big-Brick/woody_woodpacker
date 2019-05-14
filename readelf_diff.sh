#!/bin/bash
readelf -aW woody > woody.txt
readelf -aW $1 > $1.txt
vimdiff woody.txt $1.txt
