# protobuf-demo-cpp

A short sample on sending protobuf messages with C++ and CMake. The actual
method of sending messages is irrelevant as long as you can guarantee the start
and end address of a protobuf payload. This sample uses ZMQ.

The directory structure is a rough sketch, but I think the separation of
`client`, `server`, and `common` makes sense - especially putting the Protobuf
schema in `common`. The actual CMake structure could probably be improved
though.

## Setup

```
nix develop
mkdir build
cd build
cmake .. && make
./src/pb-demo-server &
./src/pb-demo-client
```

If you don't use Nix, see `flake.nix` for assumed dependencies.
