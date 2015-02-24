SET(libqhal_SOURCES qhal.cc)
SET(libqhal_HEADERS qhal.hh)

add_library(libqhal SHARED ${libqhal_SOURCES} ${libqhal_RCC_SOURCES})
set_target_properties(libqhal PROPERTIES OUTPUT_NAME sdr)
set_target_properties(libqhal PROPERTIES DEPENDS libqhal_HEADERS)
set_target_properties(libqhal PROPERTIES VERSION
  "${libqhal_VERSION_MAJOR}.${libqhal_VERSION_MINOR}.${libqhal_VERSION_PATCH}")
set_target_properties(libqhal PROPERTIES SOVERION "${libqhal_VERSION_MAJOR}")
set_target_properties(libqhal PROPERTIES MACOSX_RPATH "${CMAKE_INSTALL_RPATH}")
set_target_properties(libqhal PROPERTIES INSTALL_NAME_DIR ${CMAKE_INSTALL_FULL_LIBDIR})
target_link_libraries(libqhal ${LIBS})

add_executable(qhal main.cc)
target_link_libraries(qhal ${LIBS} libqhal)

install(TARGETS libqhal DESTINATION ${CMAKE_INSTALL_LIBDIR})
INSTALL_HEADERS_WITH_DIRECTORY("${libqhal_HEADERS}" "${CMAKE_INSTALL_INCLUDEDIR}")

