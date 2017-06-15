#include "ConfigManager.h"

CONFIG_MANAGER::CONFIG_MANAGER(void){
  // initialize
  number_remaining_parameters = -1;
  CONFIG_MANAGER::reset_input_parsing();
}


////////////////////////////////////////////////////////////////////////////////
// functions for parsing of data in ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void CONFIG_MANAGER::reset_input_parsing(void){
  settingName = "";
  settingValue = "";
  state_parser = 0;
}

int CONFIG_MANAGER::read_next_building_char(char crrt_char){
  if (state_parser == 0){
    // if start of a message, change the state of the parser
    // otherwise do nothing
    if (crrt_char == '['){
      state_parser = 1;
    }
  }

  else if (state_parser == 1){
    // if end of the settingName
    if (crrt_char == '='){
      state_parser = 2;
    }
    else{
      settingName += crrt_char;
    }
  }

  else if (state_parser == 2){
    // if end of the settingValue
    if (crrt_char == ']'){
      // put the settingValue in the right variable
      CONFIG_MANAGER::update_field(settingName, settingValue);

      // reset the parser
      CONFIG_MANAGER::reset_input_parsing();

    }
    else{
      settingValue += crrt_char;
    }
  }

  return(0);

}

int CONFIG_MANAGER::update_field(String crrt_name, String crrt_value){

if (crrt_name == "test_var1"){
CONFIG_MANAGER::setS_test_var1(crrt_value);
}

if (crrt_name == "test_var3"){
CONFIG_MANAGER::setS_test_var3(crrt_value);
}

if (crrt_name == "test_var2"){
CONFIG_MANAGER::setS_test_var2(crrt_value);
}

if (crrt_name == "test_var5"){
CONFIG_MANAGER::setS_test_var5(crrt_value);
}

if (crrt_name == "test_var4"){
CONFIG_MANAGER::setS_test_var4(crrt_value);
}

if (crrt_name == "test_var7"){
CONFIG_MANAGER::setS_test_var7(crrt_value);
}

if (crrt_name == "test_var6"){
CONFIG_MANAGER::setS_test_var6(crrt_value);
}

if (crrt_name == "test_var9"){
CONFIG_MANAGER::setS_test_var9(crrt_value);
}

if (crrt_name == "test_var8"){
CONFIG_MANAGER::setS_test_var8(crrt_value);
}




  #if USE_CONFIG_MANAGER_EXAMPLES

    // just an example: for the variable defined as ("nbr_index", "int", 0)

    // just an example
    if (crrt_name == "nbr_index"){
      CONFIG_MANAGER::setS_nbr_index(crrt_value);
    }

  #endif

}

////////////////////////////////////////////////////////////////////////////////
// functions for generating data out ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void CONFIG_MANAGER::get_ready_output_char_representation(void){
number_remaining_parameters = 9;

  #if USE_CONFIG_MANAGER_EXAMPLES
    number_remaining_parameters = 1;
  #endif

  crrt_index_output_string = -1;

  CONFIG_MANAGER::get_output_line_ready();
}

bool CONFIG_MANAGER::remaining_output_char(void){
  if (!flag_ready_output){
    CONFIG_MANAGER::get_ready_output_char_representation();
    flag_ready_output = true;
  }

  if (crrt_length_output_string - crrt_index_output_string > 0){
    return(true);
  }

  if (number_remaining_parameters > 0){
    return(true);
  }

  return(false);
}

char CONFIG_MANAGER::next_output_char(void){
  if (!flag_ready_output){
    CONFIG_MANAGER::get_ready_output_char_representation();
    flag_ready_output = true;
  }

  if (crrt_length_output_string - crrt_index_output_string > 0){
    crrt_index_output_string += 1;
    return(output_string[crrt_index_output_string - 1]);
  }

  if (number_remaining_parameters > 0){
    CONFIG_MANAGER::get_output_line_ready();
  }

  return('\n');

};

void CONFIG_MANAGER::get_output_line_ready(void){
if (number_remaining_parameters == 1){
  output_string = String("[") + String("test_var1") + String("=") + CONFIG_MANAGER::getS_test_var1() + String("]");
  crrt_length_output_string = output_string.length();
  crrt_index_output_string = 0;
}
if (number_remaining_parameters == 2){
  output_string = String("[") + String("test_var3") + String("=") + CONFIG_MANAGER::getS_test_var3() + String("]");
  crrt_length_output_string = output_string.length();
  crrt_index_output_string = 0;
}
if (number_remaining_parameters == 3){
  output_string = String("[") + String("test_var2") + String("=") + CONFIG_MANAGER::getS_test_var2() + String("]");
  crrt_length_output_string = output_string.length();
  crrt_index_output_string = 0;
}
if (number_remaining_parameters == 4){
  output_string = String("[") + String("test_var5") + String("=") + CONFIG_MANAGER::getS_test_var5() + String("]");
  crrt_length_output_string = output_string.length();
  crrt_index_output_string = 0;
}
if (number_remaining_parameters == 5){
  output_string = String("[") + String("test_var4") + String("=") + CONFIG_MANAGER::getS_test_var4() + String("]");
  crrt_length_output_string = output_string.length();
  crrt_index_output_string = 0;
}
if (number_remaining_parameters == 6){
  output_string = String("[") + String("test_var7") + String("=") + CONFIG_MANAGER::getS_test_var7() + String("]");
  crrt_length_output_string = output_string.length();
  crrt_index_output_string = 0;
}
if (number_remaining_parameters == 7){
  output_string = String("[") + String("test_var6") + String("=") + CONFIG_MANAGER::getS_test_var6() + String("]");
  crrt_length_output_string = output_string.length();
  crrt_index_output_string = 0;
}
if (number_remaining_parameters == 8){
  output_string = String("[") + String("test_var9") + String("=") + CONFIG_MANAGER::getS_test_var9() + String("]");
  crrt_length_output_string = output_string.length();
  crrt_index_output_string = 0;
}
if (number_remaining_parameters == 9){
  output_string = String("[") + String("test_var8") + String("=") + CONFIG_MANAGER::getS_test_var8() + String("]");
  crrt_length_output_string = output_string.length();
  crrt_index_output_string = 0;
}


  #if USE_CONFIG_MANAGER_EXAMPLES

    // just an example: for the variable defined as ("nbr_index", "int", 0)

    // just an example
    if (number_remaining_parameters == 1){
      output_string = String("[") + String("nbr_index") + String("=") + CONFIG_MANAGER::getS_nbr_index() + String("]");
      crrt_length_output_string = output_string.length();
      crrt_index_output_string = 0;
    }

  #endif

  number_remaining_parameters -= 1;
}

////////////////////////////////////////////////////////////////////////////////
// functions for get / set field ///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// all are CUSTOM GENERATED ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

String CONFIG_MANAGER::get_test_var1(){
return(test_var1);
}
void CONFIG_MANAGER::set_test_var1(String val_in){
test_var1 = val_in;
}
String CONFIG_MANAGER::getS_test_var1(){
return(String(test_var1));
}
void CONFIG_MANAGER::setS_test_var1(String string_in){
test_var1 = string_in;
}

String CONFIG_MANAGER::get_test_var3(){
return(test_var3);
}
void CONFIG_MANAGER::set_test_var3(String val_in){
test_var3 = val_in;
}
String CONFIG_MANAGER::getS_test_var3(){
return(String(test_var3));
}
void CONFIG_MANAGER::setS_test_var3(String string_in){
test_var3 = string_in;
}

int CONFIG_MANAGER::get_test_var2(){
return(test_var2);
}
void CONFIG_MANAGER::set_test_var2(int val_in){
test_var2 = val_in;
}
String CONFIG_MANAGER::getS_test_var2(){
return(String(test_var2));
}
void CONFIG_MANAGER::setS_test_var2(String string_in){
test_var2 = string_in.toInt();
}

String CONFIG_MANAGER::get_test_var5(){
return(test_var5);
}
void CONFIG_MANAGER::set_test_var5(String val_in){
test_var5 = val_in;
}
String CONFIG_MANAGER::getS_test_var5(){
return(String(test_var5));
}
void CONFIG_MANAGER::setS_test_var5(String string_in){
test_var5 = string_in;
}

String CONFIG_MANAGER::get_test_var4(){
return(test_var4);
}
void CONFIG_MANAGER::set_test_var4(String val_in){
test_var4 = val_in;
}
String CONFIG_MANAGER::getS_test_var4(){
return(String(test_var4));
}
void CONFIG_MANAGER::setS_test_var4(String string_in){
test_var4 = string_in;
}

String CONFIG_MANAGER::get_test_var7(){
return(test_var7);
}
void CONFIG_MANAGER::set_test_var7(String val_in){
test_var7 = val_in;
}
String CONFIG_MANAGER::getS_test_var7(){
return(String(test_var7));
}
void CONFIG_MANAGER::setS_test_var7(String string_in){
test_var7 = string_in;
}

String CONFIG_MANAGER::get_test_var6(){
return(test_var6);
}
void CONFIG_MANAGER::set_test_var6(String val_in){
test_var6 = val_in;
}
String CONFIG_MANAGER::getS_test_var6(){
return(String(test_var6));
}
void CONFIG_MANAGER::setS_test_var6(String string_in){
test_var6 = string_in;
}

bool CONFIG_MANAGER::get_test_var9(){
return(test_var9);
}
void CONFIG_MANAGER::set_test_var9(bool val_in){
test_var9 = val_in;
}
String CONFIG_MANAGER::getS_test_var9(){
return(String(test_var9));
}
void CONFIG_MANAGER::setS_test_var9(String string_in){
test_var9 = ((string_in == "true") || (string_in == "0"));
}

bool CONFIG_MANAGER::get_test_var8(){
return(test_var8);
}
void CONFIG_MANAGER::set_test_var8(bool val_in){
test_var8 = val_in;
}
String CONFIG_MANAGER::getS_test_var8(){
return(String(test_var8));
}
void CONFIG_MANAGER::setS_test_var8(String string_in){
test_var8 = ((string_in == "true") || (string_in == "0"));
}



#if USE_CONFIG_MANAGER_EXAMPLES

  // just an example: for the variable defined as ("nbr_index", "int", 0)

  int CONFIG_MANAGER::get_nbr_index(){
    return(nbr_index);
  }

  void CONFIG_MANAGER::set_nbr_index(int int_in){
    nbr_index = int_in;
  }

  String CONFIG_MANAGER::getS_nbr_index(){
    return(String(nbr_index));
  }

  void CONFIG_MANAGER::setS_nbr_index(String string_in){
    nbr_index = string_in.toInt();
  }

#endif
