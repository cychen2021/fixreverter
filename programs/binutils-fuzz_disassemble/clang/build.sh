cd binutils-gdb
cd binutils
sed -i 's/vfprintf (stderr/\/\//' elfcomm.c
sed -i 's/fprintf (stderr/\/\//' elfcomm.c
cd ../

./configure --disable-gdb --disable-gdbserver --disable-gdbsupport \
	    --disable-libdecnumber --disable-readline --disable-sim \
	    --enable-targets=all --disable-werror
make -j$(nproc)

sed -i "s/short FIXREVERTER\[FIXREVERTER_SIZE\];/extern short FIXREVERTER\[\];/" /src/fuzz_disassemble.c

mkdir -p fuzz
cp ../fuzz_*.c fuzz/
cd fuzz

$CC $CFLAGS -I ../include -I ../bfd -I ../opcodes -c fuzz_disassemble.c -o fuzz_disassemble.o
$CXX $CXXFLAGS fuzz_disassemble.o -o $OUT/fuzz_disassemble $LIB_FUZZING_ENGINE ../opcodes/libopcodes.a ../bfd/libbfd.a ../libiberty/libiberty.a ../zlib/libz.a $LDFLAGS
