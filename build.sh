#!/bin/bash

src1="
src/gettftp.c
src/tftp_cfg.c
src/socket.c
"
src2="
src/puttftp.c
src/tftp_cfg.c
src/socket.c
"

output1="-ogettftp.exe"
output2="-oputtftp.exe"

args="-g"
includes="
-Iinclude 
-Isrc
"

gcc $args $includes $src1 $output1
gcc $args $includes $src2 $output2