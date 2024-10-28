#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h> 
#include <sstream>   
#include <algorithm> 

std::pair<int, int> get_terminal_size() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return { csbi.srWindow.Bottom - csbi.srWindow.Top + 1, csbi.srWindow.Right - csbi.srWindow.Left + 1 };
}

std::string center_text(const std::string& text, int terminal_width) {
    std::string centered;
    std::istringstream iss(text);
    std::string line;
    while (std::getline(iss, line)) {
        int padding = (terminal_width - line.length()) / 2;
        centered += std::string(padding > 0 ? padding : 0, ' ') + line + "\n";
    }
    return centered;
}

void clear_console() {
    system("cls");
}

void maximize_console() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);
}

void animate_ascii(const std::vector<std::string>& frames, double delay) {
    auto terminal_size = get_terminal_size();
    int terminal_height = terminal_size.first;
    int terminal_width = terminal_size.second;

    clear_console();

    for (const auto& frame : frames) {
        std::string centered_frame = center_text(frame, terminal_width);
        std::cout << centered_frame << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(delay * 1000)));
        clear_console();
    }
}

int main() {
    maximize_console();

    std::vector<std::string> frames; // REMEMBER TO EXTRACT THE FOLDER 
    std::string base_path = "C:\\Users\\YourName\\Documents\\GIFS\\TEXTFILE\\"; //Folder where you put your ascii textfiles

    for (int i = 1; i < 134; ++i) { //134 means that I have 133 textfile inside my folder
        std::string file_name = base_path + "ASCII-" + std::to_string(i) + ".txt"; // IT READS THE ASCII-(1-133) NAMES OF YOU FILE, REMEMBER TO CHANGE YOUR FILE NAME IN SEQUENCE TO PREVENT FRAME STUTTERING
        std::ifstream file(file_name);
        if (file) {
            std::string frame((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            frames.push_back(frame);
        }
        else {
            std::cerr << "File " << file_name << " not found." << std::endl;
        }
    }


    std::cout << "Press Enter to start the animation..." << std::endl; //waits until you press the ENTER key on you keyboard..
    std::cin.get();

    if (!frames.empty()) {
        animate_ascii(frames, 0.0977); //delay of each frame to be printed
    }
    else {
        std::cout << "No frames to display." << std::endl;
    }

    return 0;
}
