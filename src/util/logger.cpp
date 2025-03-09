#include "logger.hpp"

namespace loader
{
    void logger::clear_log()
    {
        std::ofstream log_file("loader.log", std::ios::trunc);
        if (log_file.is_open())
            log_file.close();
    }

    void logger::log(std::string string)
    {
        auto now = std::chrono::system_clock::now();
        auto time_point = std::chrono::system_clock::to_time_t(now);
        std::tm tm;
        localtime_s(&tm, &time_point);

        std::stringstream time_stream;
        time_stream << std::put_time(&tm, "%H:%M:%S");

        std::cout << "[" << time_stream.str() << "] " << string.data() << std::endl;

        std::ofstream log_file("loader.log", std::ios::app);
        if (log_file.is_open())
        {
            log_file << "[" << time_stream.str() << "] " << string.data() << std::endl;
            log_file.close();
        }
        else
            std::cerr << "Unable to open log file" << std::endl;
    }
}