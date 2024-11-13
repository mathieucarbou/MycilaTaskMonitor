// SPDX-License-Identifier: MIT
/*
 * Copyright (C) 2023-2024 Mathieu Carbou
 */
#pragma once

#include <algorithm>
#include <vector>

#ifdef MYCILA_JSON_SUPPORT
#include <ArduinoJson.h>
#endif

#define MYCILA_TASK_MONITOR_VERSION "3.0.2"
#define MYCILA_TASK_MONITOR_VERSION_MAJOR 3
#define MYCILA_TASK_MONITOR_VERSION_MINOR 0
#define MYCILA_TASK_MONITOR_VERSION_REVISION 2

#ifndef MYCILA_TASK_MONITOR_STACK_FREE_MIN
#define MYCILA_TASK_MONITOR_STACK_FREE_MIN 256
#endif

namespace Mycila {
  class TaskMonitorClass {
    public:
      void begin(const size_t expectedTaskCount = 0);
      void end();

      void addTask(const char* name) { _taskNames.push_back(name); }
      void removeTask(const char* name) { _taskNames.erase(std::remove(_taskNames.begin(), _taskNames.end(), name), _taskNames.end()); }

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
