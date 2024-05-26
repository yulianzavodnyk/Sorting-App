FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    qt6-base-dev \
    qt6-tools-dev \
    qt6-tools-dev-tools \
    g++ \
    && apt-get clean

WORKDIR /usr/src/app

COPY . .

RUN mkdir -p build && cd build && \
    cmake .. && \
    make

CMD ["./build/First_Year_CS_Coursework"]