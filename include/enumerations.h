#ifndef ENUMERATIONS_H
#define ENUMERATIONS_H

typedef enum {
	Renderer_Api_None = -1, 
	Renderer_API_Open_GL,
	Renderer_API_Vulkan,
	Renderer_API_DX3D
} RENDERER_API;

typedef enum {
	Extension_Type_JPG = 0,
	Extension_Type_PNG = 1
} Extension_Type;

typedef enum {
	Layout_Type_Pos = 0,
	Layout_Type_PosCol = 1,
	Layout_Type_PosTex = 2,
	Layout_Type_PosColTex = 3,
} Layout_Type;



#endif