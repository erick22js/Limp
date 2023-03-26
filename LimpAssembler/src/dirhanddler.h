#ifndef dirhanddler_h
#define dirhanddler_h

#include "api.h"

#define LS_MAXH_PATHSIZE 255
#define LS_MAX_PATHSIZE 256


#define LS_SEPDIR '/'

#define LS_ISSEPDIR(chr) (chr=='\\' || chr=='/')

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
			if(!LS_ISSEPDIR(dpath[dpos])){
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
			if(!LS_ISSEPDIR(dpath[dpos])){
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
				if(LS_ISSEPDIR(*rel) || (*rel)==0){
					dpos--;
					while(!LS_ISSEPDIR(dpath[dpos]) && dpos>=0){
						dpath[dpos] = 0;
						dpos--;
					}
					rel++;
					continue;
				}
				else{
					dpath[dpos] = LS_SEPDIR;
					dpos++;
					dpath[dpos] = '.';
					dpos++;
					dpath[dpos] = '.';
					dpos++;
					while(!LS_ISSEPDIR(*rel) && (*rel) && (dpos<LS_MAXH_PATHSIZE)){
						dpath[dpos] = *rel;
						rel++, dpos++;
					}
					continue;
				}
				
			}
			else if(LS_ISSEPDIR(*rel)){
				rel++;
				continue;
			}
			else{
				dpath[dpos] = LS_SEPDIR;
				dpos++;
				dpath[dpos] = '.';
				dpos++;
				while(!LS_ISSEPDIR(*rel) && (*rel) && (dpos<LS_MAXH_PATHSIZE)){
					dpath[dpos] = *rel;
					rel++, dpos++;
				}
				continue;
			}
		}
		else if(LS_ISSEPDIR(*rel)){
			rel++;
		}
		dpath[dpos] = LS_SEPDIR;
		dpos++;
		while(!LS_ISSEPDIR(*rel) && (*rel) && (dpos<LS_MAXH_PATHSIZE)){
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
			if(!LS_ISSEPDIR(dpath[dpos])){
				dpos++;
			}
			break;
		}
	}
	while((dpos>=0) && !LS_ISSEPDIR(dpath[dpos])){
		dpath[dpos] = 0;
		dpos--;
	}
}


#endif // dirhanddler_h
