#include <SPI.h>
#include <DW1000Ng.hpp>

#if defined(ESP8266)
const uint8_t PIN_SS = 15; // spi select pin
#else
const uint8_t PIN_SS = SS; // spi select pin
#endif

String message;

device_configuration_t DEFAULT_CONFIG = {
  false,
  true,
  true,
  true,
  false,
  SFDMode::STANDARD_SFD,
  Channel::CHANNEL_5,
  DataRate::RATE_850KBPS,
  PulseFrequency::FREQ_16MHZ,
  PreambleLength::LEN_256,
  PreambleCode::CODE_3
};

void setup() {
  Serial.begin(9600);
  Serial.println(F("### DW1000Ng-arduino-receiver-test ###"));
  DW1000Ng::initializeNoInterrupt(PIN_SS);
  Serial.println(F("DW1000Ng initialized ..."));

  DW1000Ng::applyConfiguration(DEFAULT_CONFIG);

  DW1000Ng::setDeviceAddress(6);
  DW1000Ng::setNetworkId(10);

  DW1000Ng::setAntennaDelay(16436);
  Serial.println(F("Committed configuration ..."));
  char msg[128];
  DW1000Ng::getPrintableDeviceIdentifier(msg);
  Serial.print("Device ID: "); Serial.println(msg);
  DW1000Ng::getPrintableExtendedUniqueIdentifier(msg);
  Serial.print("Unique ID: "); Serial.println(msg);
  DW1000Ng::getPrintableNetworkIdAndShortAddress(msg);
  Serial.print("Network ID & Device Address: "); Serial.println(msg);
  DW1000Ng::getPrintableDeviceMode(msg);
  Serial.print("Device mode: "); Serial.println(msg);
}

void loop() {
  DW1000Ng::startReceive();
  while (!DW1000Ng::isReceiveDone()) {
#if defined(ESP8266)
    yield();
#endif
  }
  DW1000Ng::clearReceiveStatus();
  DW1000Ng::getReceivedData(message);
  Serial.print("Data is ... "); Serial.println(message);
  Serial.print("RX power is [dBm] ... "); Serial.println(DW1000Ng::getReceivePower());
  Serial.print("Signal quality is ... "); Serial.println(DW1000Ng::getReceiveQuality());
}
