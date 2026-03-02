#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Time {

private:
    int hours;
    int minutes;
    int seconds;

public:
    Time() : hours(0), minutes(0), seconds(0) {}

    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

    void setTime(int h, int m, int s) {
        hours = h;
        minutes = m;
        seconds = s;
    }

    void showTime() const {
        if (hours < 10) cout << "0";
        cout << hours << ":";

        if (minutes < 10) cout << "0";
        cout << minutes << ":";

        if (seconds < 10) cout << "0";
        cout << seconds << endl;
    }

    void difference(int h, int m, int s) const {
        int curr = hours * 3600 + minutes * 60 + seconds;
        int other = h * 3600 + m * 60 + s;
        int diff = other - curr;

        if (diff < 0) {
            cout << "-";
            diff = -diff;
        }

        int dh = diff / 3600;
        int dm = (diff % 3600) / 60;
        int ds = diff % 60;

        if (dh < 10) cout << "0";
        cout << dh << ":";

        if (dm < 10) cout << "0";
        cout << dm << ":";

        if (ds < 10) cout << "0";
        cout << ds << endl;
    }

    void shiftForward(int h, int m, int s) {
        seconds += s;
        minutes += m + seconds / 60;
        seconds %= 60;
        hours += h + minutes / 60;
        minutes %= 60;
        hours %= 24;
    }

    void shiftBackward(int h, int m, int s) {
        seconds -= s;
        if (seconds < 0) {
            seconds += 60;
            minutes--;
        }

        minutes -= m;
        if (minutes < 0) {
            minutes += 60;
            hours--;
        }

        hours -= h;
        if (hours < 0) {
            hours += 24;
        }
    }
};

int main() {

    Time t;
    int choice, h, m, s;

    do {
        cout << "1. Set time\n";
        cout << "2. Show time\n";
        cout << "3. Difference with another time\n";
        cout << "4. Shift forward\n";
        cout << "5. Shift backward\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cout << "\n";

        switch (choice) {
        case 1:
            cout << "Enter hours minutes seconds: ";
            cin >> h >> m >> s;
            t.setTime(h, m, s);
            cout << "Time set: ";
            t.showTime();
            break;

        case 2:
            cout << "Current time: ";
            t.showTime();
            break;

        case 3:
            cout << "Enter time to compare: ";
            cin >> h >> m >> s;
            cout << "Difference: ";
            t.difference(h, m, s);
            break;

        case 4:
            cout << "Enter shift: ";
            cin >> h >> m >> s;
            t.shiftForward(h, m, s);
            cout << "New time: ";
            t.showTime();
            break;

        case 5:
            cout << "Enter shift: ";
            cin >> h >> m >> s;
            t.shiftBackward(h, m, s);
            cout << "New time: ";
            t.showTime();
            break;

        case 0:
            break;
        }
        cout << "\n";

    } while (choice != 0);

    return 0;
}