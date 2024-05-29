#ifndef GENERATOR_HPP
#define GENERATOR_HPP

# include <string>
#include "pugixml/src/pugixml.hpp"


namespace Generators
{

struct name_variables
{
  std::string first_name;
  std::string last_name;
  std::string full_name;
};

  std::string random_number_generator(int digit_number);

  name_variables name_generator();

  std::string email_adress_generator();

};


#endif