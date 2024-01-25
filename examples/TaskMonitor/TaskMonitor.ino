#define MYCILA_LOGGER_CUSTOM_LEVEL

#include <MycilaLogger.h>
#include <MycilaTaskMonitor.h>

uint8_t Mycila::LoggerClass::getLevel() const { return ARDUHAL_LOG_LEVEL_DEBUG; }

void _task1(void* params) {
  while (true) {
    delay(2000);
  }
}

void _task2(void* params) {
  while (true) {
    delay(2000);
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial)
    continue;

  Mycila::Logger.forwardTo(&Serial);

  Mycila::TaskMonitor.begin(3);
  Mycila::TaskMonitor.addTask("loopTask");
  Mycila::TaskMonitor.addTask("task1");
  Mycila::TaskMonitor.addTask("task2");

  xTaskCreateUniversal(_task1, "task1", 1024, nullptr, 1, nullptr, 1);
  xTaskCreateUniversal(_task2, "task2", 1024, nullptr, 1, nullptr, 1);
}

void loop() {
  Mycila::TaskMonitor.loop();
}
