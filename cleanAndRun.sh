reset
make clean -i
make
./bin/filtering > script.m
octave script.m
