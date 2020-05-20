#ifndef SIR_TYPES_H
#define SIR_TYPES_H

#include <QString>

namespace SIR_types {
    enum type : int {S,I,R,V,D,TOTAL};
    enum rate : int {i,r,v,d};
    enum time : int {intervals,total};
    enum types : int {type_type, rate_type, time_type};
    static int numTypes = 5;
    static int numRates = 4;
    static QString toString(type t){
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
            default:
                break;
            }
        }
    static QString toString(rate t){
        switch (t) {
            case i:
                return QString("Infection rate");
            case r:
                return QString("Recovery rate");
            case v:
                return QString("Vaccination rate");
            case d:
                return QString("Death rate");

            default:
                break;
        }
    }
}

#endif // SIR_TYPES_H
