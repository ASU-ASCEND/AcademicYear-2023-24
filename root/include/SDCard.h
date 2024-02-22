#ifndef SDCARD_H
#define SDCARD_H

class SDCard {
private:
  //Name for the sensor to be used in CSV header and console
  static constexpr const char* nameCompiled = "SDCard";
public:
  const std::string& getSDCardName() const;
};

#endif
