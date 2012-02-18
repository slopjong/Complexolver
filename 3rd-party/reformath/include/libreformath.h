/*
* ******************************DO NOT ALTER ANYTHING IN THIS FILE!!!!******************************
*
* LIBREFORMATH is a library for converting MathML to other file formats such as PNG, PDF, SVG, XAML.
* The current version is 1.0.
* 
* Use of this software is STRICTLY for evaluation purposes only.
*
* This software is FOR SALE. Alternatively, I am willing to open source it in return for a fee. If you know of any entity or indidivual
* (e.g., foundation, philantrophist, etc.) willing to pay for this software, please let me know.
*
* This software is being developed single-handedly by the author.
*
* 
*										LibReforMath version 1.0
*									    Copyright (C) 2011 Peter Frane
*										   All Rights Reserved
*										  reformath@hotmail.com
*							Websites: http://reformath.webnode.com and http://reformath.webnode.com
*/


#ifdef __cplusplus
extern "C" {
#endif

enum mml_file_type 
{
    mml_file_type_pdf,
    mml_file_type_png,
    mml_file_type_svg,
    mml_file_type_xaml
};

struct mml_image_metrics
{
	int baseline, width, height, text_height, text_depth;
	double fwidth, fheight;
};

struct reformath_handle;

typedef reformath_handle *mml_handle;

mml_handle mml_create_handle(void);

void mml_free_handle( mml_handle handle );

bool mml_convert( mml_handle handle, const char *mathml_text );

bool mml_save_to_file( mml_handle handle, const char *filename, mml_file_type file_type );

bool mml_save_to_file_w( mml_handle handle, const wchar_t *filename, mml_file_type file_type );

bool mml_save_to_stream( mml_handle handle, unsigned char **ptr, int *block_size, mml_file_type file_type );

void mml_set_text_color( mml_handle handle, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha );

void mml_set_background_color( mml_handle handle, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha );

void mml_get_text_color( mml_handle handle, unsigned char *red, unsigned char *green, unsigned char *blue, unsigned char *alpha );

void mml_get_background_color( mml_handle handle, unsigned char *red, unsigned char *green, unsigned char *blue, unsigned char *alpha );

double mml_set_scale( mml_handle handle, double xy );

double mml_get_scale( mml_handle handle );

bool mml_can_render( mml_handle handle );

void mml_clear( mml_handle handle );

void mml_destroy_stream( unsigned char **ptr );

bool mml_get_image_size( mml_handle handle, mml_image_metrics * size );

#ifdef WIN32
#include <Windows.h>

bool mml_copy_to_clipboard( mml_handle handle, HWND hwnd );

HBITMAP mml_create_bitmap( mml_handle handle, HDC hdc, mml_image_metrics * size );
#endif

#ifdef __cplusplus
}
#endif
