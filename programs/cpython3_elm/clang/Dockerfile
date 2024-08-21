FROM fr_clang:latest
COPY --from=elmfuzz/cpython3:latest /src /src
ENV CC=clang
ENV CXX=clang++
RUN apt-get update -y && apt-get install -y automake libtool vim pkg-config expect zlib1g-dev
