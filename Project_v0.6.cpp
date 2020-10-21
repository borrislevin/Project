#include"logging.h"


int main() {
	INITIALIZE_LOGGERS();
	LOG(INFO).write("1111111");
	LOG(WARNING).write("22222");
	LOG(ERROR).write("33333");
	LOG(FATAL).write("4444");
}