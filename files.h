#include <experimental/filesystem>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> get_all_file_names(std::string from)
{   
    std::vector<std::string> to;
    for(auto& i: std::experimental::filesystem::recursive_directory_iterator(from))
      if (!std::experimental::filesystem::is_directory(i.path()))
          to.emplace_back(i.path().filename());
    return to;
} 

std::string read_from_file(std::string path){
    std::ifstream ifs(path);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    return std::string(buffer.str());
}

void save_to_file(std::string path, std::string text){
    std::ofstream ofs(path);
    ofs << text;
}

