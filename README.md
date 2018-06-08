# mpihm

Do quick&merge sorting in an MPI way! 

## Dependencies

### Windows

Toolchain with CMake 3.10+
<br>
Microsoft MPI 9.x
<br>
Microsoft MPI SDK 9.x

### Unix (Linux /  Mac OS)

gcc
<br>
MPICH 3.x

## Build

### Windows

A cmake configuration `makelist.txt` is provided. Replace variables `INC_DIR` and `LIB_DIR` with your local MS-MPI SDK paths.

```bat
cmake --build cmake-build-debug --target mpihm -- -j 4
```

### Linux /  Mac OS

Add option `"-std=c99"` to compile while following c99 standard. Make sure directory `./build` already exist.

```bash
mpicc *.h *.c -std=c99 -o build/mpihm
```
## Run

Program itself receives two parameters: `input_filename`, `output_filename`


> If the parameters are left blank, then default value `in.txt` and `out.txt` will be in use. An invalid `input_filename` would cause a fatal error.

### Windows

Set process number to 8 with the option `"-n"`

```bat
mpiexec -n 8 cmake-build-debug/mpihm build/in.txt build/out.text 2> build/error.txt
```

### Linux /  Mac OS

Add option `"--allow-run-as-root"` to enable running as root.

Add option `"--oversubscribe"` to run more processes than processors (optional)

Set process number to 8 with the option `"-np"`

```bash
mpirun --allow-run-as-root --oversubscribe -np 8 build/mpihm build/in.txt build/out.txt 2> build/error.txt
```

> For unix, a helper script `run.sh` is provided to do both building and running.

## Input

Program requires an input file that contains all the numbers to be sorted. In the file, numbers should be evenly seperated by `'\n'` or `' '`.

> <font style="color:red">CAUTION:</font> The number of numbers to be input is supposed to be a multiple of process number. Otherwise, an error may occur.

## Output

Sorted result be both be printed on the console and written into the appointed output file.

While using the helper script, error messages caused by MPI-related issues are redirected into `./build/error.txt` so that we should expect to have a clearer and tidier output.