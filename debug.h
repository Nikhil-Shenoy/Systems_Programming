#ifdef DEBUG_ON
	#ifndef DEBUG
		#define DEBUG_PRINTLN(str) do{printf(str);printf("\n");}while(0)
		#define DEBUG_PRINTLN_F(str, ...) do{printf(str, __VA_ARGS__);printf("\n");}while(0)
	#endif
#else
	#ifndef DEBUG
		#define DEBUG_PRINTLN(str) ;
		#define DEBUG_PRINTLN_F(str, ...) ;
	#endif
#endif
