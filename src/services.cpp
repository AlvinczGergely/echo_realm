#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

#include "services.h"
#include "logs.h"

void Services::config_routes(Pistache::Rest::Router& chat_router)
{
    Logs::write_log_data("              function: config_routes");

    Pistache::Rest::Routes::Get(chat_router, "/", Pistache::Rest::Routes::bind(&Services::get_login_site));
}

void Services::is_port_used(int port_num)
{
   int sockfd = socket(AF_INET, SOCK_STREAM, 0);
   struct sockaddr_in serv_addr;
   bzero(&serv_addr, sizeof (serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons (port_num);

   if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) >= 0) 
   {
        close(sockfd);
        Logs::write_log_data("              function: is_port_used --> Socket connetcted sucesfully, port is free!");
   } 
   else 
   {
        close (sockfd);
        Logs::write_log_data("              function: is_port_used --> Socket cant connect, the port is used.");
   }
}

void Services::get_login_site(const Request &request, Response response)
{
    Logs::write_log_data(" GET request, function: get_login_site");

        response.send(Http::Code::Ok, "server is running");
}
