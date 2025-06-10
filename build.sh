gcc -g -c src/mydiff.c -o build/mydiff.o -Iinclude
gcc -g build/mydiff.o src/diffpatch.c -o build/diffpatch -Iinclude
