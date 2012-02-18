/*
*
* Copyright (c) 2011 Peter Frane, Jr. All Rights Reserved
*
* Disclaimer: The author will not be responsible for any damage to your system/data as a result of using this code.
*
*
*  MAKE SURE THE STIXFONTS ARE INSTALLED
* 
*  Make sure also that the DLLs in the SDK folder are available to your EXE
* 
*
* TO COMPILE UNDER LINUX
*
* g++ -o yourfile.out yourfile.cpp -L. libreformath.so.1.1
*
* The above assumes the the yourfile.cpp is in the same folder as libreformath.so.1.1. Also, the library requires the FreeType and Cairo graphics library
*
* If the above does not work, consult an expert or search the web for instructions on how to use Linux shared objects
*/

#include "libreformath.h" // the library's header (required)
#include <stdio.h>
#include <string>

using namespace std;

#pragma comment( lib, "libreformath.lib" )

int main( int argc, char **argv )
{
        // declare the handle
        mml_handle *mhandle; 
        bool result;
        string input;

        // create a handle

        mhandle = mml_create_handle();

        if( !mhandle )
        {
                perror( "unable to create handle" );

                return 1;
        }

        // let's create some MathML input
        // <math> tag is optional; the default is inline; the xmlns attribute is ignored
        
        input  = "<math display='block'>";
        input += "<mfenced open='[' close=']' separators=''><mfrac>";
        input += "<mn>1</mn><mn>2</mn>";
        input += "</mfrac></mfenced>";
        input += "</math>";

        // convert and check the result

        result = mml_convert( mhandle, input.c_str() );

        if( result && mml_can_render( mhandle ) )
        {

        // call either mml_save_to_file() or mml_save_to_file_w to save to a file
        // or mml_save_to_stream to save to memory. When saving to memory, you must call
           // mml_destroy_stream() to free any memory used
         
           // Return values omitted for brevity. 
           // It's your responsibility to provide an explicit extension for the filename.
           // The file type is based on the second argument and NOT on the file extension!

            mml_save_to_file( mhandle, "sample.pdf", mml_file_type_pdf );
            mml_save_to_file( mhandle, "sample.svg", mml_file_type_svg );
            mml_save_to_file( mhandle, "sample.xaml", mml_file_type_xaml ); 

            // do some scaling

            mml_set_scale( mhandle, 2.0 );

            mml_save_to_file( mhandle, "sample.png", mml_file_type_png );


           // to save to a stream, declare these 2 variables

           unsigned char *buffer = NULL;
           int buf_size;

           mml_save_to_stream( mhandle, &buffer, &buf_size, mml_file_type_svg );

           // do something with the output like dumping to console
        
           puts( (char *) buffer );

           // free the buffer; note that the argument is a 
           // pointer to a pointer so the buffer can be reset to NULL

           mml_destroy_stream( &buffer );
        }
		else
		{
			// in case of error, see the file LOG.TXT			
		}

        // free the handle when done

        mml_free( mhandle );
        
        return 0;
}

