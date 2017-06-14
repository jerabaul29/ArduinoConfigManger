#include "ConfigManager.h"

String STRING_IN = "bla bla [nbr_index=34]";
int STRING_LT = 29;

char crrt_char;


void setup(){
  delay(5000);
  
  Serial.begin(9600);

  Serial.println(F("\nReady to start; reading: \n"));

  CONFIG_MANAGER CONFIG_MANAGER_inst;

  for (int i=0; i<STRING_LT; i++){
    crrt_char = STRING_IN[i];
    Serial.println(crrt_char);
    CONFIG_MANAGER_inst.read_next_building_char(crrt_char);
  }

  Serial.println(F("nbr_int: "));
  Serial.print(CONFIG_MANAGER_inst.get_nbr_index());

}

void loop(){

}
