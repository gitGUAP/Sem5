FROM ubuntu:latest

COPY ./app ./app

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends apt-utils

RUN apt-get update && apt-get install -y sudo wget gnupg gnupg2 && rm -rf /var/lib/apt/lists/*

RUN wget -qO- https://deb.nodesource.com/setup_10.x | sudo -E bash - && sudo apt-get install -y nodejs

RUN sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv 9DA31620334BD75D9DCB49F368818C72E52529D4 \
  && echo "deb [ arch=amd64 ] https://repo.mongodb.org/apt/ubuntu bionic/mongodb-org/4.0 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-4.0.list \
  && sudo apt-get update \
  && sudo apt-get install -y mongodb-org \
  && mkdir -p /data/db

CMD bash -c "mongod & sleep 10s && cd ./app && npm run start"