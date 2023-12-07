# Abelian sandpile model

Based on the input data passed in the command line as arguments, `.bmp` images of the sandpile are generated at a given frequency.

# Command line arguments
- **--input=, -i** - source `.tsv` file with input data (*coordinates* and *number* of grains of sand inside a given cell).  
**Example `.tsv` file data:**  
```
x       y       sand
|       |        |
v       v        v
0	0	1000
-51	48	567
22      1       1000000
```
- **--output=, -o** - output directory with result-images.
- **--max-iter=, -m** - maximum number of algorithm iterations.
- **--freq=, -f** - the frequency at which images are uploaded to the specified directory.

# Example of running the program

`sandpile_model.exe --input=<tsv_file> --output=<dir> -m 1000000 -f 1000` 

![image](image\sandpile_6700000.bmp)
