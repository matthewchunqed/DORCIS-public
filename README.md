# DORCIS #
DORCIS is a tool that produces depth and T-depth optimized implementation given a desired target (3-bit or 4-bit bijective) S-box. This tool is built on top of [LIGHTER](https://eprint.iacr.org/2017/101) and its reversible circuit extension [LIGHTER-R](https://ieeexplore.ieee.org/abstract/document/9088027). The corresponding paper can be found on [ePrint](https://eprint.iacr.org/2023/286).

S-boxes can be passed in the *LUT* format. This is an 8 or 16 character long string (for 3- and 4- bit S-boxes respectively). For example, "`0123456789ABCDEF`" refers to the 4-bit identity S-box.

Alternately, S-boxes can also be passed in the *bit-slice* format. This is an 8 or 19 character long string (for 3 and 4 bit S-boxes respectively). The process on how to convert from LUT to bit-slice is explained in the paper, but the strings must include the spaces. For example, "`1e 39 6a`" is the bit-slice form of what is "`01367452`" in the LUT format.

## Command Line Usage ##
    ./non-lin-search [-v] [-w] [-u] [-q] [-t]
                   [-p NUMBER] [-r NUMBER]
                   [-i SBOX] [-o SBOX]

    Required Functions:
    -q : Enable all reversible gates
    -o <function> : Define arrival function
    -t : Switch from Depth Preferred Search to T-depth Preferred Search. So if there exists a box with implementation A = depth 10, T-depth 4 and implementation B = depth 12, T-depth 3, Depth Preferred Search returns implementation 0 and T-depth Preferred Search return implementation 1.
    They usually return the same box regardless of Depth or T-Depth preference.

    Utility Functions:
    -v : Verbose mode
    -u : Expand only [-i] function (identity function by default)
    -w : Write graph output in a file
    -p <value> : Define the number of threads used
    -r <value> : Define an upper bound on the RAM used by the algorithm

DORCIS went through some algorithmic changes from LIGHTER, so some of the LIGHTER commands that affect the search algorithm have been omitted (such as `[-l]`). 

All commands should start with the following:
```
./non-lin-search -q -o "S-box"
```
for some 16 character S-box. Here are some example commands used to generate the implementations for the figures.

### Examples ###
- T-Depth and Depth Search of the GIFT S-box:
```
./non-lin-search -q -o "1A4C6F392DB7508E" -t
```
```
./non-lin-search -q -o "1A4C6F392DB7508E"
```

- T-Depth and Depth Search of the PRESENT S-box:
```
./non-lin-search -q -o "C56B90AD3EF84712" -t
```

```
./non-lin-search -q -o "C56B90AD3EF84712"
```

DORCIS will continually search, adding a .c implementation folder whenever it finds a better implementation. So the most recently produced implementation is always the best one.

## Installation to S-box Generation Example ##

* As with typical C++ programs, type `make` onto the terminal to build the code, and make the non-lin-search executable. Once it is done, the program can be run by calling the non-lin-search executable with one of the commands specified above. To find a depth-optimized quantum circuit for the GIFT S-box, as was shown in the paper, one can execute the following command: 
```
./non-lin-search -q -o "1A4C6F392DB7508E"
```

* DORCIS should start writing files that show those quantum circuit implementations. Each time it writes a file, it's more depth optimized than the last one it wrote. And each time it finds a better quantum circuit implementation, it will write two files (a .c file and a .py file).

* The .c file is the LIGHTER output, retaining the same formatting. The circuit implementation in that file can be directly copied and pasted into the [`test_sbox_from_implementation_c.py`](https://github.com/vdasu/lighter-r/blob/master/test_sbox_from_implementation_c.py) file to test whether or not the outputted circuit does correct implement the desired S-box.

* The .py file is the DORCIS [Qiskit](https://qiskit.org/) output, which can be run with Python (provided that the Qiskit and [Matplotlib](https://matplotlib.org/) libraries are installed) to show a visualization of the circuit.

* Further, the decomposition tool can be used to decompose any Qiskit .py output file into its fully decomposed form (to better visualize the depth). Simply change the name of the file stored in the variable at the top of the decomposition tool to the desired Qiskit to-be-decomposed file's name, and run the python code, to write a new file with all the decompositions written out explicitly.

* By repeating this process, one can implement any S-box and verify all findings laid forth in the paper accompanying this code.

## Notes ##

1. DORCIS requires `g++-11`. The Makefile can be adjusted from reading `g++-11` to `g++` for other versions of g++.
2. This code will run until the graph size (which is printed when you call -v) reaches the integer overflow limit. This means that you can leave the code running for a long time to search more boxes, but it is likely that most of the boxes it will find will be bunched together with respect to graph size anyway.
3. DORCIS sets the input, `F[i]`, such that `F[0]` is the most significant bit. So 1 would be represented as `001` or `F[0] = 0`, `F[1] = 0`, `F[2] = 1`.
4. The execution of DORCIS is non-deterministic.

## Recommended Specification ##

* The project is tested with `g++11` on MacOS Monterey.

* As per any other C++ code, in order to run the code, one should enter the terminal in IDE, change directory to this folder (if it does not already default to it), and run `make`. This saves all the changes to the files and creates an executable named `non-lin-search`.


