#ifndef dirhanddler_h
#define dirhanddler_h

#include "api.h"

#define LS_MAXH_PATHSIZE 255
#define LS_MAX_PATHSIZE 256


void LSDh_zero(Char* dpath){
	for(Int i=0; i<LS_MAX_PATHSIZE; i++){
		dpath[i] = 0;
	}
}

void LSDh_copy(Char* dpath, Char* spath){
	Int i=0;
	for(; i<LS_MAXH_PATHSIZE && (spath[i]); i++){
		dpath[i] = spath[i];
	}
}

void LSDh_cext(Char* dpath, Char* extension){
	Int dpos = LS_MAXH_PATHSIZE;
	for(;dpos>=0; dpos--){
		if(dpath[dpos]!=0){
			if(dpath[dpos]!='/'){
				dpos++;
			}
			break;
		}
	}
	while(dpos>=0){
		dpos--;
		if(dpath[dpos]=='.'){
			dpos++;
			break;
		}
	}
	while((dpos<LS_MAXH_PATHSIZE)&&(*extension)){
		dpath[dpos] = *extension;
		extension++;
		dpos++;
	}
	dpath[dpos] = 0;
}

void LSDh_cd(Char* dpath, Char* rel){
	Int dpos = LS_MAXH_PATHSIZE;
	for(;dpos>=0; dpos--){
		if(dpath[dpos]!=0){
			if(dpath[dpos]!='/'){
				dpos++;
			}
			break;
		}
	}
	while((*rel)&&(dpos<LS_MAXH_PATHSIZE)){
		if((*rel)=='.'){
			rel++;
			if((*rel)=='.'){
				rel++;
				if((*rel)=='/' || (*rel)==0){
					dpos--;
					while(dpath[dpos]!='/' && dpos>=0){
						dpath[dpos] = 0;
						dpos--;
					}
					rel++;
					continue;
				}
				else{
					dpath[dpos] = '/';
					dpos++;
					dpath[dpos] = '.';
					dpos++;
					dpath[dpos] = '.';
					dpos++;
					while((*rel)!='/' && (*rel) && (dpos<LS_MAXH_PATHSIZE)){
						dpath[dpos] = *rel;
						rel++, dpos++;
					}
					continue;
				}
				
			}
			else if((*rel)=='/'){
				rel++;
				continue;
			}
			else{
				dpath[dpos] = '/';
				dpos++;
				dpath[dpos] = '.';
				dpos++;
				while((*rel)!='/' && (*rel) && (dpos<LS_MAXH_PATHSIZE)){
					dpath[dpos] = *rel;
					rel++, dpos++;
				}
				continue;
			}
		}
		else if((*rel)=='/'){
			rel++;
		}
		dpath[dpos] = '/';
		dpos++;
		while((*rel)!='/' && (*rel) && (dpos<LS_MAXH_PATHSIZE)){
			dpath[dpos] = *rel;
			rel++, dpos++;
		}
	}
	dpath[dpos] = 0;
}

void LSDh_up(Char* dpath){
	Int dpos = LS_MAXH_PATHSIZE;
	for(;dpos>=0; dpos--){
		if(dpath[dpos]!=0){
			if(dpath[dpos]!='/'){
				dpos++;
			}
			break;
		}
	}
	while((dpos>=0)&&(dpath[dpos]!='/')){
		dpath[dpos] = 0;
		dpos--;
	}
}


#endif // dirhanddler_h
