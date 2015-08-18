//
// In this example the Particle device publishes the voltage and SoC readings every 10 minutes
// and stays in deep sleep mode for the rest of the time
//

#include "PowerShield/PowerShield.h"

PowerShield batteryMonitor;

void setup() {
    Serial.begin(9600); 
    // This essentially starts the I2C bus
    batteryMonitor.begin(); 
    // This sets up the fuel gauge
    batteryMonitor.quickStart();
    // Wait for it to settle down
    delay(500); //delay 0.5 second
}

void loop() { 
    
     // Read the volatge of the LiPo
    float cellVoltage = batteryMonitor.getVCell();
    // Read the State of Charge of the LiPo
    float stateOfCharge = batteryMonitor.getSoC();
    
    //Publish Cell Voltage to cloud
    Spark.publish("ps-voltage", String(cellVoltage));
    
    //Publish State of Charge to Cloud
    Spark.publish("ps-soc", String(stateOfCharge));
    delay(1000); //delay 1 second


}

