FROM php
RUN mkdir -p /home/app/
RUN apt update && apt install git clang vim -y
EXPOSE 0-40000
USER root
WORKDIR /home/app/ 