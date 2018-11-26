#include "timestamp-udf.h"
#include "timestamp-udf.inline.h"

TimestampVal UnixMillisToUtcTimestamp(FunctionContext* context,
    const BigIntVal& unix_time_millis) {
  if (unix_time_millis.is_null) return TimestampVal::null();
  return UtcFromUnixTimeTicks<MILLIS_PER_SEC>(unix_time_millis.val);
}
