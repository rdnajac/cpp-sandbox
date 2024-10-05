#include <iostream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Modify this function to use a C++ standard method for joining strings.
std::string join(const std::vector<std::string>& vec, const std::string& delim) {
    std::ostringstream joined;
    // joined << vec[0] << delim << vec[1];
    for (int i = 0; i < vec.size(); i++) {
        joined << vec[i];
        if (i != vec.size() - 1)
            joined << delim;
    }
    return joined.str();
}



#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::string employee_data = "Alice,Developer,30|Bob,Manager,45|Charlie,Designer,25";
    std::vector<std::string> employee_list;
    std::istringstream data_stream(employee_data);
    std::string record;

    // Tokenizing the employee data by '|' to separate each employee's info
    while (std::getline(data_stream, record, '|')) {
        employee_list.push_back(record);
    }

    // Iterating over the list of employees
    // the auto& keyword is used to get a reference to the actual element in the vector
    // use it as if it were a dereferenced pointer to the element
    for (auto& employee : employee_list) {
        std::istringstream record_stream(employee);
        std::string name, role;
        int age;
        char delimiter = ',';
        
        // Tokenizing each employee's info by ',' to get name, role, and age
        std::getline(record_stream, name, delimiter);
        std::getline(record_stream, role, delimiter);
        record_stream >> age;
        std::string eligibility = (age < 40) ? " - Eligible for junior position" : "";
        std::cout << "Name: " << name << " - Role: " << role << " - Age: " << age << eligibility << std::endl;
    }

    return 0;
}/ 
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void processAstronautData(const std::string& data) {
    std::istringstream sstream(data);
    std::string detail;
    
    while (std::getline(sstream, detail, ';')) {
        // skip whitespace, split names at -
        // "    Neil-Mars; Buzz-Jupiter; Sally-Venus    ";
        std::istringstream detailStream(detail);
        std::string name, planet;
        while (std::getline(detailStream, name, '-')) {
            std::getline(detailStream, planet, '-');
        }
        // remove leading and trailing whitespaces
        name = name.substr(name.find_first_not_of(' '), name.find_last_not_of(' ') + 1);
        planet = planet.substr(planet.find_first_not_of(' '), planet.find_last_not_of(' ') + 1);
        std::cout << "Astronaut " << name << " is exploring " << planet << "." << std::endl;
    }
}

int main() {
    std::string astronautData = "    Neil-Mars; Buzz-Jupiter; Sally-Venus    ";
    processAstronautData(astronautData);
    
    return 0;
}
#include <iostream>
#include <vector>
#include <sstream>

#include <iostream>
#include <vector>
#include <sstream>

int main() {
    // Space exploration crew members' data, containing their names, missions, and roles
    std::string crew_data = "Neil,Armstrong,Apollo 11,C;Buzz,Aldrin,Apollo 11,P;Michael,Collins,Apollo 11,CM";

    // TODO: Split the crew_data string into a list of individual crew member information using the appropriate delimiter
    std::vector<std::string> crew_list;
    std::istringstream crew_stream(crew_data);
    std::string crew_member;
    while (std::getline(crew_stream, crew_member, ';')) {
        crew_list.push_back(crew_member);
    }
    
    // TODO: Iterate over the list of crew member data
    std::vector<std::string> crew_member_data;
    for (auto& member : crew_list) {
        // crew_member_data = split(member, ',');
        // std::cout << join(crew_member_data, " ") << std::endl;
        // do it withot split or join
        std::istringstream member_stream(member);
        std::string detail;
        while (std::getline(member_stream, detail, ',')) {
            crew_member_data.push_back(detail);
        }
        std::cout << crew_member_data[0] << " " << crew_member_data[1] << " " << crew_member_data[2] << " " << crew_member_data[3] << std::endl;
    }
    
        // TODO: For each member, split their data string using commas as delimiters
        
        // TODO: Print the crew member's details in a formatted string
    
    // Expected output:
    // Neil Armstrong Apollo 11 C
    // Buzz Aldrin Apollo 11 P
    // Michael Collins Apollo 11 CM

    return 0;
}
