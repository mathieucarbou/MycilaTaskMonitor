#include <Arduino.h>
#include <MycilaTaskMonitor.h>

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

  Mycila::TaskMonitor.addTask("loopTask");
  Mycila::TaskMonitor.addTask("task1");
  Mycila::TaskMonitor.addTask("task2");

  xTaskCreateUniversal(_task1, "task1", 1024, nullptr, 1, nullptr, 1);
  xTaskCreateUniversal(_task2, "task2", 1024, nullptr, 1, nullptr, 1);
}

void loop() {
  Mycila::TaskMonitor.log();
  delay(2000);
}
