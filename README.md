# Cameo

Cameo is a C++ application for controlling and displaying camera frames and handling events on them.

## Usage

### To compile and execute the application, use the following rules:

1. Generate Makefiles
   
        cmake --preset release

2. Compile files

        cmake --build --preset release

3. Run the application

        ./build/release/bin/cameo

### Or use the run.sh

    sh run.sh

## Features

Cameo is an application for controlling and showing camera frames while also providing event controls. The following events can be triggered:

- **ESC**: Close application.
- **TAB**: Start/stop writing video.
- **Space**: Write image.
- **'m'**: Set/unset frames to mirrored state.

