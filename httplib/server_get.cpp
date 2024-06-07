#include "httplib.h"

using httplib::Server;
using httplib::Request;
using httplib::Response;

int main(void)
{

  Server svr;

  svr.Get("/hello", [](const Request& req, Response& res) {
    res.set_content("Hello World!", "text/plain");
    res.status = 200;
  });

  svr.Get("/hello-html", [](const Request& req, Response& res) {
    res.set_content("<p><b>Hello</b>, World!</p>", "text/html");
  });

  svr.Get("/body-header-param", [](const Request& req, Response& res) {
    if (req.has_header("User-Agent")) {
      auto val = req.get_header_value("User-Agent");

      std::cout << "User-Agent:" << val << std::endl;
    }

    std::string name = "Unknown";
    int age = -1;

    if (req.has_param("name")) {
      name = req.get_param_value("name");

      std::cout << "Name: " << name << std::endl;
    }

    if (req.has_param("age")) {
      age = std::stoi(req.get_param_value("age"));

      std::cout << "Age: " << age << std::endl;
    }

    const char* format = R"(<ul>
    <li>%s</li>
    <li>%d</li>
</ul>)";

    char buffer[256];

    sprintf(buffer, format, name.c_str(), age);

    res.set_content(buffer, "text/html");

    res.status = 200;
//    res.set_content(req.body, "text/plain");
  });

  svr.Get("/stop", [&](const Request& req, Response& res) {
    svr.stop();
  });

  svr.listen("0.0.0.0", 10000);

  return 0;
}
