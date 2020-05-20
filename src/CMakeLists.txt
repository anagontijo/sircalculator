add_executable(sir_calculator main.cpp mainwindow.cpp sir_interface.cpp sir_menu.cpp sir_plot.cpp sir_method.cpp r4_method.cpp)
target_link_libraries(sir_calculator Qt5::Core Qt5::Widgets Qt5::Charts Qt5::Gui ${ZLIB_LIBRARIES})

install(TARGETS sir_calculator DESTINATION bin COMPONENT binaries)
