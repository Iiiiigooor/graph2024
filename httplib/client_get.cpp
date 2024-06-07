#include <httplib.h>
#include <iostream>
#include <map>

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

  if (auto res = cli.Get("/hello-html")) {
    std::cout << "Status: " << res->status << std::endl;
    if (res->status == 200) {
      std::cout << res->body << std::endl;
    }
  } else {
    auto err = res.error();

    std::cout << "Error: " << errors.at(err) << std::endl;
  }
}
