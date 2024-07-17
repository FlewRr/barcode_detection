rm -r build
mkdir build
cmake -S . -B build/
cd build/
make
./main /home/sfleur/barcode_detection/barcode_detection/Image /home/sfleur/barcode_detection/barcode_detection/processed_images