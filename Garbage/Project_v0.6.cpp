#define _CRT_SECURE_NO_WARNINGS
// 설계 의도: 각 로거의 기능은 동일하다.
//          부모 클래스를 통해 공통의 기능을 캡슐화한다.
//          연산자 오버로딩(<<)을 통해 출력을 수행한다.
//          각 로그 레벨에 따라 클래스를 통해 이름 받아 오는 것이 아니라
//          부모 클래스를 통해 자식 클래스의 실제 타입을 얻어오고 싶다.

#include <string>
#include <iostream>
#include <time.h>
#include <map>
#include <fstream>
#include <stdarg.h>

enum Level {
  INFO,
  // ...
};

class Logger {
public:
  virtual ~Logger() {}

  Logger(const std::string& f) : filename(f) {
    
  }

  void write(const std::string& funcname, int line, const std::string& message) {
	  std::ofstream out;
	  std::string fn = filename + ".txt";
	  out.open(fn, std::ios::out);
	  std::string header = getLogLevel() + " " + getTimestamp() + "]";
	  out << header << message << std::endl;
	  out.close();
  }
  virtual std::string getLogLevel() const = 0;
  virtual std::string getFilename() const = 0;

  static Logger& getLogger(Level level) {
    return *loggers[level];
  }

protected:
  std::string getTimestamp() const {
    time_t current = time(nullptr);
    struct tm* t = localtime(&current);

    char buf[64];
    sprintf(buf, "%d.%d.%d %d:%d:%d", 
      t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    
    return std::string(buf);
  }

  static void registLogger(Level level, Logger* logger) {
    loggers[INFO] = logger;
  }

  

private:
  std::string filename;
  static std::map<Level, Logger*> loggers;
};


// 소스 파일
std::map<Level, Logger*> Logger::loggers;


class InfoLogger : public Logger {
public:
  InfoLogger() : Logger(getFilename()) {
      Logger::registLogger(INFO, this);
  }

  std::string getLogLevel() const override {
    return "INFO";
  }

  std::string getFilename() const override {

	std::string s = getLogLevel() + "_" + getTimestamp()+".log";
    return s;
  }

  static InfoLogger& getInstance() {
    static InfoLogger instance;
    return instance;
  }

  // 복사 / 대입 금지  싱글톤 추가 필요
private:

};

#define LOG(level) Logger::getLogger(level)

int main() {

	LOG(INFO).write("1111111");
}
