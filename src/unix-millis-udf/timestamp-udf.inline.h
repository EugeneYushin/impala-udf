#ifndef IMPALA_UDF_TIMESTAMP_UDF_INLINE_H
#define IMPALA_UDF_TIMESTAMP_UDF_INLINE_H

#include <impala_udf/udf.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#define NANOS_PER_SEC  1000000000LL
#define MILLIS_PER_SEC 1000LL

using namespace impala_udf;

template <int64_t GRANULARITY>
inline static int64_t SplitTime(int64_t* ticks) {
  int64_t result = *ticks / GRANULARITY;
  *ticks %= GRANULARITY;
  if (*ticks < 0) {
    result--;
    *ticks += GRANULARITY;
  }
  return result;
}

template <int32_t TICKS_PER_SEC>
inline TimestampVal UtcFromUnixTimeTicks(int64_t unix_time_ticks) {
  const boost::gregorian::date EPOCH = boost::gregorian::date(1970,1,1);

  int64_t days = SplitTime<(uint64_t)TICKS_PER_SEC*24*60*60>(&unix_time_ticks);
  boost::gregorian::date date_from_epoch = EPOCH + boost::gregorian::date_duration(days);
  uint32_t days_from_epoch = date_from_epoch.day_number();

  int64_t nanos = unix_time_ticks*(NANOS_PER_SEC/TICKS_PER_SEC);

  return TimestampVal(days_from_epoch, nanos);
}

#endif
