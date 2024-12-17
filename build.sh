#!/bin/bash

src="
src/main.c
src/defaultMsg.c
src/commandReader.c
src/redirection.c
src/checkManyThings.c
src/commandExec.c
"

includes="
-Iinclude 
-Isrc
"

output="-oENSEA_SHELL.exe"
args="-g"

gcc $args $includes $src $output