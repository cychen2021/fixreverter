FROM fr_phasar_port:latest
COPY --from=elmfuzz/libxml2:latest /src /src
ENV CC="wllvm"
ENV CXX="wllvm++"
ENV LLVM_COMPILER_PATH="/usr/local/llvm-10/bin"
ENV LLVM_COMPILER="clang"
RUN apt-get update -y && apt-get install -y automake libtool vim pkg-config liblzma-dev
# Need to self-compile automake-1.16.3
RUN apt-get remove -y automake
WORKDIR /src
RUN wget https://ftp.gnu.org/gnu/automake/automake-1.16.3.tar.xz
RUN tar -xvf automake-1.16.3.tar.xz
WORKDIR /src/automake-1.16.3
RUN ./configure
RUN make
RUN make install
RUN ln -s /usr/local/bin/automake /usr/bin/automake
WORKDIR /src
ENV ACLOCAL_PATH=/usr/share/aclocal
