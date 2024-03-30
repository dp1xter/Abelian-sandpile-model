# Abelian sandpile model

Based on the input data passed in the command line as arguments, `.bmp` images of the [sandpile](https://en.wikipedia.org/wiki/Abelian_sandpile_model) are generated at a given frequency. 

**4-bit color encoding is used.**

# Command line arguments
- **--input=, -i** - source `.tsv` file with input data (*coordinates* and *number* of grains of sand inside a given cell).  
**Example `.tsv` file data:**  
```
x       y       sand
|       |        |
v       v        v
-----------------------
0	0	1000
-51	48	567
22      1       1000000
```
- **--output=, -o** - output directory with result-images.
- **--max-iter=, -m** - maximum number of algorithm iterations.
- **--freq=, -f** - the frequency at which images are uploaded to the specified directory.

# Requirements
According to the requirements of lab-work, the use of the STL is prohibited.

# Example of running the program

`sandpile_model.exe --input=<tsv_file> --output=<dir> -m 1000000 -f 1000`  

[<img src="gif_example\sandpile.gif" width="500"/>](src\sandpile.gif)
