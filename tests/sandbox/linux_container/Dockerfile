FROM ubuntu:18.04
RUN apt update && apt -y upgrade && apt install -y vim clang

# VOLUME is created with -v flag in Makefile

#COPY ["compile_test.sh", "/opt/workspaceFolder/"]

ENV COMPILE_FOLDER=/opt/workspaceFolder
#RUN mkdir /opt/workspaceFolder && chmod 0777 /opt/workspaceFolder
#ENTRYPOINT ls; 
#while true; do eval \"$(cat pipe)\"; done
