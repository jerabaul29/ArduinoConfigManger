#include "ConfigManager.h"

CONFIG_MANAGER::CONFIG_MANAGER(void){
  // initialize
  number_remaining_output_char = -1;
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

  // INCLUDE_UPDATE_FIELD


  #if USE_CONFIG_MANAGER_EXAMPLES

    // just an example: for the variable defined as ("nbr_index", "int", 0)

    // just an example
    if (settingName == 'nbr_index'){
      nbr_index = settingValue.toInt();
    }

  #endif

}

////////////////////////////////////////////////////////////////////////////////
// functions for generating data out ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void CONFIG_MANAGER::get_ready_output_char_representation(void){
  // do nothing
};

int CONFIG_MANAGER::remaining_output_char(void){
  return(-1);
};

char CONFIG_MANAGER::next_output_char(void){
  return('x');
};

////////////////////////////////////////////////////////////////////////////////
// functions for get / set field ///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// all are CUSTOM GENERATED ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// INCLUDE_GET_SET_FUNCTIONS_CPP

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
