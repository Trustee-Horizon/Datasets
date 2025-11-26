/* Copyright (C) 2024 Università Cattolica del Sacro Cuore (https://www.unicatt.it/)
 * Copyright (C) 2024 Spazio IT (https://spazioit.com)
 * This program is Licensed under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. See accompanying LICENSE file.
 */
#include <iostream>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <algorithm>

#include "faker-cxx/Date.h"
#include "faker-cxx/Person.h"

using namespace std;


enum {
BUFF = 100,
MAX_LINES = 1000
};
// Initial Hasshing function
auto mm_hash(char const *input) -> size_t;

auto main(int argc, char *argv[]) -> int {
    int lines = 0;
    int i = 0;

    // Command line processing
    if (argc > 3) {
        cerr << argv[0] << ": wrong command line!" << endl;
        cerr << "syntax: " << argv[0] << " <number_of_lines>" << endl;
        return -1;
    } else  if (argc == 1) {
        lines = MAX_LINES;
    } else if (argc == 2) {
        if (sscanf(argv[1], "%d", &lines) != 1) {
            cerr << argv[0] << ": wrong number of lines!" << endl;
            cerr << "syntax: " << argv[0] << " <number_of_lines>" << endl;
            return -2;
        }
    } else {
        cerr << argv[0] << ": wrong glasgow type!" << endl;
        cerr << "syntax: " << argv[0] << " <number_of_lines>" << endl;
        return -4;
    }
    
    // Seed generation
    srand((unsigned int)time(nullptr));

    // Array to store the people names
    std::string names[lines];

    for (i = 0; i < lines; i++) {
        // Fake Personal data generation
        const auto person = new faker::Person(); 
        const auto personFullName = person->fullName(faker::Country::England);
        delete person;
        names[i] = personFullName;
    }

    // Print Health Dataset
    cout << "---- HEALTH DATASET -----" << endl;
    for (i = 0; i < lines; i++) {
        const auto startDate = faker::Date::recentDate(15);
        const auto endDate = faker::Date::soonDate(15);
        cout << setw(5) << i+1 << ", " << setw(30) <<  names[i] <<", " << setw(20) << mm_hash(names[i].c_str()) << ", "
             << startDate << ", " << endDate << ", "
             << startDate.substr(8,2) << ", " << startDate.substr(5,2) << ", " << startDate.substr(2,2) << ","
             << endDate.substr(8,2) << ", " << endDate.substr(5,2) << ", " << endDate.substr(2,2) << endl;

    }

    // Shuffle the array
    random_shuffle(&names[0], &names[lines - 1]);    
    
    // Print Education Dataset
    cout << endl << "---- EDUCATION DATASET -----" << endl;
    for (i = 0; i < lines; i++) {
        int mm_class = 0;
        char section = 0;
        char ch_section[1];
        mm_class = rand() % 5;
        mm_class++;
        section = rand() % 3;
        ch_section[0] = '1' + section;
        cout << setw(5) << i+1 << ", " << setw(30) <<  names[i] <<", " << setw(20) << mm_hash(names[i].c_str()) << ", "
             << mm_class << ", " << ch_section[0] << endl;
    }
    
    return 0;
}

auto mm_hash(char const *input) -> size_t {
	const int ret_size = 63;
	size_t ret = 0x5555550555555;
	const int per_char = 7;

	while (*input) {
		ret ^= *input++;
		ret = ((ret << per_char) | (ret >> (ret_size - per_char)));
	}
	return ret;
}

