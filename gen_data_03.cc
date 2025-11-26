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

   // Array to store persons
    class MMPerson {
        public:
            string name;
            string sex;
            int age;
    };
    MMPerson * persons[lines];

    for (i = 0; i < lines; i++) {
        // Fake Personal data generation
        const auto person = new faker::Person();
        persons[i] = new MMPerson();
        persons[i]->name =  person->fullName(faker::Country::England);
        persons[i]->sex =  person->sex();
        delete person;
    }

    // Print Health Dataset
    cout << "---- HEALTH DATASET -----" << endl;
    for (i = 0; i < lines; i++) {
        const auto personFullName = persons[i]->name; 
        const auto personSex = persons[i]->sex;
        const auto hash_value = mm_hash(personFullName.c_str());
        size_t age = hash_value % 5;
        age += 15;
        std::string strSymptom;
        int symptom = rand() % 5;
        int score;
        switch (symptom) {
            case 0:
                    strSymptom = "None";
                    score = 0;
                    break;
            case 1:
                    strSymptom = "ADHD";
                    score = rand() % 5;
                    break;
            case 2:
                    strSymptom = "Anxiety";
                    do {
                        score = rand() % 56;
                    } while (score < 15);
                    break;
            case 3:
                    strSymptom = "Bipolar Disorder";
                    do {
                        score = rand() % 30;
                    } while (score < 10);
                    break;
            case 4:
                    strSymptom = "Depression";
                    do {
                        score = rand() % 15;
                    } while (score < 5);
                    break;
        }
        cout << setw(5) << i+1 << ", " << setw(30) <<  personFullName <<", " << setw(20) << hash_value << ", "
             <<setw(2) << age << ", " << setw(6) << personSex << ", " << setw(16) << strSymptom << ", " 
             << setw(2) << score << "." << endl;
    }

    // Shuffle the array
    random_shuffle(&persons[0], &persons[lines - 1]);    
    
    // Print Education Dataset
    cout << endl << "---- EDUCATION DATASET -----" << endl;
    for (i = 0; i < lines; i++) {
        const auto personFullName = persons[i]->name; 
        const auto personSex = persons[i]->sex;
        const auto hash_value = mm_hash(personFullName.c_str());
        size_t age = hash_value % 5;
        age += 15;
        int days_absent = rand() % 15;
        days_absent++;
        int status = rand() % 3;
        std::string strStatus;
        switch (status) {
            case 0:
                    strStatus = "Low";
                    break;
            case 1:
                    strStatus = "Medium";
                    break;
            case 2:
                    strStatus = "High";
                    break;
        }

        cout << setw(5) << i+1 << ", " << setw(30) <<  personFullName <<", " << setw(20) << hash_value << ", "
             << age << ", " << setw(6) << personSex << ", " << setw(2) << days_absent << ", " << setw(6) 
             << strStatus << "." << endl;

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

