include(FetchContent)

message("Curl")
FetchContent_Declare(
    curl_fetch
    GIT_REPOSITORY https://github.com/curl/curl.git
    GIT_TAG 38bdef0220cfc6c67c7e184255f539e2f04d4291
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(curl_fetch)

add_library(Curl INTERFACE)

target_link_libraries(Curl INTERFACE libcurl)
target_include_directories(Curl INTERFACE ${curl_fetch_SOURCE_DIR}/include)