#include"logging.h"

#define LOG(level) (Logger::getLogger(level).setCurrentContext(__FILE__,__func__, __LINE__))

#define INITIALIZE_LOGGERS()				\
  do {										\
        InfoLogger::getInstance();			\
		WarningLogger::getInstance();		\
		ErrorLogger::getInstance();			\
		FatalLogger::getInstance();			\
  } while (0)								\

std::map<Level, Logger*> Logger::loggers;

void Logger::write(const char* fmt, ...) {
	fs::create_directory(getDay());
	std::ofstream out;
	std::string file;
	int i = 0;
	std::string temp;
	while (1) {
		temp = getDay() + "/" + filename + "_(" + std::to_string(i) + ").log";
		if (getFileSize(temp) < limit)	break;
		else	i++;
	}
	file = temp;
	out.open(file, std::ios::app);
	if (!out.is_open()) {
		std::cout << "로그 저장이 불가능합니다.";
	}
	std::string tempinfo = getLogLevel() + "_" + location + getTimestamp();
	va_list start;
	va_start(start, fmt);
	char message[128];
	vsprintf(message, fmt, start);
	std::string s(message);
	out << tempinfo << " " << message << std::endl;
	out.close();
}
void Logger::write_each(const char* fmt, ...) {
	std::string folder(getDay());
	std::string each = "//" + getLogLevel();
	folder.append(each);
	fs::create_directory(getDay());
	fs::create_directory(folder);
	std::ofstream out;
	std::string file;
	int i = 0;
	std::string temp;
	while (1) {
		temp = folder + "/" + filename + "_(" + std::to_string(i) + ").log";
		if (getFileSize(temp) < limit)	break;
		else	i++;
	}
	file = temp;
	out.open(file, std::ios::app);
	if (!out.is_open()) {
		std::cout << "로그 저장이 불가능합니다.";
	}
	std::string tempinfo = getLogLevel() + "_" + location + getTimestamp();
	va_list start;
	va_start(start, fmt);
	char message[128];
	vsprintf(message, fmt, start);
	std::string s(message);
	out << tempinfo << " " << message << std::endl;
	out.close();
}

Logger& Logger::getLogger(Level level) {
	return *loggers[level];
}

Logger& Logger::setCurrentContext(const std::string& file, const std::string& func, int l) {	// 위치 정보
	location = file + " " + func + "_" + "line:" + std::to_string(l) + "] ";
	cnt++;
	return *this;
}
int Logger::getFileSize(std::string s) {					// 파일 크기
	std::ifstream in_file(s, std::ios::binary);
	in_file.seekg(0, std::ios::end);
	return in_file.tellg();
}

void Logger::show(const std::string& message) {
	std::cout << this->getLogLevel() << location << getTimestamp() << "] " << message << std::endl;
}
void Logger::showLogToday() {
	std::string s = getDay();
	fs::path p(s);
	for (const fs::directory_entry& entry :
		fs::directory_iterator(p)) {
		std::cout << entry.path() << std::endl;
	}
}
void Logger::showLogOneday() {
	std::cout << "날짜를 입력하세요(yyyy.mm.dd): ";
	std::string p;
	std::cin >> p;
	if (!std::experimental::filesystem::exists(p))
		std::cout << "폴더가 존재하지 않습니다!" << std::endl;
	for (const fs::directory_entry& entry :
		fs::directory_iterator(p)) {
		std::cout << entry.path() << std::endl;
	}
}

std::string Logger::getDay() const {
	time_t current = time(nullptr);
	struct tm* t = localtime(&current);
	std::string day = std::to_string(t->tm_year + 1900) + "." +
		std::to_string(t->tm_mon + 1) + "." +
		std::to_string(t->tm_mday);
	return day;
}
std::string Logger::getTime() const {
	time_t current = time(nullptr);
	struct tm* t = localtime(&current);
	std::string ampm;
	if (t->tm_hour < 12) ampm = "a.m";
	else ampm = "p.m";
	std::string time = getDay() + "_" +
		std::to_string(t->tm_hour) + ampm;
	return time;
}
std::string Logger::getTimestamp() const {
	time_t current = time(nullptr);
	struct tm* t = localtime(&current);
	std::string time = getTime() + " " + std::to_string(t->tm_min) + ":" + std::to_string(t->tm_sec);
	return time;
}
void Logger::registLogger(Level level, Logger* logger) {
	loggers[level] = logger;
}
std::string InfoLogger::getLogLevel() const {
	return "INFO";
}
std::string InfoLogger::getFilename() const {
	std::string name;
	name = "INFO_" + getTime();
	return name;
}
InfoLogger& InfoLogger::getInstance() {
	static InfoLogger instance;
	return instance;
}

std::string WarningLogger::getLogLevel() const {
	return "WARNING";
}
std::string WarningLogger::getFilename() const {
	std::string name;
	name = "WARNING_" + getTime();
	return name;
}
WarningLogger& WarningLogger::getInstance() {
	static WarningLogger instance;
	return instance;
}

std::string ErrorLogger::getLogLevel() const {
	return "ERROR";
}
std::string ErrorLogger::getFilename() const {
	std::string name;
	name = "ERROR_" + getTime();
	return name;
}
ErrorLogger& ErrorLogger::getInstance() {
	static ErrorLogger instance;
	return instance;
}

std::string FatalLogger::getLogLevel() const {
	return "FATAL";
}
std::string FatalLogger::getFilename() const {
	std::string fname;
	fname = "FATAL_" + getTime();
	return fname;
}
FatalLogger& FatalLogger::getInstance() {
	static FatalLogger instance;
	return instance;
}

int main() {
	INITIALIZE_LOGGERS();
	int n = 10;	char c = 'A';
	LOG(INFO).write("Project Presentation");
	LOG(INFO).write_each("Project Presentation");
	LOG(WARNING).write("Project Presentation");
	LOG(WARNING).write_each("Project Presentation");
	LOG(ERROR).write("Project Presentation");
	LOG(ERROR).write_each("Project Presentation");
	LOG(FATAL).write("Project Presentation");
	LOG(FATAL).write_each("Project Presentation");
	LOG(INFO).write("Hello, World! - %d %c", n, c);
	LOG(INFO).showLogToday();
	LOG(INFO).showLogOneday();
	LOG(INFO).write_each("ASDFSDF");
}