function(set_compile_options target_name)
    if(MSVC)
        target_compile_options(${target_name} PRIVATE /W4 /WX)
    else()
        target_compile_options(${target_name} PRIVATE -Wall -Wextra -Werror -pedantic
        -lopencv_core
        -lopencv_imgproc
        -lopencv_highgui
        -lopencv_ml
        -lopencv_video
        -lopencv_features2d
        -lopencv_calib3d
        -lopencv_objdetect
        -lopencv_contrib
        -lopencv_legacy
        -lopencv_flann
        )
    endif()

    set_target_properties(
        ${target_name}
        PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
    )

    if(CLANG_TIDY_EXE)
    set_target_properties(
        ${target_name}
        PROPERTIES
        CXX_CLANG_TIDY ${CLANG_TIDY_EXE}
    )
    endif()
endfunction()
