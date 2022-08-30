add_executable(${PROJECT_NAME}
    main.cpp
    ./hw/DHT11/DHT11.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ./
    ./hw/DHT11
)

target_compile_options(${PROJECT_NAME} PUBLIC
    -Wall
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    -lwiringPi
)

