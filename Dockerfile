# syntax=docker/dockerfile:1

FROM ubuntu:24.04 AS base

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates cmake g++ make ninja-build pkg-config zip \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /src
COPY . .

FROM base AS linux-build

RUN apt-get update && apt-get install -y --no-install-recommends \
    freeglut3-dev libsfml-dev libgl1-mesa-dev \
    && rm -rf /var/lib/apt/lists/*

RUN cmake -S . -B build-linux -G Ninja -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build-linux --parallel

RUN mkdir -p /out/asteroids-linux-x86_64/lib \
    && cp build-linux/asteroids /out/asteroids-linux-x86_64/ \
    && cp -R build-linux/assets /out/asteroids-linux-x86_64/ \
    && ldd build-linux/asteroids | awk '/=> \/[^ ]+/ {print $3}' | while read -r library; do \
        case "$library" in \
            /lib*/ld-linux-*|/lib*/libc.so.*|/lib*/libm.so.*|/lib*/libpthread.so.*|/lib*/librt.so.*|/lib*/libdl.so.*|/lib*/libasound.so.*) ;; \
            *) cp "$library" /out/asteroids-linux-x86_64/lib/ ;; \
        esac; \
    done \
    && printf '%s\n' \
        '#!/bin/sh' \
        'directory=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)' \
        'export LD_LIBRARY_PATH="$directory/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"' \
        'exec "$directory/asteroids" "$@"' \
        > /out/asteroids-linux-x86_64/run-asteroids.sh \
    && chmod +x /out/asteroids-linux-x86_64/run-asteroids.sh \
    && cd /out && zip -qr asteroids-linux-x86_64.zip asteroids-linux-x86_64

FROM scratch AS package-linux
COPY --from=linux-build /out/asteroids-linux-x86_64.zip /
