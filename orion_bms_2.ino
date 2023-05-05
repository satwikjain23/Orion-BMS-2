#include <mcp_can.h>
#include <mcp_can_dfs.h>

#include <SPI.h>
#include "mcp_can.h"

const int SPI_CS_PIN = 10;              // CANBed V1
unsigned char len = 8;
unsigned char buf[8] = {0};
long unsigned int rxId;
char msgString[128];

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin


void decToBinary(int decimalNum, int binaryArray[], int arraySize) {
  // Initialize binary array to all zeros
  for (int i = 0; i < arraySize; i++) {
    binaryArray[i] = 0;
  }

  // Convert decimal number to binary and store in array
  int i = 0;
  while (decimalNum > 0 && i < arraySize) {
    binaryArray[i] = decimalNum % 2;
    decimalNum /= 2;
    i++;
  }
}

int hexToDec(String hexString) {
  int decimalValue = 0;
  int len = hexString.length();
  for (int i = 0; i < len; i++) {
    char c = hexString.charAt(i);
    int digit;
    if (isDigit(c)) {
      digit = c - '0';
    } else {
      c = toupper(c);
      digit = c - 'A' + 10;
    }
    decimalValue += digit * pow(16, len - i - 1);
  }
  return decimalValue;
}

String decToHex(int decimalValue) {
  String hexString = "";
  while (decimalValue > 0) {
    int remainder = decimalValue % 16;
    char hexDigit;
    if (remainder < 10) {
      hexDigit = '0' + remainder;
    } else {
      hexDigit = 'A' + remainder - 10;
    }
    hexString = String(hexDigit) + hexString;
    decimalValue /= 16;
  }
  return hexString;
}



void setup()
{
  Serial.begin(9600);
  while (!Serial);

  if (CAN_OK != CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ))    
  {
    Serial.println("CAN BUS FAIL!");
    while (1) delay(100);
  }
  else {
    Serial.println("CAN BUS OK!");
    delay(500);
  }
  CAN.setMode(MCP_NORMAL);
  pinMode(2, INPUT);
}


void loop()
{
    if (!digitalRead(2)){
    CAN.readMsgBuf(&rxId, &len, buf);    // read data,  len: data length, buf: data buf
    }

    Serial.println("-----------------------------");
    Serial.print("Get data from ID: ");
    Serial.println(rxId);

    for (int i = 0; i < len; i++) // print the data
    {
      Serial.print(buf[i],HEX);   
      Serial.print("\t");
    }
    
    if(rxId==2147485360){
      //CURRENT
      String c1 = decToHex(buf[0]);
      String c2 = decToHex(buf[1]);
      String c = c1+c2;
      int pack_current=(hexToDec(c))/10;
      Serial.println();
      Serial.println("Pack Current-");
      Serial.println(pack_current);

      //VOLTAGE
      String v1 = decToHex(buf[2]);
      String v2 = decToHex(buf[3]);
      String v = v1+v2;
      int pack_inst_voltage=(hexToDec(v))/10;
      Serial.print("Pack Inst. Voltage-");
      Serial.println(pack_inst_voltage);

      //STATE OF CHARGE      
      Serial.print("State Of Charge-");
      Serial.println(buf[4]/2);

      //TEMPERATURE
      Serial.print("High Temperature-");
      Serial.println(buf[5]);
      Serial.print("Low Temperature");
      Serial.println(buf[6]);

    }
    
    
    if (rxId==2147485361){
      //DTC FLAGS #1
      int a=(buf[0]);
      int flag1[8];
      decToBinary(a, flag1, 8);

      for(int i=0;i<8;i++){
    
        if((flag1[i]==1)&&(i==7))
        {
          Serial.println("P0A10 (Pack Too Hot Fault)");
          continue;
        }
        if((flag1[i]==1)&&(i==6))
        {
          Serial.println(" P0A0E (Lowest Cell Voltage Too Low Fault)");
          continue;
        }
        if((flag1[i]==1)&&(i==5))
        {
          Serial.println("P0A0C (Highest Cell Voltage Too High Fault)");
          continue;
        }
        if((flag1[i]==1)&&(i==4))
        {
          Serial.println("P0A0B (Internal Software Fault)");
          continue;
        }
        if((flag1[i]==1)&&(i==3))
        {
          Serial.println(" P0A0A (Internal Heatsink Thermistor Fault)");
          continue;
        }
        if((flag1[i]==1)&&(i==2))
        {
          Serial.println("P0A09 (Internal Hardware Fault)");
          continue;
        }
        if((flag1[i]==1)&&(i==1))
        {
          Serial.println("P0A08 (Charger Safety Relay Fault)");
          continue;
        }
        if((flag1[i]==1)&&(i==0))
        {
          Serial.println("P0A07 (Discharge Limit Enforcement Fault)");
          continue;
        }
      }

      //DTC FLAG #2
      int b=(buf[2]);
      int flag2[8];
      decToBinary(b, flag2, 8);

      for(int i=0;i<8;i++){
    
        if((flag2[i]==1)&&(i==7))
        {
          Serial.println("P0A0F (Cell ASIC Fault)");
          continue;
        }
        if((flag2[i]==1)&&(i==6))
        {
          Serial.println(" P0A0D (Highest Cell Voltage Over 5V Fault)");
          continue;
        }
        if((flag2[i]==1)&&(i==5))
        {
          Serial.println("P0AC0 (Current Sensor Fault)");
          continue;
        }
        if((flag2[i]==1)&&(i==4))
        {
          Serial.println("P0A04 (Open Wiring Fault)");
          continue;
        }
        if((flag2[i]==1)&&(i==3))
        {
          Serial.println("P0AFA (Low Cell Voltage Fault)");
          continue;
        }
        if((flag2[i]==1)&&(i==2))
        {
          Serial.println("P0A80 (Weak Cell Fault)");
          continue;
        }
        if((flag2[i]==1)&&(i==1))
        {
          Serial.println("P0A12 (Cell Balancing Stuck Off Fault)");
          continue;
        }
        if((flag2[i]==1)&&(i==0))
        {
          Serial.println("P0A1F (Internal Communication Fault)");
          continue;
        }
      }
      //2
      int c=(buf[3]);
      int flag3[8];
      decToBinary(c, flag3, 8);

      for(int i=0;i<8;i++){
    
        if((flag3[i]==1)&&(i==7))
        {
          Serial.println("P0A06 (Charge Limit Enforcement Fault)");
          continue;
        }
        if((flag3[i]==1)&&(i==6))
        {
          Serial.println("P0A05 (Input Power Supply Fault)");
          continue;
        }
        if((flag3[i]==1)&&(i==5))
        {
          Serial.println("P0AA6 (High Voltage Isolation Fault)");
          continue;
        }
        if((flag3[i]==1)&&(i==4))
        {
          Serial.println("P0560 (Redundant Power Supply Fault)");
          continue;
        }
        if((flag3[i]==1)&&(i==3))
        {
          Serial.println("U0100 (External Communication Fault)");
          continue;
        }
        if((flag3[i]==1)&&(i==2))
        {
          Serial.println("P0A9C (Thermistor Fault)");
          continue;
        }
        if((flag3[i]==1)&&(i==1))
        {
          Serial.println("P0A81 (Fan Monitor Fault)");
          continue;
        }
        if((flag3[i]==1)&&(i==0))
        {
          Serial.println("P0A02 (Weak Pack Fault)");
          continue;
        }
      }
    }
    Serial.println();
    delay(1000);                       // send data per 1000ms
  
}
