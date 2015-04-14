set(LIB_NAME transcoder)

include_directories(${LIBAVCODEC_INCLUDE_DIR} ${LIBAVFORMAT_INCLUDE_DIR})

aux_source_directory(. SOURCES)

add_library(${LIB_NAME} ${SOURCES})

target_link_libraries(${LIB_NAME} ${LIBAVCODEC_LIBRARY} ${LIBAVFORMAT_LIBRARY})

install(TARGETS ${LIB_NAME} DESTINATION lib)
