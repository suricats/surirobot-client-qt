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
    qtmultimedia5-dev \
    libopencv-dev uuid-dev \
    libopenal-dev libalut-dev libsndfile1-dev libsdl2-dev libsdl2-mixer-dev \
    libmpg123-dev libao-dev \
    libavdevice-dev \
    && apt-get clean && rm -rf /tmp/* /var/tmp/*

RUN cd ~ && \
    mkdir -p client && \
    git clone https://github.com/suricats/surirobot-client-qt.git client/ && \
    cd  client/ && \
    QMAKE=qmake make CONF=linux-debug build

CMD cd /root/client && \
    ./dist/linux-debug/GNU-Linux/surirobot-client-qt
