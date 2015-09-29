# Charm++
This repository contains different code sample that make use of Charm++. 
If running in euler or a development node make sure you run the following two commands before trying to build anything with charm++:

```
    module load gcc
    module load charm
```

## Charm++ Local setup in Linux/OSX
To setup Charm++ in a Unix based system it was relatively simple. Either clone the git repository or download the distribution version and then go into the folder and run:

```
./build
```

Answer the different question the build program asks you. Here is what I answered for my local build:

```
Are you building to run just on the local machine, and not across multiple nodes? [Y/n]
Y

Do you want to specify a compiler? [y/N]N

Do you want to specify any Charm++ build options, such as fortran compilers? [y/N]N

Choose a set of compiler flags [1-5]
	1) none
	2) debug mode                        -g -O0
	3) production build [default]        --with-production
	4) production build w/ projections   --with-production --enable-tracing
	5) custom

3

What do you want to build?
	1) Charm++ [default] (choose this if you are building NAMD)
	2) Charm++, AMPI, ParFUM, FEM and other libraries

2

Do you want to compile in parallel?
        1) No
        2) Build with -j2
        3) Build with -j4
        4) Build with -j8
        5) Build with -j16 [default]
        6) Build with -j32
        7) Build with -j

3
We have determined a suitable build line is:
	./build LIBS multicore-darwin-x86_64   -j4  --with-production


Do you want to start the build now? [Y/n]Y
Building with: ./build LIBS multicore-darwin-x86_64   -j4  --with-production
```

The reason I did not choose either an specific compiler (e.g. gcc) in step 2 was I've had problems with explicitly telling my machine to use gcc. The gcc command in my machine maps by default to the clang compiler. So I decided to simply let Charm++ build system decide. This might be the easiest choice for setting up locally, however, when building Charm++ in Euler we will have to be a little more picky I guess. 

Then add the following line to you bash file, in OSX I added the line to `.bash_profile`:

```
export CHARMDIR = "PATH TO THE DIRECTORY WHERE YOU RAN ./build"
```

This `$CHARMDIR` environment variable will be used by the Makefiles in your Charm++ program.

## Common 
To compile any of the programs in this folder you need to make sure you have gcc and add the following line in the Makefile:

```
CHARMDIR = [Insert the path to your charm installation directiory]
```

If you followied the local setup described above, then there is no need to declare the CHARMDIR variable since it already is an environment variable. Therefore the following line should have the right values

```
CHARMC = $(CHARMDIR)/bin/charmc $(OPTS)
```

### The charmrun binary

Whenever a Charm++ program is compiled it produces one extra excutable file called `charmrun`. This binary is used to run the output binary of your Charm++ program in the following way:

```
./charmrun +p4 ./arrayHello [Input arguments]
```

The previous command will run the arrayHello program using 4 PE's (processing elements).

### Chare Arrays

The ArrayHello example contains a 1D array example and the Jacobi2D contains a 2D array example. Note


## ArrayHello
### Elements of the Program
#### Main Chare
Purpose of the Main chare is to: Create the other chare objects in the application, initiate the computation, call CkExit() when the calculation is finished.

#### Hello Chare

Elements in the Chare Array. Each chare says hi and initiates the sayHi() command for the next chare in the array. 

## hello

Prints hello world using the charm++ file structure. 

After editing the Makefile you should be able to build and run the hello world with the following commands:

```
make
./charmrun ./hello
```

The binary charmrun the Charm++ runtime environment.



