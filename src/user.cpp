#include <SQLiteCpp/SQLiteCpp.h>
#include "user.h"
#include "logs.h"


void Users::insert_user(std::string email_address, std::string password, std::string user_name, std::string file_location) 
{
  Logs::write_log_data("              function: insert_user");

  SQLite::Database db(file_location, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  SQLite::Transaction transaction (db);
  SQLite::Statement query (db, "INSERT INTO Users (email_address, password, user_name, cookie) VALUES (?, ?, ?, ?)");
  query.bind(1, email_address);
  query.bind(2, password);
  query.bind(3, user_name);
  query.bind(4);

  query.exec();
  transaction.commit(); 
}

void Users::insert_cookie(std::string email_address, std::string cookie, std::string file_location)
{
  Logs::write_log_data("              function: insert_cookie_into_users");

  SQLite::Database db(file_location, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  SQLite::Transaction transaction (db);
  SQLite::Statement query (db, "UPDATE Users SET cookie = ? where email_address = ?");
  query.bind(1, cookie);
  query.bind(2, email_address);

  query.exec();
  transaction.commit();
}

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

bool Users::check_cookie(std::string cookie, std::string file_location)
{
  Logs::write_log_data("              function: check_cookie");

  SQLite::Database db(file_location, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  SQLite::Statement query(db, "SELECT cookie FROM Users");

  while (query.executeStep())
  {
    std::string database_cookie = query.getColumn(0);

    if (database_cookie == cookie)
    {
      return true;
    }
  }
  return false;
}

bool Users::remove_cookie(std::string cookie_value, std::string file_location)
{
  Logs::write_log_data("              function: delete_cookie");

  SQLite::Database db(file_location, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

  SQLite::Transaction transaction (db);
  SQLite::Statement query (db, "UPDATE Users SET cookie = NULL where cookie = ?");
  query.bind(1, cookie_value);

  query.exec();
  transaction.commit();

  return true;
}
