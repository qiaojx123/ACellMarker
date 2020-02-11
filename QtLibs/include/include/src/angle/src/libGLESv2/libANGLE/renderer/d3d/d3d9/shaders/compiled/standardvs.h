#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
// Parameters:
//
//   float4 halfPixelSize;
//   float4 texcoordOffset;
//
//
// Registers:
//
//   Name           Reg   Size
//   -------------- ----- ----
//   halfPixelSize  c0       1
//   texcoordOffset c1       1
//

    vs_2_0
    def c2, 0.5, -0.5, 1, 0
    dcl_position v0
    add oPos, v0, c0
    mad r0, v0, c2.xyzz, c2.xxww
    mov oT0.zw, r0
    mad oT0.xy, r0, c1.zwzw, c1

// approximately 4 instruction slots used
#endif

const BYTE g_vs20_standardvs[] =
{
      0,   2, 254, 255, 254, 255, 
     42,   0,  67,  84,  65,  66, 
     28,   0,   0,   0, 122,   0, 
      0,   0,   0,   2, 254, 255, 
      2,   0,   0,   0,  28,   0, 
      0,   0,   0,   1,   0,   0, 
    115,   0,   0,   0,  68,   0, 
      0,   0,   2,   0,   0,   0, 
      1,   0,   0,   0,  84,   0, 
      0,   0,   0,   0,   0,   0, 
    100,   0,   0,   0,   2,   0, 
      1,   0,   1,   0,   0,   0, 
     84,   0,   0,   0,   0,   0, 
      0,   0, 104,  97, 108, 102, 
     80, 105, 120, 101, 108,  83, 
    105, 122, 101,   0, 171, 171, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   1,   0,   0,   0, 
      0,   0,   0,   0, 116, 101, 
    120,  99, 111, 111, 114, 100, 
     79, 102, 102, 115, 101, 116, 
      0, 118, 115,  95,  50,  95, 
     48,   0,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  49,  48,  46,  49,   0, 
    171, 171,  81,   0,   0,   5, 
      2,   0,  15, 160,   0,   0, 
      0,  63,   0,   0,   0, 191, 
      0,   0, 128,  63,   0,   0, 
      0,   0,  31,   0,   0,   2, 
      0,   0,   0, 128,   0,   0, 
     15, 144,   2,   0,   0,   3, 
      0,   0,  15, 192,   0,   0, 
    228, 144,   0,   0, 228, 160, 
      4,   0,   0,   4,   0,   0, 
     15, 128,   0,   0, 228, 144, 
      2,   0, 164, 160,   2,   0, 
    240, 160,   1,   0,   0,   2, 
      0,   0,  12, 224,   0,   0, 
    228, 128,   4,   0,   0,   4, 
      0,   0,   3, 224,   0,   0, 
    228, 128,   1,   0, 238, 160, 
      1,   0, 228, 160, 255, 255, 
      0,   0
};
