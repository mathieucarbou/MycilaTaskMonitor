# MycilaTaskMonitor

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Continuous Integration](https://github.com/mathieucarbou/MycilaTaskMonitor/actions/workflows/ci.yml/badge.svg)](https://github.com/mathieucarbou/MycilaTaskMonitor/actions/workflows/ci.yml)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/mathieucarbou/library/MycilaTaskMonitor.svg)](https://registry.platformio.org/libraries/mathieucarbou/MycilaTaskMonitor)

Arduino / ESP32 library to monitor task priority and stack high watermark

This helps monitor stack sizes and correctly set the stack size of each task.

- Configurable frequency with `MYCILA_TASK_MONITOR_FREQUENCY`
- `loop()` is optional: you can call `toJson()` at any time to get the information
- Configurable warning thresholds with `MYCILA_TASK_MONITOR_STACK_FREE_MIN` and `MYCILA_TASK_MONITOR_STACK_FREE_MAX`: depending on these level, the loop will log as warnings or info.

## Usage

```c++
void setup() {
  Mycila::TaskMonitor.begin(5);
  Mycila::TaskMonitor.addTask("loopTask");
  Mycila::TaskMonitor.addTask("async_tcp");
  Mycila::TaskMonitor.addTask("mqttclient");
  Mycila::TaskMonitor.addTask("jsyTask");
  Mycila::TaskMonitor.addTask("ioTask");
}

void loop() {
  Mycila::TaskMonitor.loop();
  delay(1000);
}
```

outputs:

```
D       588202 loopTask   (1) MONITOR    loopTask   (p=1) 260 bytes
D       588207 loopTask   (1) MONITOR    async_tcp  (p=3) 496 bytes
D       588208 loopTask   (1) MONITOR    mqttclient (p=1) 544 bytes
D       588221 loopTask   (1) MONITOR    jsyTask    (p=1) 296 bytes
D       588222 loopTask   (1) MONITOR    ioTask     (p=1) 464 bytes
```
