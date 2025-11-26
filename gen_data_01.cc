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
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cstdlib>

#include "faker-cxx/Person.h"

using namespace std;


enum {
BUFF = 100,
MAX_LINES = 1000
};
using glasgow_type = enum {GLASGOW_NORM, GLASGOW_EYE, GLASGOW_MOTOR, GLASGOW_VERBAL};



// Initial Hashing function
auto mm_hash(char const *input) -> size_t;

auto main(int argc, char *argv[]) -> int {
    int eye_response = 0;
    int motor_response = 0;
    int verbal_response = 0;
    int glasgow = 0;
    int lines = 0;
    char str[BUFF+1];
    glasgow_type selected_glasgow = GLASGOW_NORM;
    int i = 0;

    // Command line processing
    if (argc > 3) {
        cerr << argv[0] << ": wrong command line!" << endl;
        cerr << "syntax: " << argv[0] << " <number_of_lines> (norm | eye | motor | verbal)" << endl;
        return -1;
    } else  if (argc == 1) {
        lines = MAX_LINES;
        selected_glasgow = GLASGOW_NORM;
    } else if (argc == 2) {
        if (sscanf(argv[1], "%d", &lines) != 1) {
            cerr << argv[0] << ": wrong number of lines!" << endl;
            cerr << "syntax: " << argv[0] << " <number_of_lines> (norm | eye | motor | verbal)" << endl;
            return -2;
        }
        selected_glasgow = GLASGOW_NORM;
    } else {
        if (sscanf(argv[1], "%d", &lines) != 1) {
            cerr << argv[0] << ": wrong number of lines!" << endl;
            cerr << "syntax: " << argv[0] << " <number_of_lines> (norm | eye | motor | verbal)" << endl;
            return -2;
        }
        if (sscanf(argv[2], "%s", str) != 1) {
            cerr << argv[0] << ": wrong glasgow type!" << endl;
            cerr << "syntax: " << argv[0] << " <number_of_lines> (norm | eye | motor | verbal)" << endl;
            return -3;
        }
        if (strcmp(str, "norm") == 0) {
            selected_glasgow = GLASGOW_NORM;
        } else if (strcmp(str, "eye") == 0) {
            selected_glasgow = GLASGOW_EYE;
        } else if (strcmp(str, "motor") == 0) {
            selected_glasgow = GLASGOW_MOTOR;
        } else if (strcmp(str, "verbal") == 0) {
            selected_glasgow = GLASGOW_VERBAL;
        } else {
            cerr << argv[0] << ": wrong glasgow type!" << endl;
            cerr << "syntax: " << argv[0] << " <number_of_lines> (norm | eye | motor | verbal)" << endl;
            return -4;
        }
    }
    
    // Seed generation
    srand((unsigned int)time(nullptr));

    for (i = 0; i < lines; i++) {
        // Fake Personal data generation
        const auto person = new faker::Person(); 
        const auto person_full_name = person->fullName(faker::Country::England);
        delete person;
        // Random generation of eye_response in [1..4]
        do {
            eye_response = rand() % 5;
        } while (eye_response ==  0);
        // Random generation of motor_response in [1..6]
        do {
            motor_response = rand() % 7;
        } while (motor_response == 0);
        // Random generation of verbal_response in [1..5]
        do {
            verbal_response = rand() % 6;
        } while (verbal_response == 0);
        switch (selected_glasgow) {
            case GLASGOW_NORM:
                // No predominance
                glasgow = eye_response + motor_response + verbal_response;
                break;
            case GLASGOW_EYE: 
                // Predominance assigned to eye response
                glasgow = ((20 * eye_response) + motor_response + verbal_response) *  0.13636363636;
                break;
            case GLASGOW_MOTOR:
                // Predominance assigned to motor response     
                glasgow = (eye_response + (20 * motor_response) + verbal_response) *  0.13636363636;
                break;
            case GLASGOW_VERBAL:
                // Predominance assigned to verbal response     
                glasgow = (eye_response + motor_response + (20 * verbal_response)) *  0.13636363636;
                break;
            default:
                // No predominance
                glasgow = eye_response + motor_response + verbal_response;;
                break;

        }

        cout << setw(5) << i+1 << ", " << setw(30) <<  person_full_name <<", " << setw(20) << mm_hash(person_full_name.c_str()) << ", "
             << setw(2) << eye_response << ", " << setw(3) << motor_response << ", " << setw(3) << verbal_response << ", "
             << setw(2) << glasgow << "." << endl;

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
