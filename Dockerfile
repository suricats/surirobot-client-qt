FROM ubuntu:16.04
LABEL maintainer="tberdy@hotmail.fr"

RUN apt-get -y update
RUN apt-get install -y --fix-missing \
    build-essential \
    cmake \
    git \
    wget \
    curl \
    pkg-config \
    software-properties-common \
    libhiredis-dev \
    qt5-default \
    && apt-get clean && rm -rf /tmp/* /var/tmp/*

RUN cd ~ && \
    mkdir -p client && \
    git clone https://github.com/suricats/surirobot-client-qt.git client/ && \
    cd  client/ && \
    QMAKE=qmake make CONF=linux-debug build

CMD cd /root/client && \
    ./dist/linux-debug/GNU-Linux/surirobot-client-qt
