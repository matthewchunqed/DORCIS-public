# DORCIS #
DORCIS is a tool that produces depth and T-depth optimized 3 × 3 and 4 × 4 S-Boxes given a desired target bijective S-Box. This tool is built off of the meet-in-the-middle algorithm from [LIGHTER](https://eprint.iacr.org/2017/101), and the quantum circuit extension of LIGHTER known as [LIGHTER-R](https://ieeexplore.ieee.org/abstract/document/9088027). 

S-Boxes can be passed in using their "LUT" format. This is an 8 or 16 character long string (for 3 and 4 bit S-boxes respectively) such as "196F7C82AED043B5" where the character in the i-th index maps to the i-th input (so "0123456789ABCDEF" refers to the 4-bit identity S-box).

S-Boxes can also be passed in using their "Bit Slice" format. This is an 8 or 19 character long string (for 3 and 4 bit S-boxes respectively). The process on how to convert from LUT to Bit Slice is explained in the paper, but the strings must include the spaces. For example, "1e 39 6a" is the bit slice form of "01367452".

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
./non-lin-search -q -o "S-Box"
```
for some 16 character S-Box. Here are some example commands used to generate the implementations for the figures.

### Examples ###
- T-Depth and Depth Search of the GIFT S-Box:
```
./non-lin-search -q -o "1A4C6F392DB7508E" -t
```
```
./non-lin-search -q -o "1A4C6F392DB7508E"
```

- T-Depth and Depth Search of the PRESENT S-Box:
```
./non-lin-search -q -o "C56B90AD3EF84712" -t
```

```
./non-lin-search -q -o "C56B90AD3EF84712"
```

DORCIS will continually search, adding a .c implementation folder whenever it finds a better implementation. So the most recently produced implementation is always the best one.

## Installation to S-Box Generation Example ##

<!-- On Github (website), click the green "Code" > Download as Zip button to download the entire DORCIS file as a Zip. Then, extract the contents of the zipped file into a new folder (which can typically be done by double clicking on the zipped folder). The zipped file can now be deleted. -->

<!-- Install `g++-11` onto the desired computer, which can be done using Homebrew by typing `brew install g++-11` into the Terminal (Mac) or Command Prompt (Windows). Now, using an IDE of choice, open the entire DORCIS-master unzipped folder into the IDE. Then, open the terminal on that IDE. Ensure the terminal says /DORCIS-master or otherwise indicates that the directory in use is the entire DORCIS folder. If it isn't, change its directory to the DORCIS file by typing "cd /DORCIS-master", or whatever path there is to the DORCIS folder. -->

<!--If it's difficult to find the path to change directory into the DORCIS-master folder, one can shift+right click (on Windows), or option+right click (on Mac) on the DORCIS folder and click "copy absolute path" to copy the path to change the IDE terminal's directory to.-->

<!-- Now, the code is ready to be built and ran.--> As with typical C++ programs, type `make` onto the terminal to build the code, and make the non-lin-search executable. Once it is done, the program can be run by calling the non-lin-search executable with one of the commands specified above. To find a depth-optimized quantum circuit for the GIFT S-Box, as was shown in the paper, one can execute the following command:

```
./non-lin-search -q -o "1A4C6F392DB7508E"
```

And DORCIS would start writing files that show those quantum circuit implementations. Each time it writes a file, it's more depth optimized than the last one it wrote. And each time it finds a better quantum circuit implementation, it will write two files: a .c file and a .py file.

The .c file is the LIGHTER output, retaining the same formatting. The circuit implementation in that file can be directly copied and pasted into the [`test_sbox_from_implementation_c.py`](https://github.com/vdasu/lighter-r/blob/master/test_sbox_from_implementation_c.py) file to test whether or not the outputted circuit does correct implement the desired S-Box.

The .py file is the DORCIS [Qiskit](https://qiskit.org/) output, which can be run with Python (provided that you have installed the Qiskit and Matplotlib libraries) to show a visualization of the circuit.

Further, the decomposition tool can be used to decompose any Qiskit .py output file into its fully decomposed form (to better visualize the depth). Simply change the name of the file stored in the variable at the top of the decomposition tool to the desired Qiskit to-be-decomposed file's name, and run the python code, to write a new file with all the decompositions written out explicitly.

By repeating this process, one can implement any S-Box and verify all findings laid forth in the paper accompanying this code.

## Notes ##

1. DORCIS requires `g++-11`. The Makefile can be adjusted from reading `g++-11` to `g++` for other versions of g++.
2. This code will run until the graph size (which is printed when you call -v) reaches the integer overflow limit. This means that you can leave the code running for a long time to search more boxes, but it is likely that most of the boxes it will find will be bunched together with respect to graph size anyway.
3. DORCIS sets the input, `F[i]`, such that `F[0]` is the most significant bit. So 1 would be represented as `001` or `F[0] = 0`, `F[1] = 0`, `F[2] = 1`.

## Recommended Specification ##
<!--I am currently running this on g++-11, on macOS Monterey. The code before modifications only had "g++" on the top line of the Makefile rather than "g++-11" and I believe the previous developers had that working on Linux. -->
The project is tested with `g++11` on MacOS Monterey.

As per any other C++ code, in order to run the code, one should enter the terminal in IDE, change directory to this folder (if it doesn't already default to it), and run `make`. This saves all the changes to the files and creates an executable which can be called, named `non-lin-search`.

<!--Please feel free to suggest/contribute new features or fix bugs or add documentation.-->
