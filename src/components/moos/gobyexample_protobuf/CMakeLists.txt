protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${CMAKE_CURRENT_BINARY_DIR} simple_status.proto)
add_library(gobyexample_protobuf SHARED ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(gobyexample_protobuf
  goby)

