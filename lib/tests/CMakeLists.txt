macro(ATTICA_TESTS)
    foreach(_testname ${ARGN})
        qt4_wrap_cpp(moc ${_testname}.cpp)
        add_executable(${_testname} ${_testname}.cpp)
        target_link_libraries(${_testname} ${QT_QTTEST_LIBRARY} ${QT_QTCORE_LIBRARY} attica)
        add_test(${_testname} ${CMAKE_CURRENT_BINARY_DIR}/${_testname})
    endforeach(_testname)
endmacro(ATTICA_TESTS)

ATTICA_TESTS(persontest
             attributestest)

