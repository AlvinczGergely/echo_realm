#include "logs.h"

#include "iostream"
#include <string>
#include <fstream>
#include <ctime>  
#include <chrono>
#include <string>
  


void Logs::write_log_data(std::string log_info)
{
    time_t now = time(0);
    struct tm tstruct;
    char current_time[80];
    tstruct = *localtime(&now);
    strftime(current_time, sizeof(current_time), "%Y-%m-%d.%X", &tstruct);

    std::ofstream log_file("../../log/log.txt", std::ios::app);

    if (log_file.is_open())
    {
        log_file << current_time;
        log_file << "   " << log_info << std::endl;
        log_file.close();
    }
    else 
    {
        std::cout << "Unable to open file";
    }
}

void Logs::write_log_data(std::string log_info, std::string user_name)
{
    time_t now = time(0);
    struct tm tstruct;
    char current_time[80];
    tstruct = *localtime(&now);
    strftime(current_time, sizeof(current_time), "%Y-%m-%d.%X", &tstruct);

    std::ofstream log_file("../../log/log.txt", std::ios::app);

    if (log_file.is_open())
    {
        log_file << current_time;
        log_file << "   " << log_info;
        log_file << " user name: " << user_name << std::endl;
        log_file.close();
    }
    else 
    {
        std::cout << "Unable to open file";
    }
}

void Logs::start_write_log_data(std::string log_info)
{
    time_t now = time(0);
    struct tm tstruct;
    char current_time[80];
    tstruct = *localtime(&now);
    strftime(current_time, sizeof(current_time), "%Y-%m-%d.%X", &tstruct);

    std::ofstream log_file("../../log/log.txt", std::ios::app);

    if (log_file.is_open())
    {
        log_file << "##################### Indo sail start #####################" << std::endl;
        log_file << current_time;
        log_file << "   " << log_info << std::endl;
        log_file.close();
    }
    else 
    {
        std::cout << "Unable to open file";
    }
}

void Logs::write_log_data_exception(std::string log_info, const std::exception &e)
{
    time_t now = time(0);
    struct tm tstruct;
    char current_time[80];
    tstruct = *localtime(&now);
    strftime(current_time, sizeof(current_time), "%Y-%m-%d.%X", &tstruct);

    std::ofstream log_file("../../log/log.txt", std::ios::app);

    if (log_file.is_open())
    {
        log_file << current_time;
        log_file << "   " << log_info;
        log_file << " exception: " << e.what() << std::endl;
        log_file.close();
    }
    else 
    {
        std::cout << "Unable to open file";
    }
}
