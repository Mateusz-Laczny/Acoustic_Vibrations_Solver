#include <iostream>
#include <string>
#include "Eigen/Dense"
#include "main_calculations.h"
#include "Functions/Function.h"
#include "Functions/FunctionCombination.h"
#include "function_util.h"

using Eigen::VectorXd;
using std::cout;
using std::cin;
using std::endl;

const int number_of_commands = 5;

int parse_command(const std::string& command, const std::string commands_codes[5]) {
    for(int i = 0; i < number_of_commands; i++) {
        if(commands_codes[i] == command) {
            return i;
        }
    }

    return -1;
}

int main() {
    bool running = true;
    const std::string commands_codes[5] = {"solve", "visualize", "info", "help", "quit"};
    std::string command_prompt = "$> ";

    std::string program_info = "=============================================================== \n"
                               "| Solver for the acoustic vibrations problem made by          | \n"
                               "| Mateusz Łączny for DE's laboratories 2020/2021              | \n"
                               "| This program uses the Eigen library for solving linear      | \n"
                               "| systems for equations. More information about this library  | \n"
                               "| can be found here: www.eigen.tuxfamily.org                  | \n"
                               "| This program uses Gnuplot; more information about this      | \n"
                               "| program can be found here: www.gnuplot.info                 | \n"
                               "=============================================================== \n";

    std::string command_help = "=============================================================== \n"
                               "| To get the solution type 'solve' (without the quotation     | \n"
                               "| marks) and then specify the number of parts to divide       | \n"
                               "| the problem domain ([0, 2] line segment) into.              | \n"
                               "| To visualize the last solution type 'visualize'             | \n"
                               "| To view program info type 'info'                            | \n"
                               "| To show the available commands at any moment type 'help'    | \n"
                               "| To quit the program type 'quit'                             | \n"
                               "=============================================================== \n";

    cout << "=============================================================== \n";
    cout << "| Welcome to the solver for the acoustic vibrations problem!  | \n";
    cout << "|                                                             | \n";
    cout << "| To get the solution type 'solve' (without the quotation     | \n";
    cout << "| marks) and then specify the number of parts to divide       | \n";
    cout << "| the problem domain ([0, 2] line segment) into.              | \n";
    cout << "| To visualize the last solution type 'visualize'             | \n";
    cout << "| To view program info type 'info'                            | \n";
    cout << "| To show the available commands at any moment type 'help'    | \n";
    cout << "| To quit the program type 'quit'                             | \n";
    cout << "=============================================================== \n";
    cout << '\n';

    FunctionCombination current_solution = FunctionCombination();
    bool has_solution = false;

    std::string current_command;
    std::string current_keyword;
    std::string current_argument;

    int number_of_parts;

    while (running) {
        current_command = "";

        cout << command_prompt;
        cin >> current_command;

        int command_code = parse_command(current_command, commands_codes);

        switch (command_code) {
            case 0:
                cin >> number_of_parts;
                if(number_of_parts > 0) {
                    current_solution = solve(number_of_parts);
                    has_solution = true;
                } else {
                    cout << "Incorrect number of parts, please give a non-negative integer \n";
                }

                break;
            case 1:
                if(has_solution) {
                    visualize(current_solution, 0, 2);
                } else {
                    cout << "No solution generated; use 'solve' command to generate a solution \n";
                }

                break;
            case 2:
                cout << program_info;
                break;
            case 3:
                cout << command_help;
                break;
            case 4:
                running = false;
                break;
            default:
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Command not found; type 'help' (without quotation marks) for help \n";
                break;
        }
    }

    cout << "Closing program...";
    return 0;
}
