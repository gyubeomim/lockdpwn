#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <sstream>

class CSVReader {
  std::string filename_;
  std::string delim_;

 public:
  CSVReader(std::string filename, std::string delim=",")
      : filename_(filename), delim_(delim)
  {}

  std::vector<std::vector<std::string>> GetData() {
    std::ifstream file(filename_);
    std::vector<std::vector<std::string>> data;

    std::string line="";

    while(std::getline(file, line)) {
      std::vector<std::string> vec;
      vec = Split(line);
      data.push_back(vec);
    }
    file.close();

    return data;
  }

  std::vector<std::string> Split(const std::string& str) {
    std::regex rgx(delim_);
    std::sregex_token_iterator first{begin(str), end(str), rgx, -1}, last;
    return{first, last};
  }

};


int main(int argc, char **argv) {
  CSVReader reader("/home/atlas1/Downloads/eval-mpb.txt");

  std::vector<std::vector<std::string>> data = reader.GetData();

  for(std::vector<std::string> vec : data) {
    for(std::string data : vec) {
      std::cout << data << " | ";
    }
    std::cout << std::endl;
  }
  return 0;
}
