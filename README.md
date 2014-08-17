janix
=====

Small kernel hobby project targeted to x86 architecture.

### Dependencies needed to compile and run janix

1. NASM 
2. GCC
3. Make
4. Bochs (bochs configuration uses sdl as a display library so bochs-sdl plugin is needed also)

If you're using some linux distribution, above dependencies should be available from package management.

### Compiling and running janix

run `make` to compile and link the binaries and to produce the .iso image. Now you can boot the kernel with `make run-bochs`.

### Cleaning up

`make deepclean` clears object files and binaries from directories. `make clean` removes produced .iso image and bochs log files.