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

// INCLUDE_UPDATE_FIELD


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
// INCLUDE_GET_READY_OUTPUT_CHAR_REPR

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
// INCLUDE_GET_OUTPUT_LINE

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

// INCLUDE_GET_SET_FUNCTIONS

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
