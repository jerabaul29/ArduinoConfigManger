# ConfigManager

This is a config manager that can be used on Arduino boards. It will let you keep track of configurations by reading and writing to ASCII format. In addition you can access each config variable independantly. This work was inspired by the code available on http://overskill.alexshu.com/saving-loading-settings-on-sd-card-with-arduino/ . This code can be useful when, for example, reading and writing config files from an SD card, and updating those config files if necessary.

## How does it work?

The functionalities of the config manager are provided by the *CONFIG_MANAGER* class. This class (available in **ExampleCppConfigManager**) can be built specifically for your needs using a Python script (available in **PyCppConfigGenerator**), and is exported to the **GeneratedConfigManager** folder (gets created if not present in the repo tree). You have to specify the parameters names, types, and init values when you use the Python script. For illustration, a dummy example is included in the class. The exported class can be used in an Arduino sketch. The types supported for the config parameters are int, String and bool.

## Structure of the repository

- The **ExampleCppConfigManager** folder contains the 'template' class that will be used as a basis by the Python code. This template class contains a dummy config parameter example for illustrative purpose (the *nbr_index* config parameter, protected  by the *#if USE_CONFIG_MANAGER_EXAMPLES*), and an Arduino sketch to illustrate the use of the class on the dummy config parameter.

- The **PyCppConfigGenerator** folder contains the Python code that can be used to generate your custom class. See the **Example_Generation.py** file for a working example.

- The **TestGeneratedLibrary** folder contains the class generated by *Example_Generation.py* together with an illustrative Arduino sketch (tested on Arduino Mega) showing how to use it. The .cpp and .h files in this folder can be obtained by:

```bash
~/Desktop/Git/PythonEasyC++ConfigFileGenerator/PyCppConfigGenerator$ python Example_Generation.py 
~/Desktop/Git/PythonEasyC++ConfigFileGenerator/PyCppConfigGenerator$ cd ..
~/Desktop/Git/PythonEasyC++ConfigFileGenerator$ cp GeneratedConfigManager/* TestGeneratedLibrary/.
```

## Use of the code

For an example of how to generate a custom class for your set of config parameters, see **PyCppConfigGenerator/Example_Generation.py**. For an example of how to use the custom generated class, see **TestGeneratedLibrary/TestGeneratedLibrary.ino**. The custom generated class shown in example is the one generated by the example Python script.

