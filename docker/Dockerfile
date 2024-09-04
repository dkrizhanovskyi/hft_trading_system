# docker/Dockerfile
FROM fedora:latest

RUN dnf -y update && \
    dnf -y install gcc gcc-c++ cmake git make gtest gtest-devel

WORKDIR /usr/src/app

COPY . /usr/src/app

RUN mkdir -p build && cd build && cmake .. && make

CMD ["./HFTTradingSystem"]
