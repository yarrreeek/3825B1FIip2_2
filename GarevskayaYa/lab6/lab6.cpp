#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class BullsAndCows {
private:
    int length;
    string secret;
    int attempts;
    int bulls;
    int cows;

    string generateSecret(int n) {
        string digits = "0123456789";
        for (int i = 9; i > 0; --i) {
            int j = rand() % (i + 1);
            swap(digits[i], digits[j]);
        }

        string result = digits.substr(0, n);

        if (n > 1 && result[0] == '0') {
            for (int i = 1; i < n; ++i) {
                if (result[i] != '0') {
                    swap(result[0], result[i]);
                    break;
                }
            }
        }
        return result;
    }

    bool isValidGuess(const string& guess) {
        if (guess.length() != length) return false;
        if (length > 1 && guess[0] == '0') return false;

        bool used[10] = { false };
        for (int i = 0; i < length; ++i) {
            if (guess[i] < '0' || guess[i] > '9') return false;
            int digit = guess[i] - '0';
            if (used[digit]) return false;
            used[digit] = true;
        }
        return true;
    }

    void calculate(const string& guess) {
        bulls = 0;
        cows = 0;

        bool secretUsed[10] = { false };
        bool guessUsed[10] = { false };

        for (int i = 0; i < length; ++i) {
            if (guess[i] == secret[i]) {
                bulls++;
                secretUsed[i] = true;
                guessUsed[i] = true;
            }
        }

        for (int i = 0; i < length; ++i) {
            if (guessUsed[i]) continue;
            for (int j = 0; j < length; ++j) {
                if (!secretUsed[j] && guess[i] == secret[j]) {
                    cows++;
                    secretUsed[j] = true;
                    break;
                }
            }
        }
    }

public:
    BullsAndCows(int n) : length(n), attempts(0), bulls(0), cows(0) {
        secret = generateSecret(n);
    }

    bool playRound() {
        string guess;

        while (true) {
            cout << "Attempt " << attempts + 1 << ". Enter " << length
                << "-digit number (digits must not repeat): ";
            cin >> guess;

            if (!isValidGuess(guess)) {
                cout << "Error! Number must consist of " << length
                    << " non-repeating digits and not start with 0.\n";
                continue;
            }

            calculate(guess);
            attempts++;

            cout << "Bulls: " << bulls << ", Cows: " << cows << endl;

            if (bulls == length) {
                cout << "\nCongratulations! You guessed the number " << secret
                    << " in " << attempts << " attempts!\n";
                return true;
            }
            break;
        }
        return false;
    }

    string getSecret() const { return secret; }
};

int main() {
    srand(time(nullptr));

    cout << "Bulls and Cows Game\n";

    int n;
    while (true) {
        cout << "Enter the length of the number (1 to 10): ";
        cin >> n;

        if (cin.fail() || n < 1 || n > 10) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Try again.\n";
        }
        else {
            break;
        }
    }

    BullsAndCows game(n);

    while (true) {
        if (game.playRound()) {
            char choice;
            cout << "\nPlay again? (y/n): ";
            cin >> choice;
            if (choice != 'y' && choice != 'Y') {
                cout << "Thanks for playing!\n";
                break;
            }
            while (true) {
                cout << "Enter new length of the number: ";
                cin >> n;
                if (cin.fail() || n < 1 || n > 10) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input.\n";
                }
                else {
                    break;
                }
            }
            BullsAndCows newGame(n);
            game = newGame;
        }
    }

    return 0;
}