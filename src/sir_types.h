#ifndef SIR_TYPES_H
#define SIR_TYPES_H

#include <QString>

namespace SIR_types {
enum type : int { S, I, R, V, D, total };
enum rate : int { i, r, v, d, n };
enum time : int { intervals, totalTime };
enum types : int { type_type, rate_type, time_type };
static int numTypes = 5;
static int numRates = 4;
static QString toString(type t) {
  switch (t) {
    case S:
      return QString("Susceptible");
    case I:
      return QString("Infected");
    case R:
      return QString("Recovered");
    case V:
      return QString("Vaccinated");
    case D:
      return QString("Dead");
    case total:
      return QString("Total population");
    default:
      break;
  }
}
static QString toString(rate t) {
  switch (t) {
    case i:
      return QString("Infection rate");
    case r:
      return QString("Recovery rate");
    case v:
      return QString("Vaccination rate");
    case d:
      return QString("Death rate");
    case n:
      return QString("No immunity rate");
    default:
      break;
  }
}

static QString toString(time t) {
  switch (t) {
    case intervals:
      return QString("Number of intervals");
      break;
    case totalTime:
      return QString("Total time");
      break;
  }
}
}  // namespace SIR_types

#endif  // SIR_TYPES_H
