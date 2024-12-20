#!/bin/bash

./puttftp.exe 127.0.0.1 manigancien_sauvage.txt data/portfolio.txt
./gettftp.exe 127.0.0.1 manigancien_sauvage.txt
./puttftp.exe 127.0.0.1 manigancien_sauvage.txt data/gringo.txt
./gettftp.exe 127.0.0.1 manigancien_sauvage.txt