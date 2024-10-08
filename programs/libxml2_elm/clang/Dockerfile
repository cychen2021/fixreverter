FROM fr_clang:latest
COPY --from=elmfuzz/libxml2:latest /src /src
ENV CC=clang
ENV CXX=clang++
RUN apt-get update -y && apt-get install -y libtool vim pkg-config
RUN apt install -y zlib1g-dev liblzma-dev
RUN apt install -y /src/automake_1.16.5-1.3_all.deb
