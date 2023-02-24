This is a tool that produces depth and T-depth optimized 3x3 and 4x4 S-Boxes given a desired target bijective S-Box. This tool is built off of the meet-in-the-middle algorithm from [LIGHTER](https://eprint.iacr.org/2017/101), and the quantum circuit extension of LIGHTER known as [LIGHTER-R](https://ieeexplore.ieee.org/abstract/document/9088027). 

S-Boxes can be passed in using their "LUT" format. This is an 8 or 16 character long string (for 3 and 4 bit S-boxes respectively) such as "196F7C82AED043B5" where the character in the i-th index maps to the i-th input (so 0123456789abcdef is the 4-bit identity).

S-Boxes can also be passed in using their "Bit Slice" format. This is an 8 or 19 character long string (for 3 and 4 bit S-boxes respectively). The process on how to convert from LUT to Bit Slice is explained in the paper, but the strings must include the spaces. 
For example, "1e 39 6a" is the bit slice form of "01367452".

As per with any C++ file, the first thing you want to do after downloading and unzipping this code is to run change directory to this folder and run "make". You can then start running the code with "./non-lin-search" followed by the arguments below.

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
    -i <function> : Define start function [Defaults to Identity]

Current version went through some minor algorithmic changes from LIGHTER, so some of the LIGHTER commands that affect the search algorithm have been omitted (such as [-l]). 

All commands should start with the following:

./non-lin-search -q -o "S-Box"

for some 16 character S-Box. Here are some example commands used to generate the implementations for the figures.

./non-lin-search -q -o "1A4C6F392DB7508E" -t

./non-lin-search -q -o "1A4C6F392DB7508E"

T-Depth and Depth Search of the GIFT S-Box.

./non-lin-search -q -o "C56B90AD3EF84712" -t

./non-lin-search -q -o "C56B90AD3EF84712"

T-Depth and Depth Search of the PRESENT S-Box.

Code will continually search, adding a .c implementation folder whenever it finds a better implementation. So the most recently produced implementation is always the best one.

## Notes ##

1. Compiling requires version `g++11`.
2. This code will run until the graph size (which is printed when you call -v) reaches the integer overflow limit. This means that you can leave the code running for a long time to search more boxes, but it is likely that most of the boxes it will find will be bunched together with respect to graph size anyway.
3. The code sets the input, F[i], such that F[0] is the most significant bit. So 1 would be represented as 001 or F[0],F[1] = 0, F[2]=1.

## Required Specs ##
This is currently running on g++-11. The code before modifications only had "g++" on the top line of the Makefile rather than "g++-11" and I believe the previous developers had that working on Linux. 

As per any other C++ code, in order to run the code you should simply enter the terminal in your IDE, change directory to this folder (if it doesn't already default to it), and run "make". This saves all the changes to the files and creates an executable which can be called, named "non-lin-search". It is executed with the command ./non-lin-search followed by the arguments you'll need to pass in.

Please feel free to suggest/contribute new features or fix bugs or add documentation.
