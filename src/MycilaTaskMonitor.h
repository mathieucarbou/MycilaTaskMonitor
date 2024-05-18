// SPDX-License-Identifier: MIT
/*
 * Copyright (C) 2023-2024 Mathieu Carbou and others
 */
#pragma once

#include <vector>
#include <algorithm>

#ifdef MYCILA_JSON_SUPPORT
#include <ArduinoJson.h>
#endif

#define MYCILA_TASK_MONITOR_VERSION "3.0.0"
#define MYCILA_TASK_MONITOR_VERSION_MAJOR 3
#define MYCILA_TASK_MONITOR_VERSION_MINOR 0
#define MYCILA_TASK_MONITOR_VERSION_REVISION 0

#ifndef MYCILA_TASK_MONITOR_STACK_FREE_MIN
#define MYCILA_TASK_MONITOR_STACK_FREE_MIN 256
#endif

#ifndef MYCILA_TASK_MONITOR_STACK_FREE_MAX
#define MYCILA_TASK_MONITOR_STACK_FREE_MAX 1024
#endif

namespace Mycila {
  class TaskMonitorClass {
    public:
      void begin(const size_t expectedTaskCount = 0);
      void end();

      void addTask(const char* name) { _taskNames.push_back(name); }
      void removeTask(const char* name) {
        auto it = std::find(_taskNames.begin(), _taskNames.end(), name);
        if (it != _taskNames.end())
          _taskNames.erase(it);
      }

      void log();

#ifdef MYCILA_JSON_SUPPORT
      void toJson(const JsonObject& root) const;
#endif

    private:
      bool _enabled = false;
      std::vector<const char*> _taskNames;
  };

  extern TaskMonitorClass TaskMonitor;
} // namespace Mycila
