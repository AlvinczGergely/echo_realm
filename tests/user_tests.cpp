#include <gtest/gtest.h>
#include <SQLiteCpp/SQLiteCpp.h>


#include "../src/user.h"



namespace  
{
    const std::string db_file = "../../db/test.db3";
    const char* email_address = "test@test.com";
    const char* password = "test_password";
    const char* user_name = "Test Gibson";
    const char* cookie = "test_cookie";

    void clear_test_db()
    {
        SQLite::Database db (db_file, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);  
        SQLite::Transaction transaction (db);
        SQLite::Statement query(db, "DELETE from Users");
        query.exec();
        transaction.commit();
    }
    
    
    TEST(user, insert_user)
    {
        Users::insert_user(email_address, password, user_name, db_file);

        SQLite::Database db (db_file, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        SQLite::Statement query(db, "SELECT * FROM Users");

        ASSERT_TRUE(query.executeStep());
        ASSERT_STREQ(email_address, query.getColumn(0));
        ASSERT_STREQ(password, query.getColumn(1));
        ASSERT_STREQ(user_name, query.getColumn(2));
        ASSERT_FALSE(query.executeStep());  

        clear_test_db();
    }

    TEST(user, insert_cookie)
    {
        Users::insert_user(email_address, password, user_name, db_file);

        Users::insert_cookie(email_address, cookie, db_file);

        SQLite::Database db (db_file, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        SQLite::Statement query(db, "SELECT cookie from Users WHERE email_address = ?");
        query.bind(1, email_address);
        query.executeStep();   

        ASSERT_STREQ(cookie, query.getColumn(0));
        ASSERT_FALSE(query.executeStep());
        
        clear_test_db();
    }

    TEST(user, valid_user)
    {
        Users::insert_user(email_address, password, user_name, db_file);

        ASSERT_TRUE(Users::valid_user(email_address, db_file));
        ASSERT_FALSE(Users::valid_user("false_test@test.com", db_file));

        clear_test_db();
    }

    TEST(user, valid_password)
    {
        Users::insert_user(email_address, password, user_name, db_file);
        ASSERT_TRUE(Users::valid_password(email_address, password, db_file));
        ASSERT_FALSE(Users::valid_password(email_address, "false_test_password", db_file));

        clear_test_db();
    }

    TEST(user, email_alredy_taken)
    {
        Users::insert_user(email_address, password, user_name, db_file);

        ASSERT_TRUE(Users::email_alredy_taken(email_address, db_file));
        ASSERT_FALSE(Users::email_alredy_taken("false_test@test.com", db_file));

        clear_test_db();
    }

    TEST(user, check_cookie)
    {
        Users::insert_user(email_address, password, user_name, db_file);
        ASSERT_FALSE(Users::check_cookie(cookie, db_file));
        ASSERT_TRUE(Users::check_cookie("", db_file));

        Users::insert_cookie(email_address, cookie, db_file);

        ASSERT_TRUE(Users::check_cookie(cookie, db_file));
        ASSERT_FALSE(Users::check_cookie("false test cookie", db_file));

        clear_test_db();
    }

    TEST(user, remove_cookie)   
    {
        Users::insert_user(email_address, password, user_name, db_file);
        Users::insert_cookie(email_address, cookie, db_file);
        SQLite::Database db(db_file, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        
        SQLite::Statement query(db, "SELECT cookie from Users WHERE email_address = ?");
        query.bind(1, email_address);
        query.executeStep();   

        ASSERT_STREQ(cookie, query.getColumn(0));
        ASSERT_FALSE(query.executeStep());

        Users::remove_cookie(cookie, db_file);

        SQLite::Statement cookie_query(db, "SELECT * FROM Users");
        ASSERT_TRUE(cookie_query.executeStep());   
        ASSERT_STREQ(email_address, cookie_query.getColumn(0));
        ASSERT_STREQ(password, cookie_query.getColumn(1));
        ASSERT_STREQ(user_name, cookie_query.getColumn(2));
        ASSERT_STREQ("", cookie_query.getColumn(3));
        ASSERT_FALSE(cookie_query.executeStep());
        
        clear_test_db();
    }

}