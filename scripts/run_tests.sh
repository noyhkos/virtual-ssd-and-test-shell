#!/bin/bash

cd "$(dirname "$0")/.." || exit 1

echo "=== Building Test Script ==="
make -C build clean
make -C build

echo -e "\n=== Running TestApp1 ==="
./bin/testScript --testapp1 && echo "TestApp1: PASS" || echo "TestApp1: FAIL"

echo -e "\n=== Running TestApp2 ==="
./bin/testScript --testapp2 && echo "TestApp2: PASS" || echo "TestApp2: FAIL"
