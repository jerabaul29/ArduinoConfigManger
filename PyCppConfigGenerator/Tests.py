from PyCppConfigGenerator import *

example_config_param_inst1 = config_param(var_name="test_var1", type="String", init='"xx"')
example_config_param_inst2 = config_param(var_name="test_var2", type="int", init="3")
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
