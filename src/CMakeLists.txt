cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 11)

find_package(Protobuf REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(ZeroMQ REQUIRED)

include_directories(${Protobuf.INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(PROTO common/message.proto)

protobuf_generate_cpp(PROTO_SRC PROTO_HEADERS ${PROTO})
protobuf_generate_cpp(PROTO_SRC PROTO_HEADERS EXPORT_MACRO DLL_EXPORT ${PROTO})
protobuf_generate_cpp(PROTO_SRC PROTO_HEADERS DESCRIPTORS PROTO_DESCS ${PROTO})

set_source_files_properties(${PROTO_SRC} ${PROTO_HEADERS} PROPERTIES GENERATED
                                                                     TRUE)

add_executable(pb-demo-client client/main.cc ${PROTO_SRC} ${PROTO_HEADERS})
add_executable(pb-demo-server server/main.cc ${PROTO_SRC} ${PROTO_HEADERS})

target_link_libraries(pb-demo-client ${Protobuf_LIBRARIES} zmq)
target_link_libraries(pb-demo-server ${Protobuf_LIBRARIES} zmq)
