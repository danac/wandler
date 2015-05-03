set(EXE_NAME ${CMAKE_PROJECT_NAME})

file(GLOB QRCs *.qrc)
qt4_add_resources(RESOURCES ${QRCs})

file(GLOB UIs *.ui)
qt4_wrap_ui(INTERFACES ${UIs})

aux_source_directory(. SOURCES)
add_executable(${EXE_NAME} ${SOURCES} ${INTERFACES} ${RESOURCES})

add_custom_command(TARGET ${EXE_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E make_directory
                   ${CMAKE_CURRENT_BINARY_DIR}/contrib)

add_custom_command(TARGET ${EXE_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E create_symlink
                   ${CMAKE_SOURCE_DIR}/contrib/${FFMPEG_EXE_NAME}
                   ${CMAKE_CURRENT_BINARY_DIR}/contrib/${FFMPEG_EXE_NAME})

target_link_libraries(${EXE_NAME} Qt4::QtGui)

install(TARGETS ${EXE_NAME} DESTINATION bin)
if(FFMPEG_EXE)
    install(FILES ${CMAKE_SOURCE_DIR}/contrib/${FFMPEG_EXE_NAME} DESTINATION contrib)
endif(FFMPEG_EXE)
