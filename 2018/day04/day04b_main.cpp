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
    return os << "year: " << ymd.year << " month: " << ymd.month << " day: " << ymd.day;
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
    return os << "hour: " << tod.hour << " minute: " << tod.minute;
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
    return os << "ymd: " << row.ymd << " tod: " << row.tod << " log_entry: " << row.log_entry;
  }
};

std::istream &operator>>(std::istream &fin, Row &row) {
  char bracket_ignore;
  fin >> bracket_ignore >> row.ymd >> row.tod >> bracket_ignore;
  return std::getline(fin, row.log_entry);
}

typedef std::map<int, std::array<int, 60>> Map;

std::string const KGuard = "Guard";
std::string const KFall = "falls";
std::string const KWakeup = "wakes";

void best_sleep_freq(std::vector<Row> const &sorted_log) {
  std::string key;
  int last_sleep_start = 0;
  int current_guard_id = -1;
  Map sleep_freq;
  for (auto const &row : sorted_log) {
    std::istringstream iss(row.log_entry);
    iss >> key;
    if (key == KGuard) {
      char hash;
      iss >> hash >> current_guard_id;
    } else if (key == KFall) {
      last_sleep_start = row.tod.minute;
    } else if (key == KWakeup) {
      for (int i = last_sleep_start; i < row.tod.minute; ++i)
        sleep_freq[current_guard_id][i]++;
    }
  }
  int best_freq = -1;
  int best_minute = -1;
  int best_guard = -1;
  for (auto const &guard : sleep_freq) {
    auto const best_sleep_minute_for_guard = std::max_element(guard.second.begin(), guard.second.end());
    int const freq = *best_sleep_minute_for_guard;
    if (freq > best_freq) {
      best_freq = freq;
      best_minute = static_cast<int>(std::distance(guard.second.begin(), best_sleep_minute_for_guard));
      best_guard = guard.first;
    }
  }
  std::cout << "Best guard id " << best_guard << " sleeps often at minute " << best_minute << " (count) " << best_freq
            << "\nAnswer " << best_guard * best_minute << '\n';
}

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
  best_sleep_freq(log);
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
