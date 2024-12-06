#pragma once

#include <string>
#include <iostream>

class waterQuality
{
  public:
    waterQuality(const std::string&,
                 const std::string&,
                 const std::string&,
                 const std::string&,
                 const std::string&,
                 const std::string&,
                 const std::string&,
                 const std::string&,
                 const std::string&,
                 //double,
                 const std::string&,
                 const std::string&,
                 const std::string&,
                 const std::string&,
                 //bool,
                 const std::string&,
                 const std::string&,
                 //int,
                 //int
                 const std::string&,
                 const std::string&
                 );
    
    std::string getId() const { return id; }
    std::string getSamplingPoint() const { return samplingPoint; }
    std::string getSamplingPointNotation() const { return samplingPointNotation; }
    std::string getSamplingPointLabel() const { return samplingPointLabel; }
    std::string getSampleDateTime() const { return sampleDateTime; }
    std::string getDeterminandLabel() const { return determinandLabel; }
    std::string getDeterminandDefinition() const { return determinandDefinition; }
    std::string getDeterminandNotation() const { return determinandNotation; }
    std::string getResultQualifier() const { return resultQualifier; }
    double getResult() const { return result; }
    //std::string getResult() const { return result; }
    std::string getResultInterpretation() const { return resultInterpretation; }
    std::string getUnit() const { return unit; }
    std::string getMaterialType() const { return materialType; }
    //bool getIsComplianceSample() const { return isComplianceSample; }
    std::string getIsComplianceSample() const { return isComplianceSample; }
    std::string getPurpose() const { return purpose; }
    int getEasting() const { return easting; }
    int getNorthing() const { return northing; }
    //std::string getEasting() const { return easting; }
    //std::string getNorthing() const { return northing; }

  private:
    std::string id;
    std::string samplingPoint;
    std::string samplingPointNotation;
    std::string samplingPointLabel;
    std::string sampleDateTime;
    std::string determinandLabel;
    std::string determinandDefinition;
    std::string determinandNotation;
    std::string resultQualifier;
    double result;
    //std::string result;
    std::string resultInterpretation;
    std::string unit;
    std::string materialType;
    //bool isComplianceSample;
    std::string isComplianceSample;
    std::string purpose;
    int easting; 
    int northing;
    //std::string easting;
    //std::string northing;
};

std::ostream& operator << (std::ostream&, const waterQuality&);