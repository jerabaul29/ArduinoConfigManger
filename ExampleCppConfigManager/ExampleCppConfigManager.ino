#define USE_CONFIG_MANAGER_EXAMPLES true
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

  Serial.println(F("\nDone reading; internal state: \n"));

  Serial.println(F("nbr_index: "));
  Serial.print(CONFIG_MANAGER_inst.get_nbr_index());
  Serial.println();

  Serial.println(F("\nAsking output of next_output_char: \n"));
  while (CONFIG_MANAGER_inst.remaining_output_char()){
    crrt_char = CONFIG_MANAGER_inst.next_output_char();
    Serial.println(crrt_char);
  }

}

void loop(){

}
