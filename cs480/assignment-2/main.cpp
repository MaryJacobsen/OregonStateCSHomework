#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

extern int yylex();
extern std::vector<std::string> identifiers;
extern std::vector<std::string> prog;
extern bool _error;

int main(int argc, char const *argv[]) {
  //if no problems with yylex, print program
  if(!yylex()) {
    std::cout << "#include <iostream>\nint main() {" << std::endl;

    std::sort(identifiers.begin(), identifiers.end());
    std::string program_str = "";

    //variables
    for(auto i : identifiers) {
      std::cout << "double " << i << ";" << std::endl;
    }

    //assignments
    for(auto i : prog) {
      if(i != ";") {
        program_str += i;
        program_str += " ";
      }
    }
    program_str = program_str.substr(0, program_str.size()-1);
    std::cout << "\n/* Begin program */\n\n" << program_str << "\n\n/* End program */\n" << std::endl;

    //cout variables and their values
    for(auto i : identifiers) {
      std::cout <<"std::cout << \""<< i << ": \" << " << i << " << std::endl;" << std::endl;
    }

    std::cout << "}" << std::endl;

    return 0;
  }
  //else return 1
  else {
    return 1;
  }
}
