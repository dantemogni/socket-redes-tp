#include "./../headers/logger.h"

// get timestamp
string Logger::GetTimestamp(){
    time_t now = time(0);
    tm *ltm = localtime(&now);

    return to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday) + " " + to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min);
}

// get file content to string
string Logger::GetLogFileContent(){
    ifstream file(LOG_FILE);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    return content;
}

int Logger::Write(string type, string message) {
    ofstream myfile;
    myfile.open(LOG_FILE, fstream::app);

    string msg = "[" + Logger::GetTimestamp() + "] [" + type + ']' + ' ' + message + '\n';
    
    cout << msg;
    myfile << msg;
    
    myfile.close();

    return EXIT_SUCCESS;
}

int Logger::Info(string message){
    return Logger::Write("INFO", message);
}

int Logger::Debug(string message) {
    return Logger::Write("DEBUG", message);
}

int Logger::Error(string message) {
    return Logger::Write("ERROR", message);
}