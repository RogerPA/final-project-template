// Copyright 2020 Roger Peralta Aranibar Advanced Data Estructures

#ifndef TIMER_ADE
#define TIMER_ADE
  #pragma warning(disable:4244)
  #if !__has_include("<chrono>")
    #include <chrono>
  #endif
  #if !__has_include("<functional>")
    #include <functional>
  #endif
  #if !__has_include("<iomanip>")
    #include <iomanip>
  #endif
  #if !__has_include("<iostream>")
    #include <iostream>
  #endif
  #if !__has_include("<memory>")
    #include <memory>
  #endif
  #if !__has_include("<utility>")
    #include <utility>
  #endif
  #if !__has_include("<string>")
    #include <string>
  #endif
  #if !__has_include("<typeinfo>")
    #include <typeinfo>
  #endif
  #if !__has_include("<vector>")
    #include <vector>
  #endif

  #define NC "\e[0m"
  #define RED "\e[0;31m"
  #define GRN "\e[0;32m"
  #define CYN "\e[0;36m"
  #define REDB "\e[41m"

  typedef std::chrono::minutes      MINUTES;
  typedef std::chrono::seconds      SECONDS;
  typedef std::chrono::milliseconds MILLISECONDS;
  typedef std::chrono::microseconds MICROSECONDS;
  typedef std::chrono::nanoseconds  NANOSECONDS;

  #define get_var_name(x) #x

  std::vector<std::pair<std::string, std::function<void()>>> test_queue;
  int64_t _duration;
  size_t _checkpoint(0);
  std::string uom_abreviation;

  #define TEST_FUNCTION(process_name)\
           test_queue.resize( test_queue.size() + size_t(1));\
           test_queue[ test_queue.size() - 1].first = get_var_name(process_name);\
           test_queue[ test_queue.size() - 1].second = [](void)

  #define __SET_TIME_UNIT_ADE__(time_unit)if(typeid( time_unit) == typeid(std::chrono::minutes)) uom_abreviation = "min.";\
                                          else if(typeid( time_unit) == typeid(std::chrono::seconds)) uom_abreviation = "s.";\
                                          else if(typeid( time_unit) == typeid(std::chrono::milliseconds)) uom_abreviation = "ms.";\
                                          else if(typeid( time_unit) == typeid(std::chrono::microseconds)) uom_abreviation = "mcs.";\
                                          else uom_abreviation = "ns."

  struct steady_clock : public std::chrono::steady_clock{
    static std::chrono::high_resolution_clock::time_point now() { return std::chrono::high_resolution_clock::now(); }
  };
  typedef steady_clock high_resolution_clock;
  #define RUN_TESTS(time_unit) __SET_TIME_UNIT_ADE__(time_unit);\
          for (; _checkpoint < test_queue.size(); ++_checkpoint) {\
            std::chrono::high_resolution_clock::time_point start = high_resolution_clock::now();\
            test_queue[_checkpoint].second();\
            std::chrono::high_resolution_clock::time_point end = high_resolution_clock::now();\
            _duration = std::chrono::duration_cast<time_unit>(end - start).count();\
            std::cout << __COUNTER__ + 1 << " Process Name: " << std::setw(10) <<  test_queue[_checkpoint].first << std::setw(30)\
            << "Duration: " + std::to_string( _duration) + " " + uom_abreviation + "\n";\
          } 
#endif // !TIMER_ADE

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

  RUN_TESTS(NANOSECONDS);

  TEST_FUNCTION(Query_KNN_test_2) {
    G_DS.get_data(query, 5);
  };

  RUN_TESTS(NANOSECONDS);
  return 0;
}