//
// In this example the Particle device publishes an event when the
// battery is low
//
// IMPORTANT: The solder bridge ALRT must be closed for this example to work
//

#include "PowerShield.h"

PowerShield batteryMonitor;

// Will be set to true by the interrupt
bool lowBatteryAlert = false;

// This function is called when the alert pin toggles
void lowBatteryInterrupt() {
  // Don't call delay or Particle functions in here. Do something quick
  // like setting a flag and return
  lowBatteryAlert = true;
}

void setup() {
    // This essentially starts the I2C bus
    batteryMonitor.begin(); 
    // This sets up the fuel gauge
    batteryMonitor.quickStart();

    // Configure alert pin for interrupt
    pinMode(D3, INPUT);
    attachInterrupt(D3, lowBatteryInterrupt, FALLING);

    // Alert at a higher level than normal as an example
    batteryMonitor.setAlertThreshold(30);
}

void loop() {
    if (lowBatteryAlert) {
        // Publish a cloud event when the low battery alert occurs
        Particle.publish("ps-low-battery", PRIVATE);
        lowBatteryAlert = false;
    }

    // Publish regular information
    float cellVoltage = batteryMonitor.getVCell();
    float stateOfCharge = batteryMonitor.getSoC();

    Particle.publish("ps-voltage", String(cellVoltage));
    Particle.publish("ps-soc", String(stateOfCharge));

    delay(5000);
}
