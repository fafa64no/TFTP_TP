#!/bin/bash

src="
src/main.c
"

includes="
-Iinclude 
-Isrc
"

output="-oTFTP_TP.exe"
args="-g"

gcc $args $includes $src $output