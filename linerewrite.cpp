// LineReWrite - A simple line by line text editor
// Copyright (C) 2018 Thomas Bruninx
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <exception>

using namespace std;

enum options_t {
	INSERT 		= 	0b00000001,
	BACKUP 		= 	0b00000010,
	MULTILINE	= 	0b00000100,
	REMOVE 		= 	0b00001000,
	PRINT 		= 	0b00010000,
	NOCHANGE 	= 	0b00100000
};

int main(int argc, char *argv[]) {
	string filename = "", temp_line;
	size_t line_nr = 0;
	uint8_t options = 0;
	vector<string> content;
	
	// Retrieve filename and line_nr from arguments
	if (argc > 2) {
		filename = argv[1];
		try {
			line_nr = stoul(argv[2]);
		} catch (exception& ex) {
			cerr << "Error: make sure line_nr is numerical" << endl;
			return -1;
		}
	} else {
		cout << "Usage: rewrite [filename] [line_nr] [options]" << endl
		<< "Options: B = Backup, I = Insert, M = Multiline," << endl 
		<< "         R = Remove, P = Print, N = No Change" << endl;
		return -1;
	}

	// Check for option parameters
	if (argc > 3) {
		for (int i = 0; i < strlen(argv[3]); i++) {
			switch (toupper(argv[3][i])) {
				case 'I':
					options |= INSERT;
					break;
				case 'B':
					options |= BACKUP;
					break;
				case 'M':
					options |= MULTILINE;
					break;
				case 'R':
					options |= REMOVE;
					break;
				case 'P':
					options |= PRINT;
					break;
				case 'N':
					options |= NOCHANGE;
				default:
					break;
			}
		} 
	}

	// If file doesn't exist or unable to open, exit program
	ifstream file_in(filename, ios::in);
	if (!file_in.good()) {
		cerr << "Error: couldn't open file: " << filename << endl;
		return -1;
	}

	// Read file contents into memory
	while (getline(file_in, temp_line)) {
		content.push_back(temp_line);
	}
	file_in.close();

	// Make a backup if necessary
	if (options & BACKUP) {
		ofstream file_out(filename + ".bak", ios::out|ios::trunc);
		for (int i = 0; i < content.size(); i++) {
			file_out << content.at(i) << endl;
		}
		file_out.close();
	}

	// Print out the file line by line if nevessary
	if (options & PRINT) {
		for (int i = line_nr; i < content.size(); i++) {
			cout << filename << ":" << i << ">" << content.at(i) << endl;
		}
	}

	// Check if the user wants to change content
	if (!(options & NOCHANGE)) {
		// Remove line if necessary
		if (options & REMOVE) {
			if (line_nr < content.size()) {
				content.erase(content.begin() + line_nr);
			} else {
				cerr << "Error: make sure line_nr is not higher than file line amount" << endl;
				return -1;
			}
		} else {
			// Let user edit requested line
			do {
				cout << filename << ":" << (line_nr > content.size() ? content.size() : line_nr) << ">";
				getline(cin, temp_line);
				if (temp_line != "") {
					if (line_nr >= content.size()) {
						content.push_back(temp_line);
					} else {
						// options = INSERT?
						if (options & INSERT) content.insert(content.begin() + line_nr, temp_line);
						else content.at(line_nr) = temp_line;
					}
					line_nr++;
				}
			// Repeat edit action if user used MULTILINE parameter
			} while (temp_line != "" && (options & MULTILINE));
		}

		// Write file back
		ofstream file_out(filename, ios::out|ios::trunc);
		for (int i = 0; i < content.size(); i++) {
			file_out << content.at(i) << endl;
		}
		file_out.close();
	}

	return 0;
}