#include<node_api.h>

/*
napi_env - This is an abstraction for v8 Isolate or instance in other vms with its own heap and gc

napi_value - This is an abstraction over JS's variables and represents JS value that you can easily create/populate and retrurn to JS Land
*/


/*
Here is the native c function that we want to be used.
This accepts napi_env(v8 abstraction) and napi_callback_info(to extract arg info)
This function will accept single js number as an argument,
convert it to 32 bit int, multiple by 17 and then return
it as another js number (which is represented by napi_value)
*/

napi_value MyFirstFunction(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 1; // total no of arg expected
  napi_value argv[1];

  printf("Inside MyFirstFunction in C world \n");
  // last two args are this and data pointer and are null for this eg 
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  printf("Populating argv with the input passed \n");
  // now we need to convert the arg from napi_value to c world (32 bit int)
  int number = 0; // 32 bit c int
  status = napi_get_value_int32(env, argv[0], &number);
   
  if(status != napi_ok) {
    napi_throw_error(env, NULL, "could not extract int value \n");
  }
  printf("Found the argument passed as %d",number); 
  // multiple number by 17 and convert back t js number
  napi_value result;
  number = number * 17;
  printf("Mulitplied the number by 17 in c \n");
  status = napi_create_int32(env, number, &result);
  printf("Converting result back to js world \n");
  return result;
}

// This is our init method that returns the exports that will be availble to JS world
napi_value Init(napi_env env, napi_value exports) {
  // module initialization code goes here
  printf("Init function called, module is initialized \n"); 
  napi_status status;
  napi_value fn;

  // create the function in js context and assign it to
  // napi_value using napi_create_function

  // arg2 and arg3 are function name and length respectively
  // leaving them empty for this example

  status = napi_create_function(env, NULL, 0, MyFirstFunction, NULL, &fn);
  if (status != napi_ok) {
    api_throw_error(env, NULL, "Unable to wrap native function");
  }

  // Assign the function to our exports using
  // napi_set_named_property
  // This function takes env (napi_env type), exorts (anpi_value) and the 
  // property name 'my_function' (this will get added in js world)
  // fn is the napi_value type (function that we want to associate with my_funcion prop) 
  status = napi_set_named_property(env, exports, "my_function", fn); 
  
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }
  return exports;
}

// here we call NAPI_MODULE function and pass it module name andiInit function
NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
