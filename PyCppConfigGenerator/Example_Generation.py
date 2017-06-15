from PyCppConfigGenerator import *

dict_all_params = {}
dict_all_params[1] = config_param(var_name="test_var1", type="String", init='"xx"')
dict_all_params[2] = config_param(var_name="test_var2", type="int", init="3")
dict_all_params[3] = config_param(var_name="test_var3", type="String", init='"x2"')
dict_all_params[4] = config_param(var_name="test_var4", type="String", init='"x3"')
dict_all_params[5] = config_param(var_name="test_var5", type="String", init='"x4"')
dict_all_params[6] = config_param(var_name="test_var6", type="String", init='"x5"')
dict_all_params[7] = config_param(var_name="test_var7", type="String", init='"x6"')
dict_all_params[8] = config_param(var_name="test_var8", type="bool", init='false')
dict_all_params[9] = config_param(var_name="test_var9", type="bool", init='true')

list_config_params = generate_list_params_from_dict(dict_all_params)

generate_Cpp_code(list_config_params)
