#!/bin/bash

SOURCE_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

conan config install "$SOURCE_DIR/profiles/settings.yml"
conan install "$SOURCE_DIR" --install-folder "$SOURCE_DIR/build" --profile "$SOURCE_DIR/profiles/clang"
conan build "$SOURCE_DIR" --build-folder "$SOURCE_DIR/build"