#ifndef GUTIL_SYSLOG_SINK_H_
#define GUTIL_SYSLOG_SINK_H_

#include "absl/log/log_entry.h"
#include "absl/log/log_sink.h"

namespace gutil {

// When constructed SyslogSink will automatically register an Abseil LogSink and
// begin forwarding all LOG() messages to syslog. In the dtor we unregister the
// LogSink so the SyslogSink should outlive the program. These messages are
// treated as user-level (i.e. a LOG_USER facility), and serverities are mapped
// as follows:
//   LOG(INFO)    -> LOG_INFO
//   LOG(WARNING) -> LOG_WARNING
//   LOG(ERROR)   -> LOG_ERR
//   LOG(FATAL)   -> LOG_EMERG
//
// The syslog message will be formatted similar to the default Abseil Log
// message except with a microsecond timestamp.
class SyslogSink final : public absl::LogSink {
 public:
  SyslogSink(const char* process_name);
  ~SyslogSink();

  void Send(const absl::LogEntry& entry) override;
};

}  // namespace gutil

#endif  // GUTIL_SYSLOG_SINK_H_
