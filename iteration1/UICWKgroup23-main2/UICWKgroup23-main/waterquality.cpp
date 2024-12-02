#include <stdexcept>
#include <sstream>
#include "waterquality.hpp"

using namespace std;


waterQuality::waterQuality(const string& id, 
                          const string& samplingPoint,
                          const string& samplingPointNotation,
                          const string& samplingPointLabel,
                          const string& sampleDateTime,
                          const string& determinandLabel,
                          const string& determinandDefinition,
                          const string& determinandNotation,
                          const string& resultQualifier,
                          //double result,
                          const string& result,
                          const string& resultInterpretation,
                          const string& unit,
                          const string& materialType,
                          //bool isComplianceSample,
                          const string& isComplianceSample,
                          const string& purpose,
                          //int easting,
                          //int northing,
                          const string& easting,
                          const string& northing):
    id(id),
    samplingPoint(samplingPoint),
    samplingPointNotation(samplingPointNotation),
    samplingPointLabel(samplingPointLabel),
    sampleDateTime(sampleDateTime),
    determinandLabel(determinandLabel),
    determinandDefinition(determinandDefinition),
    determinandNotation(determinandNotation),
    resultQualifier(resultQualifier),
    result(result),
    resultInterpretation(resultInterpretation),
    unit(unit),
    materialType(materialType),
    isComplianceSample(isComplianceSample),
    purpose(purpose),
    easting(easting),
    northing(northing)
{/*
    ostringstream error;

  if (latitude < MIN_LATITUDE or latitude > MAX_LATITUDE) {
    error << "Invalid latitude: " << latitude;
    throw out_of_range(error.str());
  }

  if (longitude < MIN_LONGITUDE or longitude > MAX_LONGITUDE) {
    error << "Invalid longitude: " << longitude;
    throw out_of_range(error.str());
  }

  if (depth < 0.0) {
    error << "Invalid depth: " << depth;
    throw out_of_range(error.str());
  }

  if (magnitude < 0.0) {
    error << "Invalid magnitude: " << magnitude;
    throw out_of_range(error.str());
  }
*/}


ostream& operator<<(ostream& out, const waterQuality& waterQuality)
{
  return out << "ID: " << waterQuality.getId()
               << "\nLocation: " << waterQuality.getSamplingPointLabel()
               << "\nDateTime: " << waterQuality.getSampleDateTime()
               << "\nPollutant: " << waterQuality.getDeterminandLabel()
               << " (" << waterQuality.getDeterminandDefinition() << ")"
               << "\nResult: " << waterQuality.getResultQualifier() << waterQuality.getResult() 
               << " " << waterQuality.getUnit()
               << "\nCoordinates: " << waterQuality.getEasting() << "E, " 
               << waterQuality.getNorthing() << "N" << endl;
}
