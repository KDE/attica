macro(ATTICA_TESTS)
    foreach(_testname ${ARGN})
        qt4_generate_moc(${_testname}.cpp ${CMAKE_CURRENT_BINARY_DIR}/${_testname}.moc)
        include_directories(${attica_BINARY_DIR}/lib)
        add_executable(${_testname} ${_testname}.cpp ${_testname}.moc)
        target_link_libraries(${_testname} ${QT_QTTEST_LIBRARY} ${QT_QTCORE_LIBRARY} attica)
        add_test(${_testname} ${CMAKE_CURRENT_BINARY_DIR}/${_testname})
    endforeach(_testname)
endmacro(ATTICA_TESTS)

ATTICA_TESTS(persontest )
#             attributestest)

add_subdirectory(projecttest)
