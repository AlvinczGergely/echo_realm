#include "generator.h"
#include "logs.h"
#include <vector>
#include <random>
#include <string>
#include "pugixml/src/pugixml.hpp"

std::string Generators::random_number_generator(int digit_number)  
{
  Logs::write_log_data("              function: random_number_generator");

  srand(time(NULL));

  int num = rand() % 89999 + 10000;

  return std::to_string(num);
}

Generators::name_variables Generators::name_generator()
{
  Logs::write_log_data("              function: name_generator");

  pugi::xml_document doc_one;                                
  pugi::xml_document doc_two;

  pugi::xml_parse_result result_first_name = doc_one.load_file("../../src/XML_test_files/first_names.xml");       
  pugi::xml_parse_result result_last_name = doc_two.load_file("../../src/XML_test_files/last_names.xml");  

  pugi::xml_node first_names = doc_one.child("first_names");         
  pugi::xml_node last_names = doc_two.child("last_names");

  std::vector<std::string> first_names_vec;
  std::vector<std::string> last_names_vec;

  for(auto name_node = first_names.child ("name"); name_node; name_node = name_node.next_sibling())
  {
    first_names_vec.push_back(name_node.text().as_string ()); 
  }

  for(auto name_node = last_names.child("name"); name_node; name_node = name_node.next_sibling())
  {
    last_names_vec.push_back(name_node.text().as_string ()); 
  }

  srand (time(NULL));

  std::string ran_first_name(first_names_vec[rand() % first_names_vec.size()]);  
  std::string ran_last_name(last_names_vec[rand() % last_names_vec.size()]); 
  std::string ran_full_name = ran_first_name + " " + ran_last_name; 

  name_variables result = {ran_first_name, ran_last_name, ran_full_name};

  return result;
} 


std::string Generators::email_adress_generator()
{
  Logs::write_log_data("              function: email_adress_generator");

  pugi::xml_document doc_one;                                
  pugi::xml_document doc_two;


  pugi::xml_parse_result result_first_name = doc_one.load_file("../../src/XML_test_files/first_names.xml"); 
  pugi::xml_parse_result result_last_name = doc_two.load_file("../../src/XML_test_files/last_names.xml");

  pugi::xml_node first_names = doc_one.child("first_names");
  pugi::xml_node last_names = doc_two.child("last_names");

  std::vector<std::string> first_names_vec;
  std::vector<std::string> last_names_vec;

  for(auto name_node = first_names.child ("name"); name_node; name_node = name_node.next_sibling())
  {
    first_names_vec.push_back(name_node.text().as_string()); 
  }

  for(auto name_node = last_names.child("name"); name_node; name_node = name_node.next_sibling())
  {
    last_names_vec.push_back(name_node.text().as_string()); 
  }

  srand(time(NULL));

  std::string ran_first_name (first_names_vec[rand() % first_names_vec.size()]);  
  std::string ran_last_name (last_names_vec[rand() % last_names_vec.size()]);

  std::string email_adress = ran_first_name + '.' +  ran_last_name + '@' + "gmail.com";

  return email_adress;
}

