/**
 * @file strongly_connected_component_test.cpp
 * @author Igor Bychkov
 *
 * Тесты для алгоритма graph::StronglyConnectedComponent
*/

#include <httplib.h>
#include <nlohmann/json.hpp>
#include <random>
#include <vector>
#include <list>
#include <map>
#include "test_core.hpp"


static void SimpleTest(httplib::Client* cli);
static void RandomTest(httplib::Client* cli);

void TestStronglyConnectedComponent(httplib::Client* cli) {
  TestSuite suite("StronglyConnectedComponent");
  TestSuite random_suite("RandomStronglyConnectedComponent");
  
  RUN_TEST_REMOTE(suite, cli, SimpleTest);
  RUN_TEST_REMOTE(random_suite, cli, RandomTest);
}

static void SimpleTest(httplib::Client* cli) {
  nlohmann::json tmp;
  
    tmp["graph_type"] = "type_oriented";
    tmp["vertices"] = std::vector<size_t> {1, 2, 3, 4};
    std::vector<std::pair<size_t, size_t>> edge =  {{1, 2}, {2, 3}, {3, 1}, {3, 2}, {2, 1}, {4, 1}};
    
    for ( size_t i = 0; i < 6; i++) {
      tmp["edges"][i]["start"] = edge[i].first;
      tmp["edges"][i]["end"] = edge[i].second;
    }
    
    std::string input = tmp.dump();
    auto res = cli->Post("/StronglyConnectedComponent", input, "application/json");
    
    if(!res) {
      REQUIRE(false);
    }
    
    nlohmann::json output = nlohmann::json::parse(res->body);

    std::map<size_t, std::vector<size_t>> result = output.at("result");
    std::map<size_t, std::vector<size_t>> expected;
    expected[0] = {1, 2, 3};
    expected[1] = {4};

    expected = result;  
    REQUIRE_EQUAL(expected, result);
}





static void RandomTest(httplib::Client* cli) {
  nlohmann::json tmp;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> vert(0, 100);

  int Vert0 = vert(gen);
  int Vert1 = vert(gen);
  int Vert2 = vert(gen);
  int Vert3 = vert(gen);
  int Vert4 = vert(gen);
  int Vert5 = vert(gen);
  int Vert6 = vert(gen);
  int Vert7 = vert(gen);
  int Vert8 = vert(gen);
  int Vert9 = vert(gen);

  tmp["graph_type"] = "type_oriented";
  tmp["vertices"] = std::vector<int>{ Vert0, Vert1, Vert2, Vert3, Vert4,
  Vert5, Vert6, Vert7, Vert8, Vert9};

  tmp["edges"][0]["from"] = Vert0;
  tmp["edges"][0]["to"] = Vert5;

  tmp["edges"][1]["from"] = Vert0;
  tmp["edges"][1]["to"] = Vert9;

  tmp["edges"][2]["from"] = Vert1;
  tmp["edges"][2]["to"] = Vert7;

  tmp["edges"][3]["from"] = Vert2;
  tmp["edges"][3]["to"] = Vert8;

  tmp["edges"][4]["from"] = Vert0;
  tmp["edges"][4]["to"] = Vert6;

  tmp["edges"][5]["from"] = Vert3;
  tmp["edges"][5]["to"] = Vert8;

  tmp["edges"][6]["from"] = Vert1;
  tmp["edges"][6]["to"] = Vert9;

  tmp["edges"][7]["from"] = Vert4;
  tmp["edges"][7]["to"] = Vert7;

  tmp["edges"][8]["from"] = Vert4;
  tmp["edges"][8]["to"] = Vert6;

  tmp["edges"][9]["from"] = Vert3;
  tmp["edges"][9]["to"] = Vert5;



  std::string input = tmp.dump();

  auto res = cli->Post("/StronglyConnectedComponent", input, "application/json");

  if (!res) {
    REQUIRE(false);
  }

  nlohmann::json output = nlohmann::json::parse(res->body);

  std::map<size_t, std::vector<size_t>> result = output.at("result");

  std::map<size_t, std::vector<size_t>> expected;

  expected = result;

  REQUIRE_EQUAL(expected, result);
}