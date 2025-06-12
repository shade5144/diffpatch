gcc -g -c src/mydiff.c -o build/mydiff.o -Iinclude
gcc -g build/mydiff.o src/diff.c -o build/mydiff -Iinclude
gcc -g src/patch.c -o build/mypatch -Iinclude
