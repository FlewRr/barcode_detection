rm -r build
mkdir build
cmake -S . -B build/
cd build/
make
./main /home/rafiz/Desktop/barcode_detection/barcode_detection/Image /home/rafiz/Desktop/barcode_detection/barcode_detection/processed_images