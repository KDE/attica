macro(ATTICA_AUTOTESTS)
    foreach(_testname ${ARGN})
        add_executable(${_testname} ${_testname}.cpp)
        target_link_libraries(${_testname} Qt5::Test ${ATTICA_LIB_SONAME})
        add_test(attica-${_testname} ${CMAKE_CURRENT_BINARY_DIR}/${_testname})
    endforeach(_testname)
endmacro(ATTICA_AUTOTESTS)

ATTICA_AUTOTESTS(
  persontest
# attributestest
)
