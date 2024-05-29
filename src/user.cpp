#include <SQLiteCpp/SQLiteCpp.h>
#include "user.h"
#include "logs.h"


bool Users::valid_user(std::string email_address, std::string file_location)
{
  Logs::write_log_data("              function: valid_user, user: " + email_address);

  SQLite::Database db(file_location, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  SQLite::Statement query(db, "SELECT email_address FROM Users");
  
  while (query.executeStep())
  {
    std::string current_email_address = query.getColumn(0);

    if (current_email_address == email_address)
    {
      Logs::write_log_data("              function: valid_user, user: " + email_address + ", return: true");
      return true;
    }
  }
  Logs::write_log_data("              function: valid_user, user: " + email_address + ", return: false");
  
  return false;
}

bool Users::valid_password(std::string email_address, std::string password, std::string file_location)
{
  Logs::write_log_data("              function: valid_password");

  SQLite::Database db(file_location, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  SQLite::Statement query(db, "SELECT password FROM Users Where email_address = ?");
  query.bind(1, email_address);

  while (query.executeStep())
  {
    std::string current_password = query.getColumn(0);

    if (current_password == password)
    {
      Logs::write_log_data("              return: true");
      return true;
    }
  }
  return false;
}
