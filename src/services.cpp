#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

#include "user.h" 
#include "generator.h"
#include "services.h"
#include "logs.h"
#include <fstream>

void Services::config_routes(Pistache::Rest::Router& chat_router)
{
    Logs::write_log_data("              function: config_routes");

    Pistache::Rest::Routes::Get(chat_router, "/", Pistache::Rest::Routes::bind(&Services::get_login_site));
    Pistache::Rest::Routes::Post(chat_router, "/login", Pistache::Rest::Routes::bind(&Services::login_handler));
    Pistache::Rest::Routes::Get(chat_router, "/chatsite", Pistache::Rest::Routes::bind(&Services::get_chat_site));
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

std::string Services::url_decode(std::string body_str) 
{
    Logs::write_log_data("              function: url_decode");

    std::regex reg_obj_space("%20");
    body_str = std::regex_replace(body_str, reg_obj_space, " ");

    std::regex reg_obj_at("%40");
    body_str = std::regex_replace(body_str, reg_obj_at, "@");

    std::regex reg_obj_and("%26");
    body_str = std::regex_replace(body_str, reg_obj_and, "&");

    std::regex reg_obj_dollar("%27");
    body_str = std::regex_replace(body_str, reg_obj_dollar, "$");

    std::regex reg_obj_exclam("%21");
    body_str = std::regex_replace(body_str, reg_obj_exclam, "!");

    std::regex reg_obj_plus("%2B");
    body_str = std::regex_replace(body_str, reg_obj_plus, "+");

    std::regex reg_obj_comma("%2C");
    body_str = std::regex_replace(body_str, reg_obj_comma, ",");

    std::regex reg_obj_per("%3A");
    body_str = std::regex_replace(body_str, reg_obj_per, "/");

    std::regex reg_obj_t_points("%3B");
    body_str = std::regex_replace(body_str, reg_obj_t_points, ":");

    std::regex reg_obj_e_comma("%3D");
    body_str = std::regex_replace(body_str, reg_obj_e_comma, ";");

    std::regex reg_obj_eq("%24");
    body_str = std::regex_replace(body_str, reg_obj_eq, "=");

    std::regex reg_obj_question_m("%3F");
    body_str = std::regex_replace(body_str, reg_obj_question_m, "?");

    std::regex reg_obj_apos("%60");
    body_str = std::regex_replace(body_str, reg_obj_apos, "'");

    Logs::write_log_data("              function: url_decode end, url data: " + body_str);
    return body_str;
}

bool Services::is_valid_session(const Request &request)
{ 
    Logs::write_log_data("              function: is_valid_session");

    try 
    {
        auto cookies = request.cookies();

        auto cookie = cookies.get("login_cookie");
        std::string cookie_token = cookie.value;
        Logs::write_log_data("              function: is_valid_session, cookie token: " + cookie_token);

        if (Users::check_cookie(cookie.value, "../../db/Users.db3"))
        {
            Logs::write_log_data("              function: is_valid_session, return: true");

            return true;
        }
    } 
    catch (std::exception &e) 
    {
        Logs::write_log_data("              function: is_valid_session");
        return false;
    }

    return false;
}

Pistache::Http::Cookie Services::login_cookie_generator(std::string email)
{
    Logs::write_log_data("              function: login_cookie_generator");

    std::string cookie_value = Generators::random_number_generator(5);
 
    Pistache::Http::Cookie cookie("login_cookie", cookie_value);

    Users::insert_cookie(email, cookie_value, "../../db/Users.db3");
    
    cookie.maxAge.emplace(3600);

    return cookie;
}

void Services::get_login_site(const Request &request, Response response)
{
    try 
    {
        Logs::write_log_data(" GET request, function: get_login_site");

        if(is_valid_session(request))
        {
            response.headers().add<Pistache::Http::Header::Location>("/chatsite");
            response.send(Pistache::Http::Code::See_Other);
        }
 
        const std::string uri = request.resource();

        std::string htmlContent;
        std::ifstream htmlFile("../../frontend/loginpage/index.html");
        std::getline(htmlFile, htmlContent, '\0');

        std::string cssContent;
        std::ifstream cssFile("../../frontend/loginpage/style.css");
        std::getline(cssFile, cssContent, '\0');

        htmlContent += "\n<style>" + cssContent + "</style>";

        response.headers().add<Pistache::Http::Header::ContentType>(MIME(Text, Html));
        response.send(Http::Code::Ok, htmlContent);
    } 
    catch (const std::exception &e) 
    {
        Logs::write_log_data_exception("              function: get_login_site, ", e);
    }
}

void Services::login_handler(const Request &request, Response response)
{
    try 
    {
        std::string body_data = url_decode(request.body());
        int and_simbol = body_data.find("&");
   
        std::string email_addres = body_data.substr(9, and_simbol - 9); 
        std::string password = body_data.substr(and_simbol + 10);

        Logs::write_log_data("POST request, function: login_handler", email_addres);

        if (Users::valid_user(email_addres, "../../db/Users.db3") == false)
        {
        
            std::string login_email_validation = R"(
            <div hx-swap="outerHTML">
				<button hx-post="/login"
					hx-target="closest div"
					hx-include="closest form">Sign In
			    </button>
                <div class='error-message'>Wrong email address.</div>
		    </div>
            )";

            response.send(Http::Code::Ok, login_email_validation);

        } 
        else if (!Users::valid_password(email_addres, password, "../../db/Users.db3"))
        {
            std::string login_poassword_validation = R"(
            <div hx-swap="outerHTML">
				<button hx-post="/login"
					hx-target="closest div"
					hx-include="closest form" ">Sign In
			    </button>
                <div class='error-message'>Wrong password.</div>
		    </div>
            )";

            response.send(Http::Code::Ok, login_poassword_validation);
        }
        else
        {
            response.headers().add<Pistache::Http::Header::Location>("/chatsite");
            response.cookies().add(login_cookie_generator(email_addres));
            response.headers().addRaw(Pistache::Http::Header::Raw{"HX-Redirect", ""});
            response.send(Pistache::Http::Code::See_Other);
        }
    } 
    catch (const std::exception &e) 
    {
        std::string login_validation_error = R"(
        <div hx-swap="outerHTML">
			<button hx-post="/login"
				hx-target="closest div"
				hx-include="closest form">Sign In
			</button>
            <div class='error-message'>Server error.</div>
		</div>
        )";

        response.send(Http::Code::Ok, login_validation_error);

        Logs::write_log_data_exception("              function: login_handler, ", e);
    }

}

void Services::get_chat_site(const Request &request, Response response)
{
    try {
        Logs::write_log_data(" GET request, function: get_chat_site");

        auto cookies = request.cookies();

        if(!cookies.has("login_cookie")) // && !Users::check_cookie(cookies.get("login_cookie").value, "../../db/Users.db3")
        {

            response.headers().add<Pistache::Http::Header::Location>("/");
            response.send(Pistache::Http::Code::See_Other);
        }
        if(!Users::check_cookie(cookies.get("login_cookie").value, "../../db/Users.db3")) // 
        {

            response.headers().add<Pistache::Http::Header::Location>("/");
            response.send(Pistache::Http::Code::See_Other);
        }
    
    

        std::string htmlContent;
        std::ifstream htmlFile("../../frontend/chatsite/index.html");
        std::getline(htmlFile, htmlContent, '\0');

        std::string cssContent;
        std::ifstream cssFile("../../frontend/chatsite/style.css");
        std::getline(cssFile, cssContent, '\0');

        htmlContent += "\n<style>" + cssContent + "</style>";

        response.headers().add<Pistache::Http::Header::ContentType>(MIME(Text, Html));

        response.send(Http::Code::Ok, htmlContent);
    } 
    catch (const std::exception &e) 
    {
        Logs::write_log_data_exception("              function: get_chat_site, ", e);
    }
}
