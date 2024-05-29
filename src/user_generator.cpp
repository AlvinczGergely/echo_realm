#include <yaml.h>
#include <yaml-cpp/yaml.h>

#include "generator.h"
#include "user.h"
#include "logs.h"
#include <ctime>


int main()
{
    Logs::write_log_data("              function: user_generator");

    YAML::Node config = YAML::LoadFile("../../src/user_generator.yaml");

    int count = config["Users"]["count"].as<int>();
    std::string db_location = "../../db/Users.db3";

    std::srand(static_cast<unsigned int>(std::time(0)));

    int i = 0;
    while(i < count)
    {
        std::string email = Generators::email_adress_generator();
        std::string random_number = Generators::random_number_generator(6);
        std::string full_name = Generators::name_generator().full_name;

        if(!Users::email_alredy_taken(email, db_location))
        {
            std::srand(static_cast<unsigned int>(std::time(0)));
            Users::insert_user(email, random_number, full_name, db_location);

            i++;
        }
    }


    return 0;
}