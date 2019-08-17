FROM alpine

RUN apk add --no-cache \
    ca-certificates \
 && apk add --no-cache --virtual .build-deps \
    binutils-dev \
    cmake \
    g++ \
    gcc \
    git \
    gmp \
    gmp-dev \
    libexecinfo-dev \
    make \
    musl-dev \
    openssl

RUN mkdir -p "/tmp/catch2" \
 && git clone https://github.com/catchorg/Catch2 /tmp/catch2 \
 && (cd /tmp/catch2 && cmake -Bbuild -H. -DBUILD_TESTING=OFF) \
 && (cd /tmp/catch2 && cmake --build build/ --target install)
