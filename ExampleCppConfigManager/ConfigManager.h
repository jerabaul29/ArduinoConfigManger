#ifndef CONFIG_MANAGER_h
#define CONFIG_MANAGER_h

#ifndef USE_CONFIG_MANAGER_EXAMPLES
  #define USE_CONFIG_MANAGER_EXAMPLES true
#endif

#include <WString.h>

// NOTE: use char[] instead of string to allow compatibility on Arduino sketches
// #include <string>
// using namespace std;

class CONFIG_MANAGER{

public:

  // -------------------------------------------------------------------------
  // GENERIC FUNCTIONS -------------------------------------------------------
  // -------------------------------------------------------------------------
  // Those are generic, i.e. not generated by the template and always available
  // -------------------------------------------------------------------------

  // constructor
  CONFIG_MANAGER(void);

  // reset the input parsing state
  void reset_input_parsing(void);

  // read next char; for building the configuration state from  char representation
  int read_next_building_char(char);

  // update field from a (settingName, settingValue) argument
  int update_field(String, String);

  // get ready to start outputting the configuration char representation
  void get_ready_output_char_representation(void);

  // if there are still remaining chars to be flush in the output
  bool remaining_output_char(void);

  // out next char; for building the string representation from the configuration state
  char next_output_char(void);


  // -------------------------------------------------------------------------
  // CUSTOM GENERATED FUNCTIONS ----------------------------------------------
  // -------------------------------------------------------------------------
  // Those are custom generated by the template
  // -------------------------------------------------------------------------

  // INCLUDE_GET_SET_FUNCTIONS_H

  #if USE_CONFIG_MANAGER_EXAMPLES

    // NOTE: it may add some overhead and weigth to the sketch to use methods
    // instead of putting all variables as public; make a variant of the code
    // that lets all internals be public?

    // just an example: for the variable defined as ("nbr_index", "int", 0)
    // two functions to get and set from native type
    int get_nbr_index(void);
    void set_nbr_index(int);
    // two functions to get and set from String
    String getS_nbr_index(void);
    void setS_nbr_index(String);


  #endif

private:

  // get one more output line ready for the parser
  void get_output_line_ready(void);

  // -------------------------------------------------------------------------
  // GENERIC VARIABLES -------------------------------------------------------
  // -------------------------------------------------------------------------
  // Those are generic, i.e. not generated by the template and always available
  // -------------------------------------------------------------------------

  // for the parser in
  String settingName;
  String settingValue;
  int state_parser;

  // for the output
  int number_remaining_parameters;
  int crrt_length_output_string;
  int crrt_index_output_string;
  String output_string;
  bool flag_ready_output = false;

  // -------------------------------------------------------------------------
  // CUSTOM GENERATED VARIABLES ----------------------------------------------
  // -------------------------------------------------------------------------
  // Those are custom generated by the template
  // -------------------------------------------------------------------------

  // INCLUDE_CONFIG_VARIABLES_H

  #if USE_CONFIG_MANAGER_EXAMPLES

    // just an example: for the variable defined as ("nbr_index", "int", 0)
    int nbr_index = 0;

  #endif

};

#endif
