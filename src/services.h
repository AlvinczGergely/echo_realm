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
    void get_login_site(const Request &request, Response response);
};

#endif
