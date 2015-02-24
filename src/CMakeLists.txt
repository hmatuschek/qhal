SET(qhal_SOURCES qhal.cc main.cc)
SET(qhal_MOC_HEADERS )
SET(qhal_HEADERS qhal.hh ${qhal_MOC_HEADERS})

qt5_wrap_cpp(qhal_MOC_SOURCES ${qhal_MOC_HEADERS})
#qt5_add_resources(qhal_RCC_SOURCES ../shared/resources.qrc)

add_executable(qhal ${qhal_SOURCES} ${qhal_MOC_SOURCES} ${qhal_RCC_SOURCES})
target_link_libraries(qhal ${LIBS})
