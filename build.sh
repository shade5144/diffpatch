gcc -c src/mydiff.c -o build/mydiff.o -Iinclude
gcc build/mydiff.o src/diffpatch.c -o build/diffpatch -Iinclude
