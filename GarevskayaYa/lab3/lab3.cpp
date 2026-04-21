#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_WORDS = 1000;

class Dictionary {
private:

    string english[MAX_WORDS];
    string russian[MAX_WORDS];
    int size;

public:

    Dictionary() {
        size = 0;
    }

    ~Dictionary() {
    }

    void addWord(string eng, string rus) {
        for (int i = 0; i < size; i++) {
            if (english[i] == eng) {
                cout << "Word already exists " << endl;
                return;
            }
        }

        if (size < MAX_WORDS) {
            english[size] = eng;
            russian[size] = rus;
            size++;
            cout << "Word added successfully" << endl;
        }
        else {
            cout << "Dictionary is full" << endl;
        }
    }

    void changeWord(string eng) {
        int index = -1;

        for (int i = 0; i < size; i++) {
            if (english[i] == eng) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            string newTranslation;
            cout << "Enter new translation: ";
            cin >> newTranslation;
            russian[index] = newTranslation;
            cout << "Translation updated" << endl;
        }
        else {
            cout << "Word not found" << endl;

            char answer;
            cout << "Do you want to add it? (y/n): ";
            cin >> answer;
            if (answer == 'y' || answer == 'Y') {
                string rusTranslation;
                cout << "Enter russian translation: ";
                cin >> rusTranslation;
                addWord(eng, rusTranslation);
            }
        }
    }

    void engToRus(string eng) {
        int index = -1;

        for (int i = 0; i < size; i++) {
            if (english[i] == eng) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            cout << english[index] << " - " << russian[index] << endl;
        }
        else {
            cout << "Translation not found" << endl;

            char answer;
            cout << "Do you want to add it? (y/n): ";
            cin >> answer;
            if (answer == 'y' || answer == 'Y') {
                string rusTranslation;
                cout << "Enter russian translation : ";
                cin >> rusTranslation;
                addWord(eng, rusTranslation);
            }
        }
    }

    void rusToEng(string rus) {
        int index = -1;
        for (int i = 0; i < size; i++) {
            if (russian[i] == rus) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            cout << russian[index] << " - " << english[index] << endl;
        }
        else {
            cout << "Translation not found" << endl;

            char answer;
            cout << "Do you want to add it? (y/n): ";
            cin >> answer;
            if (answer == 'y' || answer == 'Y') {
                string engTranslation;
                cout << "Enter english translation: ";
                cin >> engTranslation;
                addWord(engTranslation, rus);
            }
        }
    }

    void translateLine(string line) {
        string word = "";
        for (int i = 0; i <= line.length(); i++) {
            if (line[i] == ' ' || line[i] == '\0') {
                if (word != "") {
                    int index = -1;
                    for (int j = 0; j < size; j++) {
                        if (english[j] == word) {
                            index = j;
                            break;
                        }
                    }
                    if (index != -1) {
                        cout << russian[index] << " ";
                    }
                    else {
                        cout << "[" << word << "] ";
                    }
                    word = "";
                }
            }
            else {
                word = word + line[i];
            }
        }
        cout << endl;
    }

    void getSize() {
        cout << "Number of words in dictionary: " << size << endl;
    }

    void saveToFile(string filename) {
        ofstream file(filename);
        if (!file) {
            cout << "Error opening file for writing" << endl;
            return;
        }

        for (int i = 0; i < size; i++) {
            file << english[i] << " " << russian[i] << endl;
        }
        file.close();
        cout << "Dictionary saved to " << filename << endl;
    }

    void loadFromFile(string filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file for reading" << endl;
            return;
        }

        size = 0;
        string eng, rus;
        while (file >> eng >> rus && size < MAX_WORDS) {
            english[size] = eng;
            russian[size] = rus;
            size++;
        }

        file.close();
        cout << "Loaded " << size << " words from " << filename << endl;
    }
};

int main() {

    Dictionary dict;
    int choice;
    string word, translation, filename, line;

    do {
        cout << "\nMenu" << endl;
        cout << "1. Add word" << endl;
        cout << "2. Change translation" << endl;
        cout << "3. English to Russian" << endl;
        cout << "4. Russian to English" << endl;
        cout << "5. Translate line" << endl;
        cout << "6. Show number of words" << endl;
        cout << "7. Save to file" << endl;
        cout << "8. Load from file" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter english word: ";
            cin >> word;
            cout << "Enter russian translation: ";
            cin >> translation;
            dict.addWord(word, translation);
            break;
        case 2:
            cout << "Enter english word: ";
            cin >> word;
            dict.changeWord(word);
            break;
        case 3:
            cout << "Enter english word: ";
            cin >> word;
            dict.engToRus(word);
            break;
        case 4:
            cout << "Enter russian word: ";
            cin >> word;
            dict.rusToEng(word);
            break;
        case 5:
            cout << "Enter english line: ";
            cin.ignore();
            getline(cin, line);
            dict.translateLine(line);
            break;
        case 6:
            dict.getSize();
            break;
        case 7:
            cout << "Enter filename: ";
            cin >> filename;
            dict.saveToFile(filename);
            break;
        case 8:
            cout << "Enter filename: ";
            cin >> filename;
            dict.loadFromFile(filename);
            break;
        case 0:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 0);

    return 0;
}