// SPDX-License-Identifier: MIT
/*
 * Copyright (C) 2023-2025 Mathieu Carbou
 */
#pragma once

#include <algorithm>
#include <vector>

#ifdef MYCILA_JSON_SUPPORT
  #include <ArduinoJson.h>
#endif

#define MYCILA_TASK_MONITOR_VERSION          "4.0.0"
#define MYCILA_TASK_MONITOR_VERSION_MAJOR    4
#define MYCILA_TASK_MONITOR_VERSION_MINOR    0
#define MYCILA_TASK_MONITOR_VERSION_REVISION 0

#ifndef MYCILA_TASK_MONITOR_STACK_FREE_MIN
  #define MYCILA_TASK_MONITOR_STACK_FREE_MIN 256
#endif

namespace Mycila {
  class TaskMonitorClass {
    public:
      void addTask(const char* name) { _taskNames.push_back(name); }
      void removeTask(const char* name) { _taskNames.erase(std::remove(_taskNames.begin(), _taskNames.end(), name), _taskNames.end()); }
      void clear() { _taskNames.clear(); }

      void setEnabled(bool enabled) { _enabled = enabled; }

      void log();

#ifdef MYCILA_JSON_SUPPORT
      void toJson(const JsonObject& root) const;
#endif

    private:
      bool _enabled = true;
      std::vector<const char*> _taskNames;
  };

  extern TaskMonitorClass TaskMonitor;
} // namespace Mycila
