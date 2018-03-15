aux_source_directory(. SRC_LIST)
add_library(nanorpc_util ${SRC_LIST}) 
set_target_properties(nanorpc_util PROPERTIES LINKER_LANGUAGE CXX)
