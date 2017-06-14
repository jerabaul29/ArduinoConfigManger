from __future__ import print_function
import shutil
import os
import collections


def inplace_change(filename, old_string, new_string):
    """Inplace change in a text file.
    """
    stream = open(filename, 'r').read()

    if old_string in stream:
            # print 'Changing "{old_string}" to "{new_string}"'.format(**locals())
            stream = stream.replace(old_string, new_string)

            crrt_file = open(filename, 'w')
            crrt_file.write(stream)
            crrt_file.flush()
            crrt_file.close()

    else:
        print('No occurances of "{old_string}" found.'.format(**locals()))


# all places where some USE_CONFIG_MANAGER_EXAMPLES are present must be modified
config_param = collections.namedtuple('config_param', 'var_name type init')


def generate_INCLUDE_GET_SET_FUNCTIONS_H(config_param_inst):
    """Generate on the model:

    int get_nbr_index(void);
    void set_nbr_index(int);
    // two functions to get and set from String
    String getS_nbr_index(void);
    void setS_nbr_index(String);
    """

    def_1 = config_param_inst.type + " get_" + config_param_inst.var_name + "(void);\n"
    def_2 = "void set_" + config_param_inst.var_name + "(" + config_param_inst.type + ");\n"
    def_3 = "String getS_" + config_param_inst.var_name + "(void);\n"
    def_4 = "void setS_" + config_param_inst.var_name + "(String);\n"

    return def_1 + def_2 + def_3 + def_4


def generate_INCLUDE_CONFIG_VARIABLES_H(config_param_inst):
    """Generate on the model:

    int nbr_index = 0;
    """

    str_out = config_param_inst.type + " " + config_param_inst.var_name + " = " + config_param_inst.init + ";"

    return(str_out)


def generate_INCLUDE_UPDATE_FIELD(config_param_inst):
    """Generate on the model:

    if (crrt_name == 'nbr_index'){
      CONFIG_MANAGER::setS_nbr_index(crrt_value);
    }
    """

    str_out = "if (crrt_name == '" + config_param_inst.var_name + "'){\nCONFIG_MANAGER::setS_" + config_param_inst.var_name + "(crrt_value);\n}\n"
    return(str_out)


def generate_INCLUDE_GET_READY_OUTPUT_CHAR_REPR(total_number_parameters):
    """Generate on the model:

    number_remaining_parameters = 1;
    """

    return("number_remaining_parameters = " + str(total_number_parameters) + ";")


def generate_INCLUDE_GET_OUTPUT_LINE(config_param_inst, index_current_parameter):
    """Generate on the model:

    if (number_remaining_parameters == 1){
      output_string = String("[") + String("nbr_index") + String("=") + CONFIG_MANAGER::getS_nbr_index() + String("]");
      crrt_length_output_string = output_string.length();
      crrt_index_output_string = 0;
    }
    """

    line_1 = "if (number_remaining_parameters == " + str(index_current_parameter) + "){\n"
    line_2 = '  output_string = String("[") + String("' + config_param_inst.var_name + '") + String("=") + CONFIG_MANAGER::getS_' + config_param_inst.var_name + '() + String("]");\n'
    line_3 = "  crrt_length_output_string = output_string.length();\n"
    line_4 = "  crrt_index_output_string = " + str(index_current_parameter - 1) + ";\n}\n"

    return(line_1 + line_2 + line_3 + line_4)


def generate_INCLUDE_GET_SET_FUNCTIONS(config_param_inst):
    """Generate on the model:

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
    """

    def_1 = config_param_inst.type + " CONFIG_MANAGER::get_" + config_param_inst.var_name + "(){\n" + "return(" + config_param_inst.var_name + ");\n}\n"
    def_2 = "void CONFIG_MANAGER::set_" + config_param_inst.var_name + "(" + config_param_inst.type + " val_in){\n" + config_param_inst.var_name + " = val_in;\n}\n"
    def_3 = "String CONFIG_MANAGER::getS_" + config_param_inst.var_name + "(){\n" + "return(String(" + config_param_inst.var_name + "));\n}\n"

    if config_param_inst.type == 'int':
        def_4 = "void CONFIG_MANAGER::setS_" + config_param_inst.var_name + "(String string_in){\n" + config_param_inst.var_name + " = string_in.ToInt();\n}\n"

    elif config_param_inst.type == 'String':
        def_4 = "void CONFIG_MANAGER::setS_" + config_param_inst.var_name + "(String string_in){\n" + config_param_inst.var_name + " = string_in;\n}\n"

    return def_1 + def_2 + def_3 + def_4


def generate_Cpp_code(list_config_params):
    # copy into output directory

    # total number of parameters

    # perform all substitutions
    pass


example_config_param_inst1 = config_param(var_name="test_var1", type="String", init='"xx"')
example_config_param_inst2 = config_param(var_name="test_var2", type="int", init='3')

print(generate_INCLUDE_GET_SET_FUNCTIONS_H(example_config_param_inst1))
print(generate_INCLUDE_GET_SET_FUNCTIONS_H(example_config_param_inst2))

print(generate_INCLUDE_CONFIG_VARIABLES_H(example_config_param_inst1))
print(generate_INCLUDE_CONFIG_VARIABLES_H(example_config_param_inst2))

print(generate_INCLUDE_GET_SET_FUNCTIONS(example_config_param_inst1))
print(generate_INCLUDE_GET_SET_FUNCTIONS(example_config_param_inst2))

print(generate_INCLUDE_UPDATE_FIELD(example_config_param_inst1))
print(generate_INCLUDE_UPDATE_FIELD(example_config_param_inst2))

print(generate_INCLUDE_GET_OUTPUT_LINE(example_config_param_inst1, 1))
print(generate_INCLUDE_GET_OUTPUT_LINE(example_config_param_inst2, 2))

print(generate_INCLUDE_GET_READY_OUTPUT_CHAR_REPR(3))
