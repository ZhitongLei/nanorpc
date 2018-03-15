aux_source_directory(. SRC_LIST)
add_library(nanorpc_net ${SRC_LIST})
target_link_libraries(nanorpc_net nanomsg)
