from __future__ import print_function
import shutil
import os
import collections
import fnmatch


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


def wrapper_multiple_inputs_generate_INCLUDE_GET_OUTPUT_LINE(config_param_list):
    list_strs = []

    for index, crrt_arg in enumerate(config_param_list):
        crrt_output = generate_INCLUDE_GET_OUTPUT_LINE(crrt_arg, index + 1)
        list_strs.append(crrt_output)

    result = "".join(list_strs)
    return(result)


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


def generate_string(list_config_params, function):
    list_strings_out = []

    for crrt_config_param in list_config_params:
        crrt_string = function(crrt_config_param)
        list_strings_out.append(crrt_string)
        list_strings_out.append('\n')

    generated_string = "".join(list_strings_out)

    return(generated_string)


def generate_Cpp_code(list_config_params):
    # paths for source and generated code -----
    pathToSource = '../ExampleCppConfigManager/'
    pathGenerated = '../GeneratedConfigManager/'

    # take care of copying reference files for substitution -----
    if os.path.exists(pathGenerated):
        shutil.rmtree(pathGenerated)

    shutil.copytree(pathToSource, pathGenerated)

    for root, dir_name, file_names in os.walk(pathGenerated):
        for file_name in file_names:
            if not (fnmatch.fnmatch(file_name, "*.cpp") or fnmatch.fnmatch(file_name, "*.h")):
                print("non conforming file: " + root + file_name)
                os.remove(root + file_name)

    # total number of parameters -----
    total_number_parameters = len(list_config_params)

    # perform all substitutions -----

    filename_h = pathGenerated + "ConfigManager.h"
    filename_cpp = pathGenerated + "ConfigManager.cpp"

    # #define USE_CONFIG_MANAGER_EXAMPLES true
    old_string = "#define USE_CONFIG_MANAGER_EXAMPLES true"
    new_string = "#define USE_CONFIG_MANAGER_EXAMPLES false"
    inplace_change(filename_h, old_string, new_string)

    # // INCLUDE_GET_SET_FUNCTIONS_H
    old_string = "// INCLUDE_GET_SET_FUNCTIONS_H"
    new_string = generate_string(list_config_params, generate_INCLUDE_GET_SET_FUNCTIONS_H)
    inplace_change(filename_h, old_string, new_string)

    # // INCLUDE_CONFIG_VARIABLES_H
    old_string = "// INCLUDE_CONFIG_VARIABLES_H"
    new_string = generate_string(list_config_params, generate_INCLUDE_CONFIG_VARIABLES_H)
    inplace_change(filename_h, old_string, new_string)

    # // INCLUDE_UPDATE_FIELD
    old_string = "// INCLUDE_UPDATE_FIELD"
    new_string = generate_string(list_config_params, generate_INCLUDE_UPDATE_FIELD)
    inplace_change(filename_cpp, old_string, new_string)

    # // INCLUDE_GET_READY_OUTPUT_CHAR_REPR
    old_string = "// INCLUDE_GET_READY_OUTPUT_CHAR_REPR"
    new_string = generate_string(list_config_params, generate_INCLUDE_GET_READY_OUTPUT_CHAR_REPR)
    inplace_change(filename_cpp, old_string, new_string)

    # // INCLUDE_GET_OUTPUT_LINE
    old_string = "// INCLUDE_GET_OUTPUT_LINE"
    new_string = wrapper_multiple_inputs_generate_INCLUDE_GET_OUTPUT_LINE(list_config_params)
    inplace_change(filename_cpp, old_string, new_string)

    # // INCLUDE_GET_SET_FUNCTIONS
    old_string = "// INCLUDE_GET_SET_FUNCTIONS"
    new_string = generate_string(list_config_params, generate_INCLUDE_GET_SET_FUNCTIONS)
    inplace_change(filename_cpp, old_string, new_string)

example_config_param_inst1 = config_param(var_name="test_var1", type="String", init='"xx"')
example_config_param_inst2 = config_param(var_name="test_var2", type="int", init='3')
list_config_params = [example_config_param_inst1, example_config_param_inst2]

generate_Cpp_code(list_config_params)

print("\nExample of generated C++ code parts: ----- \n")

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

print("Examples of generate_string:\n")

print(generate_string(list_config_params, generate_INCLUDE_GET_SET_FUNCTIONS_H))
print(generate_string(list_config_params, generate_INCLUDE_CONFIG_VARIABLES_H))
print(generate_string(list_config_params, generate_INCLUDE_GET_SET_FUNCTIONS))
print(generate_string(list_config_params, generate_INCLUDE_UPDATE_FIELD))
print(wrapper_multiple_inputs_generate_INCLUDE_GET_OUTPUT_LINE(list_config_params))
