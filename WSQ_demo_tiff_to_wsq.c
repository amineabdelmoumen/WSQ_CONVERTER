// To compile the program use the command line
// gcc -m64 -o WSQ_demo_tiff_to_wsq.o  WSQ_demo_tiff_to_wsq.c -ldl
//  or
// gcc -m64 -ldl -o WSQ_demo_tiff_to_wsq.o  WSQ_demo_tiff_to_wsq.c
//
// To run the program use the command line
// ./WSQ_demo_tiff_to_wsq.o


#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>





void* handle = NULL;
char* error;


typedef int (*_ReadImageFromFile)(const char*, int*, int*, unsigned char**);
_ReadImageFromFile ReadImageFromFile = 0;

typedef int (*_SaveImageToFile)(const char*, int, int, int, unsigned char*);
_SaveImageToFile SaveImageToFile = 0;

typedef void (*_WriteWSQ_bitrate)(double);
_WriteWSQ_bitrate WriteWSQ_bitrate = 0;

typedef double (*_ReadWSQ_bitrate)();
_ReadWSQ_bitrate ReadWSQ_bitrate = 0;

typedef void (*_WriteWSQ_ppi)(int);
_WriteWSQ_ppi WriteWSQ_ppi = 0;

typedef int (*_ReadWSQ_ppi)();
_ReadWSQ_ppi ReadWSQ_ppi = 0;

typedef void (*_WriteWSQ_comment)(char*);
_WriteWSQ_comment WriteWSQ_comment = 0;

typedef char* (*_ReadWSQ_comment)();
_ReadWSQ_comment ReadWSQ_comment = 0;

typedef void (*_WriteTIFFcompression)(int);
 _WriteTIFFcompression WriteTIFFcompression = 0;

typedef void (*_WriteTIFFpredictor)(int);
_WriteTIFFpredictor WriteTIFFpredictor = 0;

typedef char* (*_GenerateSerialNumber)();
_GenerateSerialNumber GenerateSerialNumber = 0;

typedef int (*_UnlockWSQLibrary)(char* authorizationcode);
_UnlockWSQLibrary UnlockWSQLibrary = 0;




int main()
{


        char* input_file_name = "./sample_image_2.tif";

        char* output_file_name = "./output_image_2";
        char* error = (char*) NULL;

        int width = 0;
        int height = 0;
        unsigned char* imageData = 0;
        int type;





       if(handle == NULL)
       {
         handle = dlopen("./libWSQ_library64.so", RTLD_LAZY); // open shared library;
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


        if (!ReadImageFromFile) 
        {
          ReadImageFromFile = (_ReadImageFromFile)dlsym(handle, "ReadImageFromFile");
          error = dlerror(); if(error){printf("%s\n", error); return 1;}
        }


        if (!SaveImageToFile) 
        {
          SaveImageToFile = (_SaveImageToFile)dlsym(handle, "SaveImageToFile");
          error = dlerror(); if(error){printf("%s\n", error); return 1;}
        }


         


         ReadImageFromFile(input_file_name, &width, &height, &imageData);

        type = 1; //WSQ;
        //type = 2; //BMP;
        //type = 3; //TIF;
        //type = 4; //PNG;
        //type = 5; //JPG;
        //type = 6; //RGB;
        //type = 7; //TGA;


        SaveImageToFile(output_file_name, type, width, height, imageData);


        dlclose(handle); // close the shared library


//=============
        if(imageData != (unsigned char*) NULL)
        {free(imageData);}
        imageData = (unsigned char*) NULL;
//=============


        printf("%s\n", "Output image is saved to file \"output_image_2.wsq\"");
        return 1;


}

