FROM fr_clang:latest
COPY --from=elmfuzz/sqlite3:latest /src /src
ENV CC=clang
ENV CXX=clang++
RUN apt-get update -y && apt-get install -y automake libtool vim pkg-config expect zlib1g-dev
RUN rm -rf /src/sqlite3/bld
