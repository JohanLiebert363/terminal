#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

// who uses coments in the big 25
int sum(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }


void setColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}


void printBetterC() {
    setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    const char *art[] = {
        "   ******   ",
        " *        * ",
        "*  ****   * ",
        "* *       * ",
        "* *       * ",
        "*  ****   * ",
        " *        * ",
        "   ******   "
    };
    for (int i = 0; i < 8; i++) {
        printf("%s\n", art[i]);
    }
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}


void generatePassword() {
    int length;
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
    int charsetSize = strlen(charset);

    printf("Enter password length: ");
    scanf("%d", &length);

    if (length <= 0 || length > 100) {
        printf("Invalid length!\n");
        return;
    }

    char password[101];
    srand((unsigned int)time(NULL));

    for (int i = 0; i < length; i++) {
        password[i] = charset[rand() % charsetSize];
    }
    password[length] = '\0';

    printf("Generated password: %s\n", password);
}


void showTime() {
    printf("Press Ctrl+C to stop.\n");
    while (1) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        printf("\r%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);
        fflush(stdout);
        Sleep(1000);
    }
}


void runCalculator() {
    char option;
    int a, b, result;
    int history[1000];
    int history_index = 0;

    while (1) {
        setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("\nCalculator:\n");
        printf(" n for +\n m for -\n e for *\n d for /\n h for history\n q to quit calc\n> ");
        scanf(" %c", &option);
        option = tolower(option);

        if (option == 'q') {
            printf("Leaving calculator...\n");
            break;
        }

        if (option == 'h') {
            if (history_index == 0) {
                printf("No history saved yet.\n");
            } else {
                printf("\nCalculation History:\n");
                for (int i = 0; i < history_index; i++) {
                    printf("%d) %d\n", i + 1, history[i]);
                    Sleep(300);
                }
            }
            continue;
        }

        if (option != 'n' && option != 'm' && option != 'e' && option != 'd') {
            printf("Invalid option! Try again.\n");
            continue;
        }

        printf("Enter first number: ");
        if (scanf("%d", &a) != 1) {
            printf("Not a valid number!\n");
            break;
        }

        printf("Enter second number: ");
        if (scanf("%d", &b) != 1) {
            printf("Not a valid number!\n");
            break;
        }

        if (option == 'n') {
            result = sum(a, b);
            printf("Sum: %d\n", result);
        } else if (option == 'm') {
            result = sub(a, b);
            printf("Result: %d\n", result);
        } else if (option == 'e') {
            result = mul(a, b);
            printf("Product: %d\n", result);
        } else if (option == 'd') {
            if (b == 0) {
                printf("Error: Division by zero!\n");
                continue;
            } else {
                result = divide(a, b);
                printf("Quotient: %d\n", result);
            }
        }

        if (history_index < 1000) {
            history[history_index++] = result;
        } else {
            printf("History full! Cannot save more results.\n");
        }
    }
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}


void saySomething() {
    char sayInput[100];
    printf("Enter text to say (type 'exit' to stop):\n");
    while (1) {
        scanf("%99s", sayInput);
        if (strcmp(sayInput, "exit") == 0) break;
        printf("%s ", sayInput);
    }
    printf("\n");
}


void sysInfo() {
    char username[256];
    char computerName[256];
    DWORD size = 256;

    GetUserNameA(username, &size);
    size = 256;
    GetComputerNameA(computerName, &size);

    SYSTEM_INFO si;
    GetSystemInfo(&si);

    printf("=== System Info ===\n");
    printf("User: %s\n", username);
    printf("Computer: %s\n", computerName);
    printf("Processor Cores: %u\n", si.dwNumberOfProcessors);
}


void showIP() {
    printf("Your local IP:\n");
    system("ipconfig | findstr IPv4");
}

void noteManager() {
    char choice[10];
    char buffer[256];

    printf("Note Manager: (write/read/exit)\n");
    while (1) {
        printf("> ");
        scanf("%9s", choice);

        if (strcmp(choice, "write") == 0) {
            FILE *f = fopen("notes.txt", "a");
            if (!f) { printf("Error opening notes file!\n"); return; }
            printf("Enter note (end with ~): ");
            getchar();
            fgets(buffer, sizeof(buffer), stdin);
            fprintf(f, "%s", buffer);
            fclose(f);
            printf("Note saved.\n");
        } else if (strcmp(choice, "read") == 0) {
            FILE *f = fopen("notes.txt", "r");
            if (!f) { printf("No notes found.\n"); continue; }
            printf("Your Notes:\n");
            while (fgets(buffer, sizeof(buffer), f)) {
                printf("- %s", buffer);
            }
            fclose(f);

        } else if (strcmp(choice, "exit") == 0) {
            break;


        } else {
            printf("Unknown option! Use write/read/exit.\n");
        }
    }
}

int main() {
    char input[20];

    while (1) {
        printf("\n> ");
        scanf("%19s", input);

        for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]);
        }

        if (strcmp(input, "neofetch") == 0) {
            printBetterC();
        }
        else if (strcmp(input, "calc") == 0) {
            runCalculator();
        }
        else if (strcmp(input, "time") == 0) {
            showTime();
        }
        else if (strcmp(input, "say") == 0) {
            saySomething();
        }
        else if (strcmp(input, "password") == 0) {
            generatePassword();
        }
        else if (strcmp(input, "sysinfo") == 0) {
            sysInfo();
        }
        else if (strcmp(input, "ip") == 0) {
            showIP();
        }
        else if (strcmp(input, "note") == 0) {
            noteManager();
        }
        else if (strcmp(input, "help") == 0) {
            printf("=== Commands ===\n");
            printf(" calc      - calculator\n");
            printf(" time      - live clock\n");
            printf(" say       - repeat what you type\n");
            printf(" neofetch  - show logo\n");
            printf(" password  - generate random password\n");
            printf(" sysinfo   - show system info\n");
            printf(" ip        - show local IP address\n");
            printf(" note      - simple note manager\n");
            printf(" color      - sets text color to green\n");
            printf(" cquit      - normal text color\n");
            printf(" quit/exit - exit program\n");
        }
        else if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }
        else if (strcmp(input , "color") == 0 || strcmp(input, "COLOR") == 0) {
            setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        }
        else if (strcmp(input, "cquit") == 0 || strcmp(input, "CQUIT") == 0) {
            setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        else {
            printf("Unknown command. Type 'help' for a list.\n");
        }
    }

    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return 0;
}

