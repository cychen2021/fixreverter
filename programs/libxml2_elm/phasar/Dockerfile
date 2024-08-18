FROM fr_phasar:latest
COPY --from=elmfuzz/libxml2:latest /src /src
ENV CC=clang
ENV CXX=clang++
RUN apt-get update -y && apt-get install -y automake libtool vim pkg-config
