#!/bin/bash

src1="
src/gettftp.c
src/tftp_cfg.c

src/request.c
src/fileReader.c

src/socket/socket.c
src/socket/socketSend.c
src/socket/socketReceive.c
"
src2="
src/puttftp.c
src/tftp_cfg.c

src/request.c
src/fileReader.c

src/socket/socket.c
src/socket/socketSend.c
src/socket/socketReceive.c
"

output1="-ogettftp.exe"
output2="-oputtftp.exe"

args="-g"
includes="
-Iinclude 
-Iinclude/socket
"

gcc $args $includes $src1 $output1
gcc $args $includes $src2 $output2