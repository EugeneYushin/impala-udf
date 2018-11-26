#ifndef IMPALA_UDF_TIMESTAMP_UDF_H
#define IMPALA_UDF_TIMESTAMP_UDF_H

#include <impala_udf/udf.h>

using namespace impala_udf;

TimestampVal UnixMillisToUtcTimestamp(FunctionContext* context,
      const BigIntVal& unix_time_millis);

#endif
