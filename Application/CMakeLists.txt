set(
    App_source
    chapter3_led_driver.c
    chapter3_led_driver.h
)

add_library(
    application_library STATIC
    ${App_source}
)

target_include_directories(
    application_library PUBLIC
    ${CMAKE_SOURCE_DIR}/Application
    ${CMAKE_SOURCE_DIR}/Source
)