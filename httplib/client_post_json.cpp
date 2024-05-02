#include <httplib.h>
#include <iostream>
#include <map>
#include "json.hpp"

std::map<httplib::Error, std::string> errors = {
  {httplib::Error::Success, "Success"},
  {httplib::Error::Unknown, "Unknown"},
  {httplib::Error::Connection, "Connection"},
  {httplib::Error::BindIPAddress, "BindIPAddress"},
  {httplib::Error::Read, "Read"},
  {httplib::Error::Write, "Write"},
  {httplib::Error::ExceedRedirectCount, "ExceedRedirectCount"},
  {httplib::Error::Canceled, "Canceled"},
  {httplib::Error::SSLConnection, "SSLConnection"},
  {httplib::Error::SSLLoadingCerts, "SSLLoadingCerts"},
  {httplib::Error::SSLServerVerification, "SSLServerVerification"},
  {httplib::Error::UnsupportedMultipartBoundaryChars, "UnsupportedMultipartBoundaryChars"}
};


int main(void)
{
  httplib::Client cli("localhost", 10000);

  nlohmann::json j;

  j["id"] = 1;
  j["kelvin"] = 200;
  
  if (auto res = cli.Post("/celcius", j.dump(), "application/json")) {

    nlohmann::json out = nlohmann::json::parse(res->body);

    std::cout << "Temperature in celcius: " << out.at("value") << std::endl;
  } else {
    auto err = res.error();

    std::cout << "Error: " << errors.at(err) << std::endl;
  }
}
