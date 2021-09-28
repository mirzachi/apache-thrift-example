cmake_minimum_required(VERSION 3.14)

# make the ExternalProject commands available
include(ExternalProject)

# download, configure, build and install the dependency
# note: The install location is set to the build folder
ExternalProject_Add(
        apache-thrift
        GIT_REPOSITORY https://github.com/apache/thrift.git
        GIT_TAG 8317ec43ea2425b6f8e24e4dc4f5b2360f717eb4 # Commit hash for 0.15.0
        GIT_PROGRESS TRUE
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/install
        -DCMAKE_BUILD_TYPE=Debug
        -DBUILD_TESTING=OFF
        -DBUILD_NODEJS=OFF
        -DBUILD_JAVASCRIPT=OFF
        -DBUILD_JAVA=OFF
        -DBUILD_C_GLIB=OFF
        -DWITH_AS3=OFF
        -DWITH_ZLIB=OFF
        -DWITH_LIBEVENT=OFF
        -DWITH_QT5=OFF
        -DWITH_OPENSSL=OFF
        -DCMAKE_POSITION_INDEPENDENT_CODE=ON
)
