This file should contain the CSV encoder and scan files.

The playback data is read from a CSV file.
The first three columns contain the binary motor encoder signals A, B and Z.
The fourth column contains the signal voltage that is to be presented to the PDC via the 5M1 resistor on the LDA (0 to 5V).
The fifth column is used to separate the test data into bundles to indicate suitable break points during playback.

Optionally the first lines of the file contains metadata as key=value pairs on lines starting with a '#'.
There is then a single header line which does not start with a '#'.
The rest of the file contains data lines.

# rate=1000000Hz
A (binary), B (binary), Z (binary), signal (V fed to PDC via 5M1R on LDA), separate bundles (binary)
0,0,0,2.50000,0
1,0,0,2.51740,0
1,1,0,2.51714,0
...
0,0,0,2.51785,1
1,0,0,2.51740,1
1,1,0,2.51714,1
...
0,0,0,2.51785,0
1,0,0,2.51740,0
1,1,0,2.51714,0

A caching mechanism is available whereby a numpy NPZ file is written following a successful load of the CSV file.
Further loads of the same file will only need to process the header metadata and can load the raw data arrays from the NPZ
file.
The file size and timestamps are checked to make sure the CSV file has not been updated since the NPZ file was written.

