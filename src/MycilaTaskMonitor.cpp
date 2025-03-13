// SPDX-License-Identifier: MIT
/*
 * Copyright (C) 2023-2025 Mathieu Carbou
 */
#include <MycilaTaskMonitor.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#ifdef MYCILA_LOGGER_SUPPORT
  #include <MycilaLogger.h>
extern Mycila::Logger logger;
  #define LOGD(tag, format, ...) logger.debug(tag, format, ##__VA_ARGS__)
  #define LOGI(tag, format, ...) logger.info(tag, format, ##__VA_ARGS__)
  #define LOGW(tag, format, ...) logger.warn(tag, format, ##__VA_ARGS__)
  #define LOGE(tag, format, ...) logger.error(tag, format, ##__VA_ARGS__)
#else
  #define LOGD(tag, format, ...) ESP_LOGD(tag, format, ##__VA_ARGS__)
  #define LOGI(tag, format, ...) ESP_LOGI(tag, format, ##__VA_ARGS__)
  #define LOGW(tag, format, ...) ESP_LOGW(tag, format, ##__VA_ARGS__)
  #define LOGE(tag, format, ...) ESP_LOGE(tag, format, ##__VA_ARGS__)
#endif

#include <esp32-hal-log.h>

#define TAG "MONITOR"

void Mycila::TaskMonitorClass::log() {
  if (_enabled && _taskNames.size() > 0) {
    for (const char* name : _taskNames) {
      const TaskHandle_t handle = xTaskGetHandle(name);
      if (handle) {
        const UBaseType_t size = uxTaskGetStackHighWaterMark(handle);
        if (size < MYCILA_TASK_MONITOR_STACK_FREE_MIN)
          LOGW(TAG, "%-10.10s (p=%u) %u bytes", name, uxTaskPriorityGet(handle), size);
        else
          LOGI(TAG, "%-10.10s (p=%u) %u bytes", name, uxTaskPriorityGet(handle), size);
      } else {
        LOGE(TAG, "%-10.10s Handle not found", name);
      }
    }
  }
}

#ifdef MYCILA_JSON_SUPPORT
void Mycila::TaskMonitorClass::toJson(const JsonObject& root) const {
  for (const char* name : _taskNames) {
    TaskHandle_t handle = xTaskGetHandle(name);
    if (handle) {
      root[name]["stackHighWaterMark"] = uxTaskGetStackHighWaterMark(handle);
      root[name]["priority"] = uxTaskPriorityGet(handle);
    }
  }
}
#endif

namespace Mycila {
  TaskMonitorClass TaskMonitor;
} // namespace Mycila
