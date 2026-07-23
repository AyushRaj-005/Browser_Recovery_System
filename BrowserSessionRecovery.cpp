#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

const string SESSION_FILE = "session.txt";


class Tab {
public:
    string websiteName;
    string url;
    string category;
    string openingTime;

    // Default constructor - creates a blank tab
    Tab() {
        websiteName = "";
        url = "";
        category = "";
        openingTime = "";
    }

    // Parameterized constructor - creates a tab with actual data
    Tab(string websiteName, string url, string category, string openingTime) {
        this->websiteName = websiteName;
        this->url = url;
        this->category = category;
        this->openingTime = openingTime;
    }

    // Displays all details of this tab
    void displayTab(int tabNumber) const {
        cout << "-------------------------------------------" << endl;
        cout << "Tab Number   : " << tabNumber << endl;
        cout << "Website Name : " << websiteName << endl;
        cout << "URL          : " << url << endl;
        cout << "Category     : " << category << endl;
        cout << "Opening Time : " << openingTime << endl;
    }

    // Converts tab details into one text line (for saving to file)
    // Example: YouTube|www.youtube.com|Entertainment|10:30 AM
    string toFileString() const {
        return websiteName + "|" + url + "|" + category + "|" + openingTime;
    }

    // Creates a Tab object back from a saved text line (for loading)
    static Tab fromFileString(const string &line) {
        string parts[4];
        int index = 0;
        stringstream ss(line);
        string segment;

        while (getline(ss, segment, '|') && index < 4) {
            parts[index] = segment;
            index++;
        }

        return Tab(parts[0], parts[1], parts[2], parts[3]);
    }
};


class Browser {
private:
    vector<Tab> openTabs;     // Stack of currently open tabs
    vector<Tab> closedTabs;   // Stack of closed tabs (history)

    int totalOpened;
    int totalClosed;
    int totalRestored;
    int totalSearches;
    int totalSessionsSaved;

    // Checks if a website is already open (to prevent duplicates)
    bool isDuplicateWebsite(const string &websiteName) const {
        for (size_t i = 0; i < openTabs.size(); i++) {
            if (openTabs[i].websiteName == websiteName) {
                return true;
            }
        }
        return false;
    }

public:
    Browser() {
        totalOpened = 0;
        totalClosed = 0;
        totalRestored = 0;
        totalSearches = 0;
        totalSessionsSaved = 0;
    }

    // ---------- 1. Open New Tab ----------
    void openNewTab() {
        string websiteName, url, category, openingTime;

        cin.ignore();

        cout << "\nEnter Website Name : ";
        getline(cin, websiteName);

        if (websiteName.empty()) {
            cout << "Invalid Input! Website name cannot be empty.\n";
            return;
        }

        if (isDuplicateWebsite(websiteName)) {
            cout << "Duplicate Website! \"" << websiteName << "\" is already open.\n";
            return;
        }

        cout << "Enter URL : ";
        getline(cin, url);

        cout << "Enter Category (Education/Entertainment/Work/Other) : ";
        getline(cin, category);

        cout << "Enter Opening Time (e.g. 10:30 AM) : ";
        getline(cin, openingTime);

        Tab newTab(websiteName, url, category, openingTime);
        openTabs.push_back(newTab);   // push operation

        totalOpened++;
        cout << "\nTab Opened Successfully!\n";
    }

    // ---------- 2. Close Current Tab ----------
    void closeCurrentTab() {
        if (openTabs.empty()) {
            cout << "\nNo Tabs Open! Stack is empty.\n";
            return;
        }

        Tab topTab = openTabs.back();

        openTabs.pop_back();
        closedTabs.push_back(topTab);

        totalClosed++;
        cout << "\nTab Closed Successfully.\n";
        cout << "Closed Tab: " << topTab.websiteName << endl;
    }

    // ---------- 3. Restore Last Closed Tab ----------
    void restoreLastClosedTab() {
        if (closedTabs.empty()) {
            cout << "\nNo Closed Tabs Available to Restore.\n";
            return;
        }

        Tab lastClosed = closedTabs.back();

        closedTabs.pop_back();
        openTabs.push_back(lastClosed);

        totalRestored++;
        cout << "\nRecovered Successfully.\n";
        cout << "Restored Tab: " << lastClosed.websiteName << endl;
    }

    // ---------- 4. Show Current Open Tabs ----------
    void showOpenTabs() const {
        if (openTabs.empty()) {
            cout << "\nNo Tabs are currently open.\n";
            return;
        }

        cout << "\n============ CURRENTLY OPEN TABS ============\n";
        for (int i = (int)openTabs.size() - 1, tabNumber = 1; i >= 0; i--, tabNumber++) {
            openTabs[i].displayTab(tabNumber);
        }
        cout << "-------------------------------------------" << endl;
    }

    // ---------- 5. Show Closed Tabs History ----------
    void showClosedTabs() const {
        if (closedTabs.empty()) {
            cout << "\nNo Closed Tabs in History.\n";
            return;
        }

        cout << "\n============ CLOSED TABS HISTORY ============\n";
        for (int i = (int)closedTabs.size() - 1, tabNumber = 1; i >= 0; i--, tabNumber++) {
            closedTabs[i].displayTab(tabNumber);
        }
        cout << "-------------------------------------------" << endl;
    }

    // ---------- 6. Save Session ----------
    void saveSession() {
        ofstream outFile(SESSION_FILE);

        if (!outFile) {
            cout << "\nError! Could not create/open session file.\n";
            return;
        }

        if (openTabs.empty()) {
            cout << "\nNo Open Tabs to save.\n";
            outFile.close();
            return;
        }

        for (size_t i = 0; i < openTabs.size(); i++) {
            outFile << openTabs[i].toFileString() << endl;
        }

        outFile.close();
        totalSessionsSaved++;
        cout << "\nSession Saved Successfully to \"" << SESSION_FILE << "\"\n";
    }

    // ---------- 7. Load Previous Session ----------
    void loadSession() {
        ifstream inFile(SESSION_FILE);

        if (!inFile) {
            cout << "\nError! Session file not found. Please save a session first.\n";
            return;
        }

        openTabs.clear();

        string line;
        int count = 0;
        while (getline(inFile, line)) {
            if (!line.empty()) {
                openTabs.push_back(Tab::fromFileString(line));
                count++;
            }
        }

        inFile.close();

        if (count == 0) {
            cout << "\nSession file is empty. Nothing to load.\n";
        } else {
            cout << "\nSession Loaded Successfully! " << count << " tab(s) restored.\n";
        }
    }

    // ---------- 8. Search Open Tab ----------
    void searchTab() {
        if (openTabs.empty()) {
            cout << "\nNo Open Tabs to search in.\n";
            return;
        }

        string searchName;
        cin.ignore();
        cout << "\nEnter Website Name to search : ";
        getline(cin, searchName);

        totalSearches++;

        for (size_t i = 0; i < openTabs.size(); i++) {
            if (openTabs[i].websiteName == searchName) {
                cout << "\nTab Found!\n";
                openTabs[i].displayTab((int)i + 1);
                return;
            }
        }

        cout << "\nNo Tab Found.\n";
    }

    // ---------- 9. Clear All Tabs ----------
    void clearAllTabs() {
        if (openTabs.empty()) {
            cout << "\nNo Open Tabs to clear.\n";
            return;
        }

        char choice;
        cout << "\nAre you sure you want to close ALL tabs? (Y/N) : ";
        cin >> choice;

        if (choice == 'Y' || choice == 'y') {
            while (!openTabs.empty()) {
                closedTabs.push_back(openTabs.back());
                openTabs.pop_back();
                totalClosed++;
            }
            cout << "\nAll Tabs have been closed and moved to history.\n";
        } else {
            cout << "\nOperation Cancelled.\n";
        }
    }

    // ---------- 10. Browser Statistics ----------
    void showStatistics() const {
        cout << "\n============ BROWSER STATISTICS ============\n";
        cout << "Currently Open Tabs   : " << openTabs.size() << endl;
        cout << "Currently Closed Tabs : " << closedTabs.size() << endl;
        cout << "Total Tabs Opened     : " << totalOpened << endl;
        cout << "Total Tabs Closed     : " << totalClosed << endl;
        cout << "Total Tabs Restored   : " << totalRestored << endl;
        cout << "Total Searches Made   : " << totalSearches << endl;
        cout << "Total Sessions Saved  : " << totalSessionsSaved << endl;
        cout << "-------------------------------------------" << endl;
    }
};

/* ===================================================================
   FUNCTION: showMenu
   -------------------------------------------------------------------
   Displays the main menu on the screen.
   =================================================================== */
void showMenu() {
    cout << "\n===============================================\n";
    cout << "       BROWSER SESSION RECOVERY SYSTEM\n";
    cout << "===============================================\n";
    cout << " 1. Open New Tab\n";
    cout << " 2. Close Current Tab\n";
    cout << " 3. Restore Last Closed Tab\n";
    cout << " 4. Show Current Open Tabs\n";
    cout << " 5. Show Closed Tabs History\n";
    cout << " 6. Save Session\n";
    cout << " 7. Load Previous Session\n";
    cout << " 8. Search Open Tab\n";
    cout << " 9. Clear All Tabs\n";
    cout << "10. Browser Statistics\n";
    cout << "11. Exit\n";
    cout << "===============================================\n";
    cout << "Enter your choice : ";
}

/* ===================================================================
   FUNCTION: main
   -------------------------------------------------------------------
   Entry point. Shows the menu in a loop and calls the matching
   Browser function based on user choice.
   =================================================================== */
int main() {
    Browser myBrowser;
    int choice;

    cout << "Welcome to the Browser Session Recovery System!\n";

    do {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid Input! Please enter a number between 1 and 11.\n";
            continue;
        }

        switch (choice) {
            case 1: myBrowser.openNewTab(); break;
            case 2: myBrowser.closeCurrentTab(); break;
            case 3: myBrowser.restoreLastClosedTab(); break;
            case 4: myBrowser.showOpenTabs(); break;
            case 5: myBrowser.showClosedTabs(); break;
            case 6: myBrowser.saveSession(); break;
            case 7: myBrowser.loadSession(); break;
            case 8: myBrowser.searchTab(); break;
            case 9: myBrowser.clearAllTabs(); break;
            case 10: myBrowser.showStatistics(); break;
            case 11:
                cout << "\nThank you for using Browser Session Recovery System!\n";
                cout << "Exiting Program...\n";
                break;
            default:
                cout << "\nInvalid Choice! Please select between 1 and 11.\n";
        }

    } while (choice != 11);

    return 0;
}
