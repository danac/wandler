set(EXE_NAME ${CMAKE_PROJECT_NAME})

file(GLOB QRCs *.qrc)
qt4_add_resources(RESOURCES ${QRCs})

file(GLOB UIs *.ui)
qt4_wrap_ui(INTERFACES ${UIs})

aux_source_directory(. SOURCES)
add_executable(${EXE_NAME} ${SOURCES} ${INTERFACES} ${RESOURCES})

target_link_libraries(${EXE_NAME} Qt4::QtGui)

install(TARGETS ${EXE_NAME} DESTINATION bin)
