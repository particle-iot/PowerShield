# Power Shield

_The Power Shield library provides functions to use the on-board MAX17043 fuel guage via I2C_

## Typical usage

Connect a Photon to a Power Shield with a [3.7V LiPo battery](https://www.sparkfun.com/products/8483) and use the library to get the voltage and state of charge.

```
#include "PowerShield.h"

PowerShield batteryMonitor;

void setup() {
    batteryMonitor.begin(); 
    batteryMonitor.quickStart();
}
  
void loop() {
    delay(5000);

    float cellVoltage = batteryMonitor.getVCell();
    float stateOfCharge = batteryMonitor.getSoC();

    Particle.publish("voltage", String(cellVoltage));
    Particle.publish("soc", String(stateOfCharge));
}
```

## Examples

See [complete example](examples/sawtooth/sawtooth.ino) in the examples directory.

1. [**Read voltage over serial:**](examples/1_Read_voltage_over_serial/1_Read_voltage_over_serial.cpp) In this example the Particle device sends the volatge and SoC readings over serial every 1 second
2. [**Publish voltage readings:**](examples/2_Publish_voltage_readings/2_Publish_voltage_readings.cpp) In this example the Particle device publishes the voltage and SoC readings every 10 minutes and stays in deep sleep mode for the rest of the time

## Reference

### `PowerShield`

`PowerShield batteryMonitor;`

Creates an object to interact with the MAX17043 fuel gauge on the Power Shield.

### `begin`

`batteryMonitor.begin();`

Starts communicating with the fuel gauge. Should normally be called once in `setup`.

### `quickStart`

`batteryMonitor.quickstart();`

Resume state of charge calculations. See Quick-Start in the [MAX17043 datasheet](http://datasheets.maximintegrated.com/en/ds/MAX17043-MAX17044.pdf) for details.

### `getVCell`

`float cellVoltage = batteryMonitor.getVCell();`

Reads the voltage of the single cell battery connected to the Power Shield. The range is 0 V to 5 V.

### `getSoC`


`float stateOfCharge = batteryMonitor.getSoC();`

Reads the state of charge of the single cell battery connected to the Power Shield, from 0% to 100%, so that you know when to send out an alert to replace/charge the battery.

### `getVersion`

`int version = batteryMonitor.getVersion();`

The version of the MAX17043 chip, currently 3.

### `getCompensateValue`

Gets the configuration for battery chemistry. See `CONFIG` in the [MAX17043 datasheet](http://datasheets.maximintegrated.com/en/ds/MAX17043-MAX17044.pdf) for details.

### `getAlertThreshold`

`byte thereshold = batteryMonitor.getAlertThreshold();`

Gets the state of charge threshold (1 to 32%) that will generate a low pulse on pin D3 when the state of charge falls below this level.

The default threshold is 4%.

For the pulse to be generated the ALRT solder bridge needs to be closed on the Power Shield.

To trigger an interrupt on low battery, configure pin D3 for a falling
interrupt. See [the interrupt on low voltage example](examples/3_Interrupt_on_low_voltage/3_Interrupt_on_low_voltage.ino) for details.

### `setAlertThreshold`

`batteryMonitor.setAlertThreshold(threshold);`

Sets the state of charge threshold (1 to 32%) that will generate a pulse on D3.

### `getAlert`

`bool lowBatteryAlert = batteryMonitor.getAlert();`

Returns true when the state of charge is below the alert threshold. Use this if you don't want to use the D3 pin as an low battery interrupt.

Once true, this will stay true, even if the battery is charged, until cleared by software with `clearAlert()`.

### `clearAlert`

`batteryMonitor.clearAlert();`

Clears the low voltage alert so that `getAlert()` returns false.

### `reset`

`batteryMonitor.reset();`

Reset the MAX17043 fuel gauge as if power had been removed.

## Resource Utilization

The Power Shield uses pins D0, D1 (I2C) and D3 (if optional solder bridge is closed).


## References

- [Power Shield Documentation](http://docs.particle.io/photon/shields/#power-shield)
- [MAX17043 datasheet](http://datasheets.maximintegrated.com/en/ds/MAX17043-MAX17044.pdf)

## License
Copyright 2015 Particle

Released under the LGPL license
