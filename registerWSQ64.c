// To compile the program use the command line
// gcc -m64 -o registerWSQ64.o  registerWSQ64.c -ldl
// or
// gcc -m64 -ldl -o registerWSQ64.o  registerWSQ64.c
// To run the program use the command line
// ./registerWSQ64.o


#include <stdio.h>
#include <dlfcn.h>



void* handle = NULL;
char* error;


typedef char* (*_GenerateSerialNumber)();
_GenerateSerialNumber GenerateSerialNumber = 0;

typedef int (*_UnlockWSQLibrary)(char* authorizationcode);
_UnlockWSQLibrary UnlockWSQLibrary = 0;




int main()
{


        char* serial_number;
        char* wsq_unlock_code = "my-unlock-code"; // enter here your unlock code (authorization key)
        char* error;
        int ret;



       if(handle == NULL)
       {
         handle = dlopen("./libWSQ_library64.so", RTLD_LAZY); // open shared library
         error = dlerror(); if(error){printf("%s\n", error); return 1;}
       }


        if (!GenerateSerialNumber) 
        {
          GenerateSerialNumber = (_GenerateSerialNumber)dlsym(handle, "GenerateSerialNumber");
          error = dlerror(); if(error){printf("%s\n", error); return 1;}
        }




        if (!UnlockWSQLibrary) 
        {
          UnlockWSQLibrary = (_UnlockWSQLibrary)dlsym(handle, "UnlockWSQLibrary");
          error = dlerror(); if(error){printf("%s\n", error); return 1;}
        }




         serial_number = GenerateSerialNumber();

       /*   printf("%s%s\n", "Generated serial number is:\n", serial_number);
 */

         ret = UnlockWSQLibrary(wsq_unlock_code);

        /*  if (ret == 1)
         {printf("%s\n", "WSQ library successfully registered to this computer.");}
         else if (ret == 0)
         {printf("%s\n", "Authorization code is invalid.");}
         else if (ret == 2)
         {printf("%s\n", "Error writing license file. Please check directory write permisions.");}
 */

         dlclose(handle); // close the shared library

         return 1;


}

