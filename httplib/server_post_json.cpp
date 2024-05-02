#include "httplib.h"
#include <string>
#include <iterator>
#include "json.hpp"

int main(void)
{
  using namespace httplib;

  Server svr;

  svr.Post("/celcius", [](const Request& req, Response& res) {

    nlohmann::json j = nlohmann::json::parse(req.body);

    if (j.find("kelvin") == j.end()) {
      res.status = 400;
      return;
    }

    nlohmann::json out;

    out["value"] = int(j.at("kelvin")) - 273;
    out["id"] = j.at("id");

    res.set_content(out.dump(), "application/json");

  });


  svr.Get("/stop", [&](const Request& req, Response& res) {
    svr.stop();
  });

  svr.listen("localhost", 10000);

  return 0;
}
