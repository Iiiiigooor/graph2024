#include "httplib.h"
#include <string>
#include <iterator>

int main(void)
{
  using namespace httplib;

  Server svr;

  svr.Post("/hello", [](const Request& req, Response& res) {
    if (req.has_param("key")) {
      auto val = req.get_param_value("key");

      std::cout << "Value: " << val << std::endl;
    }

    std::cout << "Body: " << req.body << std::endl;
    res.status = 200;
    res.set_content(req.body, "text/plain");

  });

  svr.Get("/form", [](const Request& req, Response& res) {
    std::ifstream in("page.html");

    std::string data;

    std::copy(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>(), std::back_inserter(data));

    std::cout << data;

    res.set_content(data, "text/html");
  });

  svr.Post("/send", [](const Request& req, Response& res) {
    if (req.has_param("fname") && req.has_param("lname")) {
      auto fname = req.get_param_value("fname");
      auto lname = req.get_param_value("lname");

      const char* format = R"(
<!DOCTYPE html>
<html>
<body>

<p>User details:</p>
<ul>
  <li>First name: %s</li>
  <li>Last name: %s</li>
</ul>

</body>
</html>
      )";

      char buffer[1024];

      sprintf(buffer, format, fname.c_str(), lname.c_str());

      res.set_content(buffer, "text/html");
    } else {
      res.status = 400;
    }
  });


  svr.Get("/stop", [&](const Request& req, Response& res) {
    svr.stop();
  });

  svr.listen("localhost", 10000);

  return 0;
}
