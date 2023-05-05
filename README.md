
# Orion BMS 2

A battery management system (BMS) is any electronic system that manages a rechargeable battery, such as by protecting the battery from operating outside its safe operating area, monitoring its state, calculating secondary data, reporting that data, controlling its environment, balancing it.


## Documentation

[Wiring and Installation Manual](https://www.orionbms.com/manuals/pdf/orionbms2_wiring_manual.pdf)

[Operation Manual](https://www.orionbms.com/manuals/pdf/orionbms2_operational_manual.pdf)

[Utility Manual](https://www.orionbms.com/manuals/pdf/orionbms2_operational_manual.pdf)





## Installation

1)Install the utility on Windows
https://www.orionbms.com/downloads/orionbms2_utility_stable.exe

2)Install Arduino IDE

3)Install the following libraries:
    
a)arduino-mcp2515 (https://github.com/autowp/arduino-mcp2515/archive/master.zip)

b)mcp-can.h (https://downloads.arduino.cc/libraries/github.com/coryjfowler/mcp_can-1.5.0.zip)

4)In the arduino IDE, go to Sketch -> Include Library -> Add .ZIP Library and add the .zip files for both the libararies you just downloaded.
## LED Status

Continuous RED Light- BMS OK

Flashing RED Light- Fault in wiring (**TURN OFF THE BMS!!**)
## Wiring

For testing the BMS connect it to the charger first instead of HV

1)Connect the **Ready Power** and **Ground** of BMS to positive and negative terminals of charger respectively

2)Connect **Always On Power** and **Charge Power** to each other via a fuse

3)Attach a wire to the **Ground Lug** and join it with **Ground** of BMS,i.e.both of the wires are connected to the negative terminal of charger

//ADD IMAGE
## CANBUS Settings

How to edit canbus messages-https://www.orionbms.com/downloads/misc/editing_canbus_messages.pdf

//ADD IMAGE

NOTE-

1)Scale the parameters in your arduino code and not in the utility

2)For parameters with lenth of 2 bytes (eg-Pack Current, Pack Inst. Voltage,etc) data from both the bytes need to be joined first and then scaled.

3)You can see the **Scalling** value of parameters from the following pdf https://www.orionbms.com/downloads/misc/orionbms_obd2_pids.pdf
## Connections to access utility

1)Connect the BMS to laptop using CAN Adapter,which is attached to the CAN 1 wires

//ADD IMAGE

2)Click on **Connect to BMS option**

3)Click on **Connect**

//ADD IMAGE

4)

NOTE-

1)You can view the incoming data by clicking on **Live CANBUS Traffic**

2)Click on **Send Profile Changes To BMS** only after making proper changes to CANBUS settings






## Connections to Arduino

1)Connect the CAN2 wires, CAN2_H and CAN2_L to MCP2515 module

2)Connect the MCP2515 to Arduino UNO using the following connections:

//ADD IMAGE
