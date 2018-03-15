add_executable(rpc_client client.cpp)
target_link_libraries(rpc_client nanorpc)

add_executable(rpc_server test_server.cpp)
target_link_libraries(rpc_server nanorpc)
