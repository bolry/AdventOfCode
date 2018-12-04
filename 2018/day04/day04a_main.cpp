#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <new>
#include <numeric>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

namespace {

struct YMD {
  int year;
  int month;
  int day;
  friend std::ostream &operator<<(std::ostream &os, const YMD &ymd) {
    os << "year: " << ymd.year << " month: " << ymd.month << " day: " << ymd.day;
    return os;
  }
};
std::istream &operator>>(std::istream &fin, YMD &ymd) {
  char dash_ignore;
  return fin >> ymd.year >> dash_ignore >> ymd.month >> dash_ignore >> ymd.day;
}
struct TOD {
  int hour;
  int minute;
  friend std::ostream &operator<<(std::ostream &os, const TOD &tod) {
    os << "hour: " << tod.hour << " minute: " << tod.minute;
    return os;
  }
};
std::istream &operator>>(std::istream &fin, TOD &tod) {
  char colon_ignore;
  return fin >> tod.hour >> colon_ignore >> tod.minute;
}
struct Row {
  YMD ymd;
  TOD tod;
  std::string log_entry;
  friend std::ostream &operator<<(std::ostream &os, const Row &row) {
    os << "ymd: " << row.ymd << " tod: " << row.tod << " log_entry: " << row.log_entry;
    return os;
  }
};
std::istream &operator>>(std::istream &fin, Row &row) {
  char bracket_ignore;
  fin >> bracket_ignore >> row.ymd >> row.tod >> bracket_ignore;
  return std::getline(fin, row.log_entry);
}

typedef std::map<int, int> Map;

std::string const KGuard = "Guard";
std::string const KFall = "falls";
std::string const KWakeup = "wakes";

int guard_with_most_sleep_time(std::vector<Row> const &sorted_log) {
  Map sleep_log;
  int current_guard_id = -1;
  std::string key;
  int last_sleep_start;
  for (auto const &row : sorted_log) {
    std::istringstream iss(row.log_entry);
    iss >> key;
    if (key == KGuard) {
      char hash;
      iss >> hash >> current_guard_id;
    } else if (key == KFall) {
      last_sleep_start = row.tod.minute;
    } else if (key == KWakeup) {
      int const sleep_time = row.tod.minute - last_sleep_start;
      sleep_log[current_guard_id] += sleep_time;
    } else {
      throw std::runtime_error("Found unknown keyword: " + key);
    }
  }
  for (auto const &e : sleep_log) {
    std::cout << "id: " << e.first << " sleep: " << e.second << '\n';
  }
  auto sleepiest_guard_id =
      std::max_element(sleep_log.begin(), sleep_log.end(), [](Map::value_type const &a, Map::value_type const &b) {
        return a.second < b.second;
      });
  return sleepiest_guard_id->first;
}

}

int best_sleep_miniute(int const id, std::vector<Row> const &sorted_log) {
  std::string key;
  int last_sleep_start = 0;
  int current_guard_id = -1;
  std::array<int, 60> sleep_minutes;
  for (auto const &row : sorted_log) {
    std::istringstream iss(row.log_entry);
    iss >> key;
    if (key == KGuard) {
      char hash;
      iss >> hash >> current_guard_id;
    } else if (current_guard_id == id && key == KFall) {
      last_sleep_start = row.tod.minute;
    } else if (current_guard_id == id && key == KWakeup) {
      for (int i = last_sleep_start; i < row.tod.minute; ++i)
        sleep_minutes[i]++;
    }
  }
  return std::distance(sleep_minutes.begin(), std::max_element(sleep_minutes.begin(), sleep_minutes.end()));
}
int main(int argc, char *argv[])
try {
  std::cout.exceptions(std::cout.badbit | std::cout.eofbit | std::cout.failbit);
  if (argc < 2) throw std::runtime_error("Need input data filename\n");
  std::ifstream log_file(argv[1]);
  if (!log_file) throw std::runtime_error(std::string("Unable to open input file: ") + argv[1]);
  std::istream_iterator<Row> row_reader(log_file);
  std::istream_iterator<Row> row_reader_EOF;
  std::vector<Row> log;
  std::copy(row_reader, row_reader_EOF, std::back_inserter(log));
  std::sort(log.begin(), log.end(), [](Row const &a, Row const &b) {
    return std::tie(a.ymd.year, a.ymd.month, a.ymd.day, a.tod.hour, a.tod.minute)
        < std::tie(b.ymd.year, b.ymd.month, b.ymd.day, b.tod.hour, b.tod.minute);
  });
  std::cout << log.front() << '\n';
  std::cout << log.back() << '\n';
  int const sleepy_guard_id = guard_with_most_sleep_time(log);
  std::cout << "Sleepy Guard id: " << sleepy_guard_id << '\n';
  int const sleepy_minute = best_sleep_miniute(sleepy_guard_id, log);
  std::cout << "Best time to sleep: " << sleepy_minute << '\n';

  std::cout << "Result day 4 A is: " << sleepy_guard_id * sleepy_minute << '\n' << std::flush;
  return EXIT_SUCCESS;
}
catch (std::bad_alloc const &) {
  std::fputs("Sorry, out-of-memory\n", stderr);
  std::fflush(stderr);
  return EXIT_FAILURE;
}
catch (std::exception const &x) {
  std::cerr << x.what() << '\n' << std::flush;
  return EXIT_FAILURE;
}
#if 0
catch (...) {
    std::cerr << "Unexpected unhandled error\n" << std::flush;
    return EXIT_FAILURE;
}
#endif  // 0
