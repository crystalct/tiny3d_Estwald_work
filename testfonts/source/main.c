/* 
   TINY3D sample / (c) 2010 Hermes  <www.elotrolado.net>

*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>

#include <io/pad.h>

#include <tiny3d.h>


// draw one background color in virtual 2D coordinates

void DrawBackground2D(u32 rgba)
{
    tiny3d_SetPolygon(TINY3D_QUADS);

    tiny3d_VertexPos(0  , 0  , 65535);
    tiny3d_VertexColor(rgba);

    tiny3d_VertexPos(847, 0  , 65535);

    tiny3d_VertexPos(847, 511, 65535);

    tiny3d_VertexPos(0  , 511, 65535);
    tiny3d_End();
}

void drawScene()
{
	
    tiny3d_Project2D(); // change to 2D context (remember you it works with 848 x 512 as virtual coordinates)
    DrawBackground2D(0x0040ffff) ; // light blue 

    

}





s32 main(s32 argc, const char* argv[])
{
	padInfo padinfo;
	padData paddata;
	int i;
	tiny3d_Init(1024*1024);
	ioPadInit(7);
	while(1) {
        tiny3d_Clear(0xff000000, TINY3D_CLEAR_ALL);
        tiny3d_AlphaTest(1, 0x10, TINY3D_ALPHA_FUNC_GEQUAL);
        tiny3d_BlendFunc(1, TINY3D_BLEND_FUNC_SRC_RGB_SRC_ALPHA | TINY3D_BLEND_FUNC_SRC_ALPHA_SRC_ALPHA,
            TINY3D_BLEND_FUNC_DST_RGB_ONE_MINUS_SRC_ALPHA | TINY3D_BLEND_FUNC_DST_ALPHA_ZERO,
            TINY3D_BLEND_RGB_FUNC_ADD | TINY3D_BLEND_ALPHA_FUNC_ADD);
		ioPadGetInfo(&padinfo);
		for(i = 0; i < MAX_PADS; i++){
			if(padinfo.status[i]){
				ioPadGetData(i, &paddata);
				if(paddata.BTN_CROSS){
					return 0;
				}
			}
		}
        
		drawScene(); // Draw
		
		tiny3d_Flip();
	}

	return 0;
}

