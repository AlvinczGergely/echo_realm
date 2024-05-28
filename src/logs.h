#ifndef LOGS_HPP
#define LOGS_HPP

#include "iostream"

class Logs 
{
public:

    static void start_write_log_data(std::string log_info);
    static void write_log_data(std::string log_info);
    static void write_log_data(std::string log_info, std::string user_name);
    static void write_log_data_exception(std::string log_info, const std::exception &e);
};


#endif




