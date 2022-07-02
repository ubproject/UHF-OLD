#ifndef STR_H_
#define STR_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <wchar.h>
#include <typeinfo>
#if __has_include("locale.h")
	#include <locale.h>
#endif


#ifndef debugmode
#define debugmode false
#endif

typedef long long size;
/*	Author:SanaeProject
 * 	Date:2022/04/29
 * 	Contents:
 * 	Utility programs for string.
 */
namespace sanae{
class str {
private:
	typedef struct{
		size start;
		size end;
	}setting_copystr;

	char*		st =	NULL;
	char*	sub_str=	NULL;
	wchar_t*	wst=	NULL;
	const int over =	2;
	size font_leave=	0;
	static const size start	=0;
	static const size end	=-1;


	inline void log(const char* text){
		if(debugmode){
			printf("[DEBUG]%s\n",text);
		}
	}
	inline void logi(int data){
		if(debugmode){
			printf("size:%d\n",data);
		}
	}
	/*NORMALMODE for copystr*/
	const setting_copystr normalmode{0,-1};
	/*Failed to secure memorys*/
	void mem_err() {
		log("MEM ERROR");
		throw std::runtime_error("Failed to allocate memory.");
	}
	/*Access to out of range*/
	void ran_err() {
		log("Try access to out of range.");
		throw std::range_error("Tried access to out of range.");
	}
	/*Judgement of lowercase*/
	inline bool is_lowercase(char text_c){
		log("Compare lowercase");
		if((size)'a'<=text_c&&text_c<=(size)'z'){
				return true;
		}
		return false;
	}
	/*Lowercase convert to uppercase*/
	inline char up(char text_c){
		log("Change lowercase to uppercase");
		return (char)((size)text_c-font_leave);
	}
	/*Uppercase convert to lowercase*/
	inline char low(char text_c){
		log("Change uppercase to lowercase");
		return (char)((size)text_c+font_leave);
	}
	inline bool compare(const char* text1,const char* text2){
		log("compare str and str");
		size len = 0;
		if((len=(size)strlen(text1))!=(size)strlen(text2))return false;
		for(size i=0;i<len;i++){
			if(text1[i]!=text2[i])return false;
		}
		return true;
	}
	inline void sfree(char** data) {
		log("Free memory");
		free(*data);
		*data = NULL;
	}
	/* id:
	 * copystr:		1001
	 * connect:		1002,1003,1004
	 * str:			1005
	 * operator=:	1006
	 * add:			1007
	 * add_front:	1008
	 * substr:		1009
	 * convert:		1010
	 * */
	inline bool secure(char** data, size count,unsigned const int id) {
		//printf("id:%u,size:%d,size=%d\n",id,(int)count,(int)sizeof(char));
		log("Secure to");
		logi((int)count);
		count += over;
		sfree(data);
		*data = (char*)calloc(count, sizeof(char));
		return *data == NULL ? false : true;
	}
#if __has_include("locale.h")&&__has_include("wchar.h")
	inline bool wsecure(wchar_t** data,size count){
		log("Wsecure to");logi((int)count);
		count += over;
		free(*data);
		*data=NULL;
		*data = (wchar_t*)calloc(count, sizeof(wchar_t*));
		return *data == NULL ? false : true;
	}
#endif
	inline void copystr(char** todata, char** fromdata, setting_copystr mode, bool del_secure = true) {
		log("function [copystr]:");
		logi((int)strlen(*fromdata));
		size secure_count = mode.end == -1 ? strlen(*fromdata)+1 : mode.end;
		if (secure_count<mode.start)ran_err();
		if (del_secure)if(!secure(todata, secure_count,1001))mem_err();
		size i = 0;
		for (size j = mode.start; j < secure_count; j++, i++) {
			(*todata)[i] = (*fromdata)[j];
		}
		(*todata)[i + 1] = '\0';
	}
	inline void connect(char** data,char** front,char** back,bool clean=true){
		log("function [connect]:");
		size all_length = strlen(*front)+strlen(*back)+2;
		char* copy=NULL;
		if(*data==*front){
			copystr(&copy,front,normalmode);
			if(!secure(data,all_length,1002))mem_err();
			for(size i=0;i<(size)strlen(copy);i++){
				(*data)[i]=copy[i];
			}
			for(size i=0,j=(size)strlen(copy);i<(size)strlen(*back);i++,j++){
				(*data)[j]=(*back)[i];
			}
			(*data)[strlen(copy)+strlen(*back)]=0;
			sfree(&copy);
		}else if(*data==*back){
			copystr(&copy,back,normalmode);
			if(!secure(data,all_length,1003))mem_err();
			for(size i=0;i<(size)strlen(*front);i++){
				(*data)[i]=(*front)[i];
			}
			for(size i=0,j=(size)strlen(*front);i<(size)strlen(copy);j++,i++){
				(*data)[j]=copy[i];
			}
			(*data)[strlen(*front)+strlen(copy)]=0;
			sfree(&copy);
		}else{
			if(!secure(data,all_length,1004))mem_err();
			for(size i=0;i<(size)strlen(*front);i++){
				(*data)[i]=(*front)[i];
			}
			for(size i=0,j=(size)strlen(*front);i<(size)strlen(*back);j++,i++){
				(*data)[j]=(*back)[i];
			}
			(*data)[strlen(*front)+strlen(*back)]=0;
		}
	}
public:
	/*Constructors*/
	str(const char* text) {
		log("Constructor:const char*");
		logi((int)strlen(text));
		font_leave=(size)'a'-(size)'A';
		if (text == NULL) {
			const char* te = "";
			copystr(&st, (char**)&te, normalmode);
		}
		else {
			copystr(&st, (char**)&text, normalmode);
		}
	}
#if __has_include("locale.h")&&__has_include("wchar.h")
	str(const wchar_t* wtext){
		log("Constructor:const wchar_t*");
		logi((int)wcslen(wtext));
		font_leave=(size)'a'-(size)'A';
		setlocale(LC_ALL,"");
		size_t err		= 0;
		size_t buffer	= wcslen(wtext)+1;
		if (!secure(&st, buffer,1005))mem_err();
		wcstombs_s(&err,st,sizeof(wchar_t)*buffer,wtext,_TRUNCATE);
	}
#endif
	str():str(""){log("Constructor:\"\"");font_leave=(size)'a'-(size)'A';}
	str(const str& data) {
		log("Constructor const str&");
		logi((int)strlen(data.st));
		font_leave=(size)'a'-(size)'A';
		copystr(&st, (char**)&data.st, normalmode);
	}
	~str() {
		log("Destructor");
		sfree(&st);
		free(wst);
		wst=NULL;
		sfree(&sub_str);
	}
	inline const char* c_str() {
		log("Return char*");
		return (const char*)st;
	}
	inline const wchar_t* c_wstr(){
		log("Return wchar_t*");
		setlocale(LC_ALL,"");
		size_t ret = 0;
		size num = sizeof(wchar_t);
		if (!wsecure(&wst,strlen(st)))mem_err();
		mbstowcs_s(&ret,wst,(num*strlen(st)), st, _TRUNCATE);
		return wst;
	}
	/*operators*/
	inline str& operator =(const char* text){
		log("operator:=(char*)");
		logi((int)strlen(text));
		copystr(&st,(char**)&text,normalmode);
		return *this;
	}
	inline str& operator =(const wchar_t* wtext){
		log("operator:=(wchar_t*)");
		logi((int)wcslen(wtext));
		setlocale(LC_ALL,"");
		size_t err		= 0;
		size_t buffer	= wcslen(wtext)+1;
		if (!secure(&st, buffer,1006))mem_err();
		wcstombs_s(&err,st,sizeof(wchar_t)*buffer,wtext,_TRUNCATE);
		return *this;
	}
	inline str& operator =(const str& text){
		log("operator:=(str&)");
		logi((int)strlen(text.st));
		const setting_copystr equal={0,-1};
		copystr(&st,(char**)&(text.st),equal);
		return *this;
	}
	/*if*/
	inline bool operator ==(const char* text){
		log("Compare:== const char*");
		return compare(text,(const char*)st);
	}
	inline bool operator ==(str& text){
		log("Compare:== str&");
		return compare(text.st,(const char*)st);
	}
	inline bool operator !=(const char* text){
		log("Compare:!= char*");
		return compare(text,(const char*)st)?false:true;
	}
	inline bool operator !=(str& text){
		log("Compare:!= str&");
		return compare((const char*)text.st,(const char*)st)?false:true;
	}
	/*Convert function*/
	inline operator const char*()	{	return (const char*)st;		}
	inline operator	char*()			{	return st;		}
	inline operator str*()			{	return *this;	}
	inline explicit operator int()	{	return atoi(st);}
	#if __has_include("wchar.h") && __has_include("locale.h")
		inline operator const wchar_t* () { return this->c_wstr();};
	#endif
	/*funcs*/
	inline bool empty(){
		return strlen(st)==0?true:false;
	}
	inline size len(){
		return strlen(st);
	}

	inline size find(char data){
		log("Find char");
		for(size i=0;i<(size)strlen(st);i++){
			if(st[i]==data)return i;
		}
		return -1;
	}
	inline size find(const char* data){
		log("Find char*");
		for(size i=0;i<(size)strlen(st);i++){
			if(st[i]==data[0]){
				for(size j=0;j<(size)strlen(data);j++,i++){
					if(st[i]!=data[j]){
						break;
					}else if(st[i]==data[j]&&j==(size)strlen(data)-1){
						return i-(strlen(data)-1);
					}
				}
			}
		}
		return -1;
	}
	inline str& add(const char* text){
		log("Add char*");
		logi((int)strlen(text));
		connect(&st,&st,(char**)&text);
		return *this;
	}
	inline str& add(char text_c){
		log("Add char");
		char* adddata=NULL;
		if(!secure(&adddata,2,1007))mem_err();
		adddata[0]=text_c;
		adddata[1]=0;
		connect(&st,&st,&adddata);
		sfree(&adddata);
		return *this;
	}
	inline str& add_front(const char* text){
		log("Add_front");
		logi((int)strlen(text));
		connect(&st,(char**)&text,&st);
		return *this;
	}
	inline str& add_front(char text_c){
		log("Add_front");
		char* adddata=NULL;
		if(!secure(&adddata,2,1008))mem_err();
		adddata[0]=text_c;
		adddata[1]=0;
		connect(&st,&adddata,&st);
		sfree(&adddata);
		return *this;
	}
	inline const char* substr(size pos,size len){
		log("Substr");
		sfree(&sub_str);
		if((size)strlen(st)<(pos+len))ran_err();
		char* data=NULL;
		if(!secure(&data,len+1,1009))mem_err();
		for(size i=0,j=pos;i<len;i++,j++){
			data[i]=st[j];
		}
		data[len]=0;
		return data;
	}
	inline void replace_c(size pos,size len,const char* replacetext){
		log("Replace_c");
		if(pos==(size)-1)return;
		char* front	=NULL;
		char* back	=NULL;
		setting_copystr front_s={0,pos};
		setting_copystr back_s={(size)(pos+len),(size)strlen(st)};
		copystr(&front,&st,front_s);
		copystr(&back,&st,back_s);
		connect(&st,&front,(char**)&replacetext);
		connect(&st,&st,&back);
		sfree(&front);
		sfree(&back);
	}
	inline str& replace(const char* from,const char* to){
		log("Replace");
		replace_c(this->find(from),strlen(from),to);
		return *this;
	}
	inline str& reverse(size startpoint=start,size endpoint=end){
		log("Reverse");
		char copy;
		if(endpoint==-1)endpoint=(size)strlen(st)-1;
		for(size i=startpoint;i<(size)((endpoint+1)/2);i++){
			copy=st[i];
			st[i]=st[endpoint-i];
			st[endpoint-i]=copy;
		}
		return *this;
	}
	inline str& upper(size startpoint=start,size endpoint=end){
		log("To uppercase");
		endpoint=endpoint==-1?strlen(st):endpoint;
		for(size i=0;i<(size)strlen(st);i++){
			if(is_lowercase(st[i])){
				st[i]=up(st[i]);
			}
		}
		return *this;
	}
	inline str& lower(size startpoint=start,size endpoint=end){
		log("To lowercase");
		endpoint=endpoint==-1?strlen(st):endpoint;
		for(size i=0;i<(size)strlen(st);i++){
			if(!is_lowercase(st[i])){
				st[i]=low(st[i]);
			}
		}
		return *this;
	}
};
}
#endif /* STR_H_ */
