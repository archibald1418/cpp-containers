FROM ubuntu:18.04
RUN apt update && apt -y upgrade && apt install -y vim clang

# VOLUME is created with -v flag in Makefile

#COPY ["compile_test.sh", "/opt/workspaceFolder/"]

VOLUME /opt/workspaceFolder
ARG COMPILE_FOLDER=/opt/workspaceFolder
#RUN mkdir /opt/workspaceFolder && chmod 0777 /opt/workspaceFolder
WORKDIR $COMPILE_FOLDER
ENTRYPOINT \
while true; do eval "$(cat < pipe | tr -d '\0')" >> eval.log 2>>errors.log; > pipe && sleep 0.6; done
