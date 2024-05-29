#include "generator.h"
#include "logs.h"
#include <string>

std::string Generators::random_number_generator(int digit_number)  
{
  Logs::write_log_data("              function: random_number_generator");

  srand(time(NULL));

  int num = rand() % 89999 + 10000;

  return std::to_string(num);
}

