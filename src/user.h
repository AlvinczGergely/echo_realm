#ifndef USERS_HPP
#define USERS_HPP

namespace Users
{
  bool valid_user(std::string email_address, std::string file_location);
  bool valid_password(std::string email_address, std::string password, std::string file_location);
};



#endif