# scripts/build.sh
#!/bin/bash
set -e
mkdir -p build
cd build
cmake ..
make
echo "Build completed successfully!"
