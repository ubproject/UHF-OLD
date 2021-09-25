#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SanaeStr
/*null通常のNULLを使用すると正しく動作しません。*/
#define null ""
namespace sanae {
/*
*Copyright 2021 SanaeProject.ALL Rights Reserved.
*/
	class str {
	private:
		char* st = NULL;
		/*mode:
		true=コピー先の初期化
		false=初期化なし*/
		void copystring(char** to, const char** from, bool mode = true, bool dofree = false) {
			if (mode) {
				if (dofree) {free(*to);}
				(*to) = (char*)malloc(sizeof(*from) * (strlen(*from) + 1));
			}
			if(*to==NULL) {
				printf("\nMessage:メモリの確保に失敗しました。\n");
				exit(0);
			}
			strcpy_s(*to, strlen(*from)+1,*from);
		}
		int getlen(char **text) {
			return strlen(*text)+1;
		}
		void replace_c(int position,int len,char* to) {
			char* str1 = (char*)malloc(sizeof(char*) * position);
			char* str2 = NULL;
			char* str3 = (char*)malloc(sizeof(char*)*(strlen(st)+1-(position+len)));
			/*str1=前方文字列 str2=挿入文字列 str3=後方文字列*/
			char* text = (char*)malloc(sizeof(char*)*(position+strlen(to)+strlen(st)+1-(position+len)+1));
			/*text=str1+str2+str3*/
			if (str1==NULL&&str3==NULL&&text==NULL) {
				printf("\nMessage:メモリの確保に失敗しました。\n");exit(0);
			}
			//str1格納
			for (int i = 0; i < position; i++) {
				*(str1+i) = *(st + i);
			}
			*(str1+position) = 0;
			//str2格納
			copystring(&str2,(const char**)&to);
			//str3格納
			for (unsigned int i = position + len, i2 = 0; i <= strlen(st);i++,i2++) {
				*(str3 + i2) = *(st + i);
			}
			*(str3 + (strlen(str3) + 1)) = 0;
			free(st);
			st = (char*)malloc(sizeof(char*)*(strlen(str1)+strlen(str2)+strlen(str3)+3));
			if (st == NULL) { printf("\nMessage:メモリの確保に失敗しました。\n"); exit(0); }
			copystring(&st,(const char**)&str1,false);
			strcat_s(st, strlen(str1) + strlen(str2) + strlen(str3) + 3,str2);
			strcat_s(st, strlen(str1) + strlen(str2) + strlen(str3) + 3, str3); 
			if (position>0) {free(str1);}//0の場合エラーが起きるため1以上の場合許可
			free(str2);
			free(str3);
		}
	public:
		/*初期化*/
		str(const char text[]) {
			copystring(&st, &text);
		}
		virtual void operator =(const char text[])final{
			if (strcmp(st, text) != 0) {
				copystring(&st, &text, true, true);
			}
		}
		/*その他処理*/
		virtual char operator [](unsigned int i){
			if ((strlen(st)+1)<i) {return NULL;}
			return st[i];
		}
		virtual void operator +=(const char* t){
			this->add(&(*t));
		}
		virtual void operator +=(int i){
			this->addint(i);
		}
		/*if*/
		virtual bool operator ==(const char text[]){
			if (strcmp(st, text) == 0) { return 1; }
			return 0;
		}
		virtual bool operator ==(str t){
			if (strcmp(st, t.c_str()) == 0) { return 1; }
			return 0;
		}
		virtual bool operator !=(const char text[]){
			if (strcmp(st, text) != 0) { return 1; }
			return 0;
		}
		virtual bool operator !=(str t){
			if (strcmp(st, t.c_str()) != 0) { return 1; }
			return 0;
		}
		/*変換関数*/
		virtual operator const char* () {
			return st;
		}
		virtual operator char* (){
			return st;
		}
		virtual operator int(){return atoi(st);}
		/*char*型で返す*/
		virtual const char* c_str() final{
			return st;
		}
		/*文字列追加*/
		virtual char* addchr(char d) {
			char buf[12];
			snprintf(buf, 12, "%c", d);
			add(buf);
			return st;
		}
		virtual char* add(const char* text) final{
			char* copyst = (char*)malloc(sizeof(char*)*getlen(&st));
			if (copyst == NULL) { printf("\nMessage:メモリの確保に失敗しました。\n"); exit(0); }
			copystring(&copyst,(const char**)&st);
			free(st);
			st = (char*)malloc(sizeof(char*)*(strlen(copyst)+strlen(text)+2));
			copystring(&st,(const char**)&copyst,false);
			if(st==NULL){ printf("\nMessage:メモリの確保に失敗しました。\n"); exit(0); }
			strcat_s(st, strlen(copyst) + strlen(text) + 2,text);
			free(copyst);
			return st;
		}
		virtual char* addint(const int i) final{
			char buf[12];
			snprintf(buf, 12, "%d", i);
			add(buf);
			return st;
		}
		virtual int find(const char* to) final{
			if (strstr(st, to)==0) {return -1;}
			return strlen(st)-strlen(strstr(st,to));
		}
		virtual int replace(const char* from,const char* to) final{
			const int position = this->find(from);
			if (position == -1) { return -1; }
			const int len = strlen(from);
			replace_c(position,len,(char*)to);
			return 0;
		}
		virtual void clear() {
			free(st);
		}
	};
}