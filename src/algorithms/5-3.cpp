#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

void updateHouseNumbers(std::vector<std::string>& houses, int step) {
    std::vector<std::string> newHouses = houses;

    for (size_t i = 0; i < houses.size(); i++) {
        std::string& donorHouse = houses[i];
        std::string& receivingHouse = newHouses[(i + 1) % houses.size()];

        if (step <= donorHouse.length()) {
            char digit = donorHouse[donorHouse.length() - step];
            donorHouse.erase(donorHouse.length() - step, 1);
            receivingHouse = digit + receivingHouse;
        }
    }

    // Remove leading zeros
    for (auto& house : newHouses) {
        house.erase(0, std::min(house.find_first_not_of('0'), house.size()-1));
    }

    houses = newHouses;
}

std::vector<std::string> house_game(const std::vector<std::string>& initial_houses) {
    std::vector<std::string> currentHouses = initial_houses;
    std::vector<std::string> previousHouses;
    int step = 1;

    while (currentHouses != previousHouses) {
        previousHouses = currentHouses;
        updateHouseNumbers(currentHouses, step);
        step++;

        // Debug output
        std::cout << "Step " << step - 1 << ": ";
        for (const auto& house : currentHouses) {
            std::cout << house << " ";
        }
        std::cout << std::endl;

        if (step > 1000) {  // Safety check to prevent infinite loop
            std::cout << "Reached maximum steps. Exiting." << std::endl;
            break;
        }
    }

    return currentHouses;
}

// Helper function to convert vector of ints to vector of strings
std::vector<std::string> intToStringVector(const std::vector<int>& intVector) {
    std::vector<std::string> stringVector;
    for (int num : intVector) {
        stringVector.push_back(std::to_string(num));
    }
    return stringVector;
}

// Wrapper function to maintain the original interface
std::vector<int> house_game_wrapper(const std::vector<int>& houses) {
    auto stringHouses = intToStringVector(houses);
    auto result = house_game(stringHouses);
    
    std::vector<int> intResult;
    for (const auto& house : result) {
        try {
            intResult.push_back(std::stoi(house));
        } catch (const std::out_of_range&) {
            std::cout << "Warning: Number " << house << " is too large for int. Truncating." << std::endl;
            intResult.push_back(std::numeric_limits<int>::max());
        } catch (const std::invalid_argument&) {
            std::cout << "Error: Invalid number " << house << ". Setting to 0." << std::endl;
            intResult.push_back(0);
        }
    }
    return intResult;
}
