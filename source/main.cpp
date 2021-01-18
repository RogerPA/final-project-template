// Copyright 2020 Roger Peralta Aranibar Advanced Data Estructures
#pragma warning ( disable : 4244)

#include <iomanip>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <string>
#include <chrono>
#include <typeinfo>
#include <functional>

namespace timer_aed {
#define MINUTES      std::chrono::minutes
#define SECONDS      std::chrono::seconds
#define MILLISECONDS std::chrono::milliseconds
#define MICROSECONDS std::chrono::microseconds
#define NANOSECONDS  std::chrono::nanoseconds

  std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
  std::string uom_abreviation;
  int64_t duration;

#define get_var_name(x) #x
#define TEST_FUNCTION(current_process) std::function<void()> current_process = []

#define RUN_TIMER(test_function_, unit_of_measurement)\
        if(typeid(unit_of_measurement) == typeid(std::chrono::minutes)) uom_abreviation = "min.";\
        else if(typeid(unit_of_measurement) == typeid(std::chrono::seconds)) uom_abreviation = "s.";\
        else if(typeid(unit_of_measurement) == typeid(std::chrono::milliseconds)) uom_abreviation = "ms.";\
        else if(typeid(unit_of_measurement) == typeid(std::chrono::microseconds)) uom_abreviation = "mcs.";\
        else if(typeid(unit_of_measurement) == typeid(std::chrono::nanoseconds)) uom_abreviation = "ns.";\
        start = std::chrono::high_resolution_clock::now();\
        test_function_();\
        end = std::chrono::high_resolution_clock::now();\
        duration = std::chrono::duration_cast<unit_of_measurement>(end - start).count();\
        std::cout << std::setw(10) << get_var_name(test_function_) << std::setw(30)\
        << "Duration: " + std::to_string(duration) + " " + uom_abreviation + "\n"
};

using namespace timer_aed;

class MyDataStructure {
 public:
  MyDataStructure() {}

  void add(float entry) { data_.push_back(entry); }

  std::vector<std::vector<float>> get_data(std::vector<float> query, int k) {
    query.push_back(k);
    std::vector<std::vector<float>> result;
    result.push_back(data_);
    result.push_back(query);
    return result;
  }

 private:
  std::vector<float> data_;
};

MyDataStructure G_DS;

void build_data_structure() {
  for (float i = 0; i < 10; ++i) {
    G_DS.add(i);
  }
}

void query_knn() {
  std::vector<float> query = { 1, 2, 3 };
  int k = 2;
  for (auto v : G_DS.get_data(query, k)) {
    for (auto e : v)
      std::cout << e << ' ';
    std::cout << '\n';
  }
}

std::vector<float> query;

int main() {
  TEST_FUNCTION(Indexation_test) {
    for (float i = 0; i < 10; ++i) {
      G_DS.add(i);
    }
  };

  query = { 1, 2, 3 };

  TEST_FUNCTION(Query_KNN_test) {
    G_DS.get_data(query, 2);
  };

  RUN_TIMER(Indexation_test, NANOSECONDS);
  RUN_TIMER(Query_KNN_test, MICROSECONDS);
  return 0;
}
