git clone https://github.com/Thaylo/TMatrix.git
mv TMatrix/*.h .
reset
make clean -i
make
./bin/filtering > script.m
octave script.m
rm TMatrix -rf