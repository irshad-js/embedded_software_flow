set(
    Test_source
    test_main.cpp
    chapter2_test_sprintf.cpp
    chapter3_test_led_driver.cpp
    chapter4_test_led_driver_continued.cpp
    runtime_error_stub.h
    runtime_error_stub.c
    runtime_error.h
    chapter8_test_lightsched.cpp
    lightcontroller_spy_test.cpp
    LightControllerSpy.h
    LightControllerSpy.c
    FakeTimeService.h
    FakeTimeService.c
    FakeTimeService_test.cpp
    Fakerandom_minute.c
    Fakerandom_minute.h
)

add_executable(
    Test_app 
    ${Test_source}
)

target_include_directories(
    Test_app PUBLIC
    ${CMAKE_SOURCE_DIR}/Source
    ${CMAKE_SOURCE_DIR}/Application
)

target_link_libraries(
    Test_app PUBLIC
    application_library
    CppUTest::CppUTest
)