/* Logging
 * Copyright (C) 2013 Shanika Kuruppu
 * All rights reserved.

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER>
 * BE LIABLE FOR ANY * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; * LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND * ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT * (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS * SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Logging -- Allows logging using the insertion (`<<`) operator.
 * Author: Shanika Kuruppu
 * Usage: LOG(level) << expr1 << expr2 << ...;
 */

#ifndef INCLUDE_LOG_H
#define INCLUDE_LOG_H

#include <iostream>
#include <stdio.h>
#include <string>

#define DEBUG 0
#define INFO 1
#define WARNING 2
#define CRITICAL 3
#define ERROR 4

#ifndef LOGLEVEL
#define LOGLEVEL WARNING
#endif

class Log {
public:
  bool operator&(std::ostream &stream) {
    stream << std::endl;
    return true;
  }
};

inline std::string log_level_to_str(const int log_level) {
  char buf[12];
  std::string str = "";

  switch (log_level) {
  case DEBUG:
    str = "[DEBUG]";
    break;
  case INFO:
    str = "[INFO]";
    break;
  case WARNING:
    str = "[WARNING]";
    break;
  case ERROR:
    str = "[ERROR]";
    break;
  case CRITICAL:
    str = "[CRITICAL]";
    break;
  default:
    break;
  }

  sprintf(buf, "%-9s ", str.c_str());
  return buf;
}

/* If the minimum log level requirement is satisfied then prints the log
message. This works because the & operator has lower precedence than the
<< operator, therefore the stream output is evaluated before the Log
class is initialised. */
#define LOG(log_level)                                                         \
  log_level >= LOGLEVEL &&Log() & std::cerr << log_level_to_str(log_level)     \
                                            << ": "

#endif
