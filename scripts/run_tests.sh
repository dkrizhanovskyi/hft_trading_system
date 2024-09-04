# scripts/run_tests.sh
#!/bin/bash
set -e
cd build
ctest --output-on-failure
echo "All tests passed successfully!"
