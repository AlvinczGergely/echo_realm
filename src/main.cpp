#include "services.h"
#include "logs.h"
#include <thread>
#include <exception>
using namespace Pistache;


int main()
{
  try
  {
    Logs::start_write_log_data("              function: main");

    uint16_t port_num = 9090;
    Services::is_port_used(port_num);
    Pistache::Http::Endpoint end_point(Pistache::Address("localhost", port_num));
    end_point.init(Pistache::Http::Endpoint::options().threads(std::thread::hardware_concurrency()));
          
    Pistache::Rest::Router chat_router;
    Services::config_routes(chat_router);
    end_point.setHandler(chat_router.handler());

    end_point.serve();
  }
  catch (const std::exception &e)
  {
    std::cout << "exception caught in main: " << e.what() << std::endl; 
    return 1;
  }
  catch (...)
  {
    std::cout << "exception caught in main ..." << std::endl;
    return 1;
  }

  return 0;
}
