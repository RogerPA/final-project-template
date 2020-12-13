// Copyright 2020 Roger Peralta Aranibar Advanced Data Estructures
#include <iomanip>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

template <typename>
class Timer;

template <typename R, typename... T>
class Timer<R(T...)> {
 public:
  typedef R (*function_type)(T...);
  function_type function;

  explicit Timer(function_type function, std::string process_name = "")
      : function_(function), process_name_(process_name) {}

  R operator()(T... args) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    R result = function_(std::forward<T>(args)...);

    end = std::chrono::high_resolution_clock::now();
    int64_t duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count();

    std::cout << std::setw(10) << process_name_ << std::setw(30)
              << "Duration: " + std::to_string(duration) + " ns\n";
    return result;
  }

 private:
  function_type function_;
  std::string process_name_;
};

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

int build_data_structure() {
  for (float i = 0; i < 10; ++i) {
    G_DS.add(i);
  }
  return 0;
}

std::vector<std::vector<float>> query_knn(std::vector<float> query, int k) {
  return G_DS.get_data(query, k);
}

int main() {
  Timer<int()> timed_built(build_data_structure, "Index");
  timed_built();

  Timer<std::vector<std::vector<float>>(std::vector<float>, int)> timed_query(
      query_knn, "Query KNN");
  std::vector<float> query = {1, 2, 3};
  int k = 2;
  std::vector<std::vector<float>> result = timed_query(query, k);
}
