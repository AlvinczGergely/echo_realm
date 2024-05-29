#ifndef LOGIN_HPP
#define LOGIN_HPP
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

using namespace Pistache;
using Request = Pistache::Rest::Request;
using Response = Pistache::Http::ResponseWriter;


namespace Services
{
    void config_routes(Pistache::Rest::Router& chat_router);
    void is_port_used(int port_num);
    static std::string url_decode(std::string body_str);
    Pistache::Http::Cookie login_cookie_generator(std::string email);
    void get_login_site(const Request &request, Response response);
    void login_handler(const Request &request, Response response);
    void registration_handler(const Request &request, Response response);
    void get_chat_site(const Request &request, Response response);
    static bool is_valid_session(const Request &request);
    void log_out_handler(const Request &request, Response response); 
};

#endif
