Knowledge capture and experiments with low level C++ on RISC-V.

More details at either:

- https://philmulholland.medium.com/ 
- https://www.shincbm.com/

Projects:

- blinky : Example C++ blinky program for RISC-V

## Building

Platform IO is used to build the project locally.

Docker is used to build the project on github.

## Docker

The included dockerfile installs the [xpack RISC-V GCC toolchain](https://xpack.github.io/riscv-none-embed-gcc/) and uses cmake to compile the project.

To build locally using the docker file use these commands:
~~~
docker build --tag=my_project:latest .
docker run \
       -it \
       -v `pwd`:/work \
       my_project:latest \
       /work \
       blinky/src \

~~~
