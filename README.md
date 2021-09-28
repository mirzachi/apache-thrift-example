# apache-thrift-example
Simple example of integrating Apache Thrift with CMake

## Build Thrift

First install Thrift with CMake with:

```bash
# For Python bindings necessary
sudo apt-get install python-dev   # for python2.x installs
sudo apt-get install python3-dev  # for python3.x installs
pip install thrift

cmake -S apache-thrift -B apache-thrift/build --log-level=VERBOSE
cmake --build apache-thrift/build --parallel 8 --verbose
cmake --install apache-thrift/build
```

## Build server

```bash
cmake -S . -B build
cmake --build build --parallel 8 --verbose
```

## Execution

Start C++ server:
```bash
./build/server
```

Start Python client:

Start C++ server:
```bash
python3 client.py
```

