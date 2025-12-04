include(FetchContent)

message("Curl")
FetchContent_Declare(
    Curl
    GIT_REPOSITORY https://github.com/curl/curl.git
    GIT_TAG 38bdef0220cfc6c67c7e184255f539e2f04d4291
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(Curl)