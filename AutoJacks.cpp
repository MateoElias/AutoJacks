#include <iostream>
#include <string>
#include <windows.h>
#include <vector>

using std::string, std::cout, std::cin, std::vector;

string num_to_word(int number){
    // Number Values
    string ones[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    string teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen","sixteen", "seventeen", "eighteen", "nineteen"};
    string tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    if(number < 10){
        return ones[number];
        } else if (number < 20) {
            return teens [number - 10];
        } else if (number < 100) {
            return tens[number / 10] + ((number % 10 != 0) ? " " + num_to_word(number % 10) : "");
        } else if (number < 1000) {
            return num_to_word(number / 100) + " hundred" + ((number % 100 != 0) ? " " + num_to_word(number % 100) : "");
        }
        return "error";
}

void keyboard_write(string message){
    
    // Press '/' to trigger the chat
    INPUT slash[2] = {};
    slash[0].type = INPUT_KEYBOARD;
    slash[0].ki.wVk = 0xBF;
    slash[0].ki.dwFlags = KEYEVENTF_UNICODE;

    slash[1].type = INPUT_KEYBOARD;
    slash[1].ki.wVk = 0xBF;
    slash[1].ki.dwFlags = KEYEVENTF_KEYUP;

    // String Input
    std::vector<INPUT> vec;
    for(auto ch : message)
    {
        INPUT input = { 0 };

        input.type = INPUT_KEYBOARD;
        input.ki.dwFlags = KEYEVENTF_UNICODE;
        input.ki.wScan = ch;
        vec.push_back(input);

        input.ki.dwFlags |= KEYEVENTF_KEYUP;
        vec.push_back(input);
    }

    // Press 'enter' to send 0x0D
    INPUT enter[2] = {};
    enter[0].type = INPUT_KEYBOARD;
    enter[0].ki.wVk = 0x0D;
    enter[0].ki.dwFlags = KEYEVENTF_UNICODE;

    enter[1].type = INPUT_KEYBOARD;
    enter[1].ki.wVk = 0x0D;
    enter[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, slash, sizeof(INPUT));
    Sleep(1000);
    SendInput(vec.size(), vec.data(), sizeof(INPUT));
    SendInput(2, enter, sizeof(INPUT));
    return;
}

// Main Function
int main(){
    // Variables
    int amount;

    cout << "How many JJs do you wish to do?\n";
    cin >> amount;

    for(int i = 1; i <= amount; i++){
        keyboard_write(num_to_word(i));
    }
    return 0;
}
