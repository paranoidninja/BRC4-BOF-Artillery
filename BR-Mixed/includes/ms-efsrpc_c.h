


 
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for ms-efsrpc.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data
    VC __declspec() decoration level:
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/


#if defined(_M_AMD64)

#include <string.h>

#include "ms-efsrpc_h.h"

#define TYPE_FORMAT_STRING_SIZE   497
#define PROC_FORMAT_STRING_SIZE   1795
#define EXPR_FORMAT_STRING_SIZE   1
#define TRANSMIT_AS_TABLE_SIZE    0
#define WIRE_MARSHAL_TABLE_SIZE   0

typedef struct _ms2Defsrpc_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } ms2Defsrpc_MIDL_TYPE_FORMAT_STRING;

typedef struct _ms2Defsrpc_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } ms2Defsrpc_MIDL_PROC_FORMAT_STRING;

typedef struct _ms2Defsrpc_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } ms2Defsrpc_MIDL_EXPR_FORMAT_STRING;


const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax =
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const ms2Defsrpc_MIDL_TYPE_FORMAT_STRING ms2Defsrpc__MIDL_TypeFormatString;
extern const ms2Defsrpc_MIDL_PROC_FORMAT_STRING ms2Defsrpc__MIDL_ProcFormatString;
extern const ms2Defsrpc_MIDL_EXPR_FORMAT_STRING ms2Defsrpc__MIDL_ExprFormatString;

#define GENERIC_BINDING_TABLE_SIZE   0


/* Standard interface: efsrpc, ver. 1.0,
   GUID={0xc681d488,0xd850,0x11d0,{0x8c,0x52,0x00,0xc0,0x4f,0xd9,0x0f,0x7e}} */




extern const MIDL_STUB_DESC efsrpc_StubDesc;






#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

const ms2Defsrpc_MIDL_PROC_FORMAT_STRING ms2Defsrpc__MIDL_ProcFormatString =
    {
        0,
        {

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x28 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0x40 ),	
			0x46,		
			0x4,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x110 ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0x6 ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0x48 ),	
			NdrFcShort( 0x18 ),	
			0x8,		
			0x0,		

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x20 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x1 ),	
			NdrFcShort( 0x18 ),	
			0x30,		
			0x40,		
			NdrFcShort( 0x0 ),	
			0x0,		
			0x0,		
			NdrFcShort( 0x24 ),	
			NdrFcShort( 0x8 ),	
			0x4c,		
			0x3,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x8 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0xe ),	

	

			NdrFcShort( 0x4114 ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0x18 ),	

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x10 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x2 ),	
			NdrFcShort( 0x18 ),	
			0x30,		
			0x40,		
			NdrFcShort( 0x0 ),	
			0x0,		
			0x0,		
			NdrFcShort( 0x24 ),	
			NdrFcShort( 0x8 ),	
			0x4c,		
			0x3,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x8 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0xe ),	

	

			NdrFcShort( 0x10c ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0x26 ),	

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x10 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x3 ),	
			NdrFcShort( 0x8 ),	
			0x30,		
			0xe0,		
			NdrFcShort( 0x0 ),	
			0x0,		
			0x0,		
			NdrFcShort( 0x38 ),	
			NdrFcShort( 0x38 ),	
			0x40,		
			0x1,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x118 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x32 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x4 ),	
			NdrFcShort( 0x18 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			0x46,		
			0x2,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x10 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x5 ),	
			NdrFcShort( 0x20 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0x8 ),	
			0x46,		
			0x3,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0x48 ),	
			NdrFcShort( 0x10 ),	
			0x8,		
			0x0,		

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x18 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x6 ),	
			NdrFcShort( 0x20 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			0x47,		
			0x3,		
			0xa,		
			0x3,		
			NdrFcShort( 0x1 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0x2013 ),	
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0x36 ),	

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x18 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x7 ),	
			NdrFcShort( 0x20 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			0x47,		
			0x3,		
			0xa,		
			0x3,		
			NdrFcShort( 0x1 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0x2013 ),	
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0x36 ),	

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x18 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0x20 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			0x46,		
			0x3,		
			0xa,		
			0x5,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x1 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0xcc ),	

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x18 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x9 ),	
			NdrFcShort( 0x20 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			0x46,		
			0x3,		
			0xa,		
			0x5,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x1 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0x148 ),	

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x18 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0xa ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0xb ),	
			NdrFcShort( 0x40 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x18 ),	
			NdrFcShort( 0x8 ),	
			0x46,		
			0x7,		
			0xa,		
			0x5,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x1 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0x48 ),	
			NdrFcShort( 0x18 ),	
			0x8,		
			0x0,		

	

			NdrFcShort( 0x48 ),	
			NdrFcShort( 0x20 ),	
			0x8,		
			0x0,		

	

			NdrFcShort( 0xb ),	
			NdrFcShort( 0x28 ),	
			NdrFcShort( 0x15c ),	

	

			NdrFcShort( 0x48 ),	
			NdrFcShort( 0x30 ),	
			0x8,		
			0x0,		

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x38 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0xc ),	
			NdrFcShort( 0x28 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0x8 ),	
			0x47,		
			0x4,		
			0xa,		
			0x3,		
			NdrFcShort( 0x1 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0x48 ),	
			NdrFcShort( 0x10 ),	
			0x8,		
			0x0,		

	

			NdrFcShort( 0x2013 ),	
			NdrFcShort( 0x18 ),	
			NdrFcShort( 0x17e ),	

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x20 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0xd ),	
			NdrFcShort( 0x40 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x18 ),	
			NdrFcShort( 0x8 ),	
			0x46,		
			0x7,		
			0xa,		
			0x5,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x1 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0x48 ),	
			NdrFcShort( 0x18 ),	
			0x8,		
			0x0,		

	

			NdrFcShort( 0x48 ),	
			NdrFcShort( 0x20 ),	
			0x8,		
			0x0,		

	

			NdrFcShort( 0xb ),	
			NdrFcShort( 0x28 ),	
			NdrFcShort( 0x15c ),	

	

			NdrFcShort( 0x48 ),	
			NdrFcShort( 0x30 ),	
			0x8,		
			0x0,		

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x38 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0xe ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0xf ),	
			NdrFcShort( 0x30 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0x8 ),	
			0x46,		
			0x5,		
			0xa,		
			0x5,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x1 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x48 ),	
			NdrFcShort( 0x8 ),	
			0x8,		
			0x0,		

	

			NdrFcShort( 0xb ),	
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0x15c ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x18 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x20 ),	
			NdrFcShort( 0x148 ),	

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x28 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0x38 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0x8 ),	
			0x47,		
			0x6,		
			0xa,		
			0x7,		
			NdrFcShort( 0x1 ),	
			NdrFcShort( 0x1 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x48 ),	
			NdrFcShort( 0x8 ),	
			0x8,		
			0x0,		

	

			NdrFcShort( 0xb ),	
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0x15c ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x18 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0x48 ),	
			NdrFcShort( 0x20 ),	
			0x8,		
			0x0,		

	

			NdrFcShort( 0x2013 ),	
			NdrFcShort( 0x28 ),	
			NdrFcShort( 0x17e ),	

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x30 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x11 ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x12 ),	
			NdrFcShort( 0x20 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			0x47,		
			0x3,		
			0xa,		
			0x3,		
			NdrFcShort( 0x1 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0x2013 ),	
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0x17e ),	

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x18 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x13 ),	
			NdrFcShort( 0x30 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			0x46,		
			0x5,		
			0xa,		
			0x5,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x1 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0xb ),	
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0x15c ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x18 ),	
			NdrFcShort( 0x16a ),	

	

			NdrFcShort( 0xb ),	
			NdrFcShort( 0x20 ),	
			NdrFcShort( 0x186 ),	

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x28 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x14 ),	
			NdrFcShort( 0x10 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			0x44,		
			0x1,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x8 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x15 ),	
			NdrFcShort( 0x28 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0x8 ),	
			0x46,		
			0x4,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0xb ),	
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0x1a4 ),	

	

			NdrFcShort( 0x48 ),	
			NdrFcShort( 0x18 ),	
			0x8,		
			0x0,		

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x20 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x16 ),	
			NdrFcShort( 0x20 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			0x47,		
			0x3,		
			0xa,		
			0x3,		
			NdrFcShort( 0x1 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			NdrFcShort( 0x10b ),	
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0xc ),	

	

			NdrFcShort( 0x2013 ),	
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0x1a8 ),	

	

			NdrFcShort( 0x70 ),	
			NdrFcShort( 0x18 ),	
			0x8,		
			0x0,		

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x17 ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x18 ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x19 ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x1a ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x1b ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x1c ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x1d ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x1e ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x1f ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x20 ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x21 ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x22 ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x23 ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x24 ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x25 ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x26 ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x27 ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x28 ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x29 ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x2a ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x2b ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

	

			0x0,		
			0x48,		
			NdrFcLong( 0x0 ),	
			NdrFcShort( 0x2c ),	
			NdrFcShort( 0x8 ),	
			0x32,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			0x40,		
			0x0,		
			0xa,		
			0x1,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x0 ),	

			0x0
        }
    };

const ms2Defsrpc_MIDL_TYPE_FORMAT_STRING ms2Defsrpc__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	

			0x11, 0x4,	
			NdrFcShort( 0x2 ),	
			0x30,		
			0xa0,		
			0x0,		
			0x0,		

			0x11, 0x8,	

			0x25,		
			0x5c,		
			0x30,		
			0x41,		
			0x0,		
			0x0,		

			0x11, 0x4,	
			NdrFcShort( 0x4 ),	
			0x2,		
			0x5c,		
			0xb5,		
			0x0,		
			NdrFcShort( 0xfffc ),	
			NdrFcShort( 0x1 ),	
			NdrFcShort( 0x1 ),	

			0x11, 0x0,	
			NdrFcShort( 0x4 ),	
			0x2,		
			0x5c,		
			0xb5,		
			0x0,		
			NdrFcShort( 0xfffc ),	
			NdrFcShort( 0x1 ),	
			NdrFcShort( 0x1 ),	

			0x11, 0x4,	
			NdrFcShort( 0x2 ),	
			0x30,		
			0xe1,		
			0x0,		
			0x0,		

			0x11, 0x14,	
			NdrFcShort( 0x2 ),	

			0x12, 0x0,	
			NdrFcShort( 0x90 ),	
			0xb7,		
			0x8,		
			NdrFcLong( 0x0 ),	
			NdrFcLong( 0x1f4 ),	

			0x1d,		
			0x0,		
			NdrFcShort( 0x6 ),	
			0x1,		
			0x5b,		

			0x15,		
			0x0,		
			NdrFcShort( 0x6 ),	
			0x4c,		
			0x0,		
			NdrFcShort( 0xfff4 ),	
			0x5c,		
			0x5b,		

			0x1b,		
			0x3,		
			NdrFcShort( 0x4 ),	
			0x4,		
			0x0,		
			NdrFcShort( 0xfff9 ),	
			NdrFcShort( 0x1 ),	
			0x8,		
			0x5b,		

			0x17,		
			0x3,		
			NdrFcShort( 0x8 ),	
			NdrFcShort( 0xfff0 ),	
			0x2,		
			0x2,		
			0x4c,		
			0x0,		
			NdrFcShort( 0xffe0 ),	
			0x5c,		
			0x5b,		
			0xb7,		
			0x8,		
			NdrFcLong( 0x0 ),	
			NdrFcLong( 0x64 ),	

			0x1b,		
			0x0,		
			NdrFcShort( 0x1 ),	
			0x19,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x1 ),	
			0x2,		
			0x5b,		

			0x1a,		
			0x3,		
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0xa ),	
			0x4c,		
			0x0,		
			NdrFcShort( 0xffe0 ),	
			0x40,		
			0x36,		
			0x5c,		
			0x5b,		

			0x12, 0x0,	
			NdrFcShort( 0xffe2 ),	

			0x1a,		
			0x3,		
			NdrFcShort( 0x20 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			0x8,		
			0x40,		
			0x36,		
			0x36,		
			0x36,		
			0x5b,		

			0x12, 0x0,	
			NdrFcShort( 0xffb8 ),	

			0x12, 0x0,	
			NdrFcShort( 0xffd8 ),	

			0x12, 0x8,	

			0x25,		
			0x5c,		

			0x21,		
			0x3,		
			NdrFcShort( 0x0 ),	
			0x19,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x1 ),	
			NdrFcLong( 0xffffffff ),	
			NdrFcShort( 0x0 ),	

			0x12, 0x0,	
			NdrFcShort( 0xffd4 ),	
			0x5c,		
			0x5b,		

			0x1a,		
			0x3,		
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0xa ),	
			0x4c,		
			0x0,		
			NdrFcShort( 0xff68 ),	
			0x40,		
			0x36,		
			0x5c,		
			0x5b,		

			0x12, 0x0,	
			NdrFcShort( 0xffd8 ),	

			0x11, 0x0,	
			NdrFcShort( 0xffea ),	

			0x11, 0x0,	
			NdrFcShort( 0x62 ),	
			0xb7,		
			0x8,		
			NdrFcLong( 0x0 ),	
			NdrFcLong( 0x1f4 ),	
			0xb7,		
			0x8,		
			NdrFcLong( 0x0 ),	
			NdrFcLong( 0x8000 ),	

			0x1b,		
			0x0,		
			NdrFcShort( 0x1 ),	
			0x19,		
			0x0,		
			NdrFcShort( 0x4 ),	
			NdrFcShort( 0x1 ),	
			0x2,		
			0x5b,		

			0x1a,		
			0x3,		
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0xa ),	
			0x8,		
			0x4c,		
			0x0,		
			NdrFcShort( 0xffdf ),	
			0x36,		
			0x5c,		
			0x5b,		

			0x12, 0x0,	
			NdrFcShort( 0xffe2 ),	

			0x1a,		
			0x3,		
			NdrFcShort( 0x18 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			0x8,		
			0x40,		
			0x36,		
			0x36,		
			0x5c,		
			0x5b,		

			0x12, 0x0,	
			NdrFcShort( 0xff38 ),	

			0x12, 0x0,	
			NdrFcShort( 0xffd8 ),	

			0x21,		
			0x3,		
			NdrFcShort( 0x0 ),	
			0x19,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x1 ),	
			NdrFcLong( 0xffffffff ),	
			NdrFcShort( 0x0 ),	

			0x12, 0x0,	
			NdrFcShort( 0xffd8 ),	
			0x5c,		
			0x5b,		

			0x1a,		
			0x3,		
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0xa ),	
			0x4c,		
			0x0,		
			NdrFcShort( 0xff96 ),	
			0x40,		
			0x36,		
			0x5c,		
			0x5b,		

			0x12, 0x0,	
			NdrFcShort( 0xffd8 ),	

			0x12, 0x0,	
			NdrFcShort( 0xc ),	
			0xb7,		
			0x8,		
			NdrFcLong( 0x0 ),	
			NdrFcLong( 0x41000 ),	

			0x1a,		
			0x3,		
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0xa ),	
			0x4c,		
			0x0,		
			NdrFcShort( 0xffec ),	
			0x40,		
			0x36,		
			0x5c,		
			0x5b,		

			0x12, 0x0,	
			NdrFcShort( 0xff00 ),	

			0x11, 0x14,	
			NdrFcShort( 0xffdc ),	

			0x11, 0x0,	
			NdrFcShort( 0xffe6 ),	

			0x12, 0x0,	
			NdrFcShort( 0x2 ),	

			0x1a,		
			0x3,		
			NdrFcShort( 0x20 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			0x8,		
			0x40,		
			0x36,		
			0x36,		
			0x36,		
			0x5b,		

			0x12, 0x0,	
			NdrFcShort( 0xff32 ),	

			0x12, 0x0,	
			NdrFcShort( 0xff7e ),	

			0x12, 0x0,	
			NdrFcShort( 0xffc8 ),	

			0x12, 0x8,	

			0x25,		
			0x5c,		

			0x11, 0x14,	
			NdrFcShort( 0x2 ),	

			0x12, 0x10,	
			NdrFcShort( 0x2 ),	

			0x12, 0x0,	
			NdrFcShort( 0x2e ),	

			0x1a,		
			0x3,		
			NdrFcShort( 0x18 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x8 ),	
			0x8,		
			0x40,		
			0x36,		
			0x36,		
			0x5c,		
			0x5b,		

			0x12, 0x0,	
			NdrFcShort( 0xfea0 ),	

			0x12, 0x8,	

			0x25,		
			0x5c,		

			0x21,		
			0x3,		
			NdrFcShort( 0x0 ),	
			0x19,		
			0x0,		
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x1 ),	
			NdrFcLong( 0xffffffff ),	
			NdrFcShort( 0x0 ),	

			0x12, 0x0,	
			NdrFcShort( 0xffd8 ),	
			0x5c,		
			0x5b,		

			0x1a,		
			0x3,		
			NdrFcShort( 0x10 ),	
			NdrFcShort( 0x0 ),	
			NdrFcShort( 0x6 ),	
			0x8,		
			0x40,		
			0x36,		
			0x5b,		

			0x12, 0x0,	
			NdrFcShort( 0xffdc ),	

			0x0
        }
    };

const unsigned short efsrpc_FormatStringOffsetTable[] =
    {
    0,
    54,
    104,
    154,
    192,
    234,
    282,
    330,
    378,
    426,
    474,
    504,
    576,
    630,
    702,
    732,
    792,
    858,
    888,
    936,
    996,
    1032,
    1086,
    1134,
    1164,
    1194,
    1224,
    1254,
    1284,
    1314,
    1344,
    1374,
    1404,
    1434,
    1464,
    1494,
    1524,
    1554,
    1584,
    1614,
    1644,
    1674,
    1704,
    1734,
    1764
    };


#endif 