rm -r build
mkdir build
cmake -S . -B build/
cd build/
make -j 16
./main /home/rafiz/Desktop/barcode_detection/barcode_detection/Image /home/rafiz/Desktop/barcode_detection/barcode_detection/Markup