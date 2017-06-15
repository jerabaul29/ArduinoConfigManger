/*
 * 
 * Illustration of the use of the ConfigManager library.
 * Tested successfully on Arduino Mega.
 * 
 * Produces following serial output:

Asking output: 

[test_var6=x5]
[test_var7=x6]
[test_var4=x3]
[test_var5=x4]
[test_var2=3]
[test_var3=x2]
[test_var1=xx]

Get one single parameter: 

test_var2 (as native type and String): 
3
3

Update parameters var1 (rho) and var2 (5)... 

After updated internal state: 

test_var1: 
rho
rho
test_var2: 
5
5

Read input message: 

[test_var4=bla]
[test_var2=10]
Asking output: 

[test_var6=x5]
[test_var7=x6]
[test_var4=bla]
[test_var5=x4]
[test_var2=10]
[test_var3=x2]
[test_var1=rho]

 * 
 */

#define USE_CONFIG_MANAGER_EXAMPLES true
#include "ConfigManager.h"

String STRING_IN = "[test_var4=bla]\n[test_var2=10]";

int STRING_LT = STRING_IN.length();

char crrt_char;


void setup(){
  delay(500);

  Serial.begin(9600);

  CONFIG_MANAGER CONFIG_MANAGER_inst;

  Serial.println(F("\nAsking output: \n"));
  CONFIG_MANAGER_inst.get_ready_output_char_representation();
  while (CONFIG_MANAGER_inst.remaining_output_char()){
    crrt_char = CONFIG_MANAGER_inst.next_output_char();
    Serial.print(crrt_char);
  }

  Serial.println(F("\n\nGet one single parameter: \n"));

  Serial.println(F("test_var2 (as native type and String): "));
  Serial.print(CONFIG_MANAGER_inst.get_test_var2());
  Serial.println();
  Serial.print(CONFIG_MANAGER_inst.getS_test_var2());
  Serial.println();

  Serial.println(F("\nUpdate parameters var1 (rho) and var2 (5)... \n"));

  String settingName = "test_var1";
  String settingValue = "rho";
  CONFIG_MANAGER_inst.update_field(settingName, settingValue);
  settingName = "test_var2";
  settingValue = "5";
  CONFIG_MANAGER_inst.update_field(settingName, settingValue);

  Serial.println(F("After updated internal state: \n"));

  Serial.println(F("test_var1: "));
  Serial.print(CONFIG_MANAGER_inst.get_test_var1());
  Serial.println();
  Serial.print(CONFIG_MANAGER_inst.getS_test_var1());
  Serial.println();
  Serial.println(F("test_var2: "));
  Serial.print(CONFIG_MANAGER_inst.get_test_var2());
  Serial.println();
  Serial.print(CONFIG_MANAGER_inst.getS_test_var2());
  Serial.println();

  Serial.println(F("\nRead input message: \n"));

  CONFIG_MANAGER_inst.reset_input_parsing();
  for (int i=0; i<STRING_LT; i++){
    crrt_char = STRING_IN[i];
    Serial.print(crrt_char);
    CONFIG_MANAGER_inst.read_next_building_char(crrt_char);
  }

  Serial.println(F("\nAsking output: \n"));
  CONFIG_MANAGER_inst.get_ready_output_char_representation();
  delay(5);
  while (CONFIG_MANAGER_inst.remaining_output_char()){
    crrt_char = CONFIG_MANAGER_inst.next_output_char();
    Serial.print(crrt_char);
  }
  
}

void loop(){

}
