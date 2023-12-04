#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <thread>
#include <windows.h>

using namespace std;

void login();
void registration();
void startExam();
void displayInstructions();
void displayQuestion(int questionNumber, const string &question, const string options[]);
char getAnswer();
void displayClock(int remainingTime);

const int totalQuestions = 10;
const int timeLimit = 300; // 5 minutes in seconds

int main()
{

    system("color 2F");
	//textcolor(0);
    int choice;
    do
    {
        cout << "\n\t\t\t\t\t\t\t\tNew user? \n\t\t\t\t\t\t\tPress 1 for registration" << endl;
        cout << "\n\n\t\t\t\t\t\t\t    Registered user? \n\t\t\t\t\t\t\tPress 2 for Sign Up or login" << endl;

        cin >> choice;

        switch (choice)
        {
        case 1:
            registration();
            break;
        case 2:
            login();
            break;

        default:
            cout << "Wrong enter. Please try again." << endl;
        }
    } while (choice != 2); // Continue loop until login is successful

    startExam(); // Start the exam after successful login

    return 0;
}

void displayInstructions()
{
    cout << "\n\n\t\t\t\t\t\t    Northern University Bangladesh" << endl;
    cout << "\n\n\t\t\t\t\t\tWelcome to NUB Online Examination System!" << endl;
    cout << "\n\t\t\tPlease follow the instructions given below." << endl;
    cout << "\t\t\t 1. You have 5 minutes to answer " << totalQuestions << " questions." << endl;
    cout << "\t\t\t 2. You will receive 1 point for each correct answer." << endl;
    cout << "\t\t\t 3. For each wrong answer, 0.25 points will be deducted." << endl;
    cout << "\t\t\t 4. You can only select one option (a, b, c or d) for each question." << endl;
    cout << "\nPress 'S' to start the exam when you are ready." << endl;
}

void displayQuestion(int questionNumber, const string &question, const string options[])
{
    cout << "Q" << questionNumber << ". " << question << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << options[i] << endl;
    }
}

char getAnswer()
{
    char answer;
    cin >> answer;
    return tolower(answer);
}

void displayClock(int remainingTime)
{
    cout << "Time Remaining: " << remainingTime / 60 << " min " << remainingTime % 60 << " sec" << endl;
}

void login()
{
    int count = 0;
    string usernm, sid, nm, id;
    system("CLS");
    cout << "\t\t\t\t\t\t  For Log in: Input Your user Name and ID" << endl;
    cout << "\n\t\t\t\t\t\t\t     Student Name :" << endl;
    cin >> usernm;
    cout << "\n\t\t\t\t\t\t\t      Student ID:" << endl;
    cin >> sid;
    ifstream input("records.txt");

    while (input >> nm >> id)
    {
        if (nm == usernm && id == sid)
        {
            count = 1;
            system("CLS");
        }
    }
    input.close();
    if (count == 1)
    {
        cout << " Welcome " << usernm << ". Your login is successful!" << endl;
    }
    else
    {
        cout << "Wrong Name and Id. Please try again." << endl;
        login();
    }
}

void registration()
{
    string usernm2, sid2;
    system("CLS");
    cout << "\t\t\t\t\t\t\t    Student Name : " << endl;
    cin >> usernm2;
    cout << "\n\t\t\t\t\t\t\t     Student ID : " << endl;
    cin >> sid2;
    ofstream f1("records.txt", ios::app);

    f1 << usernm2 << ' ' << sid2 << endl;
    cout << "\t\t\t\t\t Congratulations. Your Registration is successful!!" << endl;
    cout << "\t\t\t\t\t\t\t  Press 2 for login " << endl;
}

void startExam()
{
    string questions[totalQuestions] =
        {
            "What is the Official Name of Bangladesh?",
            "What is the capital of Bangladesh?",
            "Who is the First President of Bangladesh?",
            "Who is the First Prime Minister of Bangladesh?",
            "Who is the Prime Minister of Bangladesh?",
            "Who is the President of Bangladesh?",
            "Which river is the longest in Bangladesh and forms part of its eastern border?",
            "What is the official language of Bangladesh?",
            "Which of these is a UNESCO World Heritage Site in Bangladesh?",
            "What is the National Animal of Bangladesh?"};

    string options[totalQuestions][4] =
        {
            {"a) Muslim Republic", "b) United States of East Bengal", "c) Republic of Islamic State", "d) People's Republic of Bangladesh"},
            {"a) Dhaka", "b) Kolkata", "c) Khulna", "d) Barisal"},
            {"a) Captain M Monsur Ali", "b) Sayed Nazrul Islam", "c) Bangabandhu Sheikh Mujibur Rahman", "d) Tajuddin Ahmad"},
            {"a) Captain M Monsur Ali", "b) Sayed Nazrul Islam", "c) Bangabandhu Sheikh Mujibur Rahman", "d) Tajuddin Ahmad"},
            {"a) Khaleda Zia", "b) Sheikh Hasina", "c) Bangabandhu", "d) Zillur Rahman"},
            {"a) Mr. Sahabuddin Chuppu", "b) H M Ershad", "c) General Moin", "d) Farsah Uddin"},
            {"a) Ganges", "b) Brahmaputra", "c) Jamuna", "d) Padma"},
            {"a) Urdu", "b) Bengali (Bangla)", "c) English", "d) Hindi"},
            {"a) Cox's Bazar Beach", "b) Sylhet Tea Gardens", "c) Sundarbans Mangrove Forest", "d) Lalbagh Fort"},
            {"a) Bengal Tiger", "b) Asian Elephant", "c) Royal Bengal Tiger", "d) Red Panda"}};

    char answers[totalQuestions] = {'d', 'a', 'c', 'd', 'b', 'a', 'b', 'b', 'c', 'c'};

    int score = 0;
    int wrongAnswers = 0;

    time_t startTime, currentTime;
    time(&startTime);

    char startExam;
    displayInstructions();
    cin >> startExam;

    if (tolower(startExam) != 's')
    {
        cout << "You didn't start the exam. Exiting..." << endl;
        return;
    }

    for (int i = 0; i < totalQuestions; i++)
    {
        system("CLS");
        displayQuestion(i + 1, questions[i], options[i]);

        char userAnswer = getAnswer();

        if (userAnswer == answers[i])
        {
            score++;
        }
        else
        {
            wrongAnswers++;
        }

        time(&currentTime);
        int elapsedSeconds = difftime(currentTime, startTime);

        int remainingTime = timeLimit - elapsedSeconds;

        if (remainingTime <= 0)
        {
            cout << "Time's up! You couldn't answer all questions in time." << endl;
            break;
        }

        displayClock(remainingTime);
        // Wait for 1 second before clearing the screen for the next question
        this_thread::sleep_for(chrono::seconds(1));
        system("CLS");
    }

    float finalScore = score - (0.25 * wrongAnswers);

    system("CLS");

    cout << "Your Score: " << score << " out of " << totalQuestions << endl;
    cout << "Final Score (after deductions): " << finalScore << endl;

    if (finalScore >= (totalQuestions * 0.6))
    {
        cout << "Congratulations, you passed the exam!" << endl;
    }
    else
    {
        cout << "You did not pass the exam. Best of luck for the next time." << endl;
    }
}
