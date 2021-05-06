#include "Adafruit_VCNL4040.h"
#include "esphome.h"
#include "Wire.h"

Adafruit_VCNL4040 vcnl4040 = Adafruit_VCNL4040();
using namespace esphome;

class MyVCNL4040 : public PollingComponent, public Sensor {

public:

Sensor *prox_sensor = new Sensor();
Sensor *lux_sensor = new Sensor();
Sensor *rawLight_sensor = new Sensor();
MyVCNL4040() : PollingComponent(1000) {}
float get_setup_priority() const override { return esphome::setup_priority::BUS; }

void setup() override {

  if (!vcnl4040.begin()) {
    while (1);
  }
}
  
void update() override {
    int prox = vcnl4040.getProximity();
    prox_sensor->publish_state(prox);

    int lux = vcnl4040.getLux();
    lux_sensor->publish_state(lux);

    int raw = vcnl4040.getWhiteLight();
    rawLight_sensor->publish_state(raw);
}
};