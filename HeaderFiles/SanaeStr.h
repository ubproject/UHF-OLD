#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SanaeStr
/*null通常のNULLを使用すると正しく動作しません。*/
#define null ""

#define sfree(d){free(d);d=NULL;}
namespace sanae {
/*
*Copyright 2021 SanaeProject.ALL Rights Reserved.
* Author Usagi
*/
	class str {
	private:
		char* st = NULL;
		/*mode:
		true=コピー先の初期化
		false=初期化なし*/
		void copystring(char** to, const char** from, bool mode = true, bool dofree = false) {
			if (mode) {
				if (dofree) {sfree(*to);}
				(*to) = (char*)malloc(sizeof(*from) * (strlen(*from) + 1));
			}
			if(*to==NULL) {
				printf("\nMessage:メモリの確保に失敗しました。\n");
				exit(0);
			}
			strcpy_s(*to, strlen(*from)+1,*from);
		}
		void replace_c(int position,int len,char* to) {
			char* str1 = (char*)malloc(sizeof(char*) * position);
			char* str2 = NULL;
			char* str3 = (char*)malloc(sizeof(char*)*(strlen(st)+1-(position+len)));
			/*str1=前方文字列 str2=挿入文字列 str3=後方文字列*/
			char* text = (char*)malloc(sizeof(char*)*(position+strlen(to)+strlen(st)+1-(position+len)+1));
			/*text=str1+str2+str3*/
			if (str1==NULL || str3==NULL || text==NULL) {
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
			sfree(st);
			st = (char*)malloc(sizeof(char*)*(strlen(str1)+strlen(str2)+strlen(str3)+3));
			if (st == NULL) { printf("\nMessage:メモリの確保に失敗しました。\n"); exit(0); }
			copystring(&st,(const char**)&str1,false);
			strcat_s(st, strlen(str1) + strlen(str2) + strlen(str3) + 3,str2);
			strcat_s(st, strlen(str1) + strlen(str2) + strlen(str3) + 3, str3); 
			if (position>0) {sfree(str1);}//0の場合エラーが起きるため1以上の場合許可
			sfree(str2);
			sfree(str3);
		}
	public:
		/*初期化*/
		str(const char text[]) {
			copystring(&st, &text);
		}
		/*初期化*/
		str() {
			const char* text = "";
			copystring(&st, &text);
		}
		~str() {
			this->clear();
		}
		size_t len() {
			return strlen(st);
		}
		virtual void operator =(const char text[])final{
			if (strcmp(st, text) != 0) {
				copystring(&st, &text, true, true);
			}
		}
		virtual void operator =(const int d)final {
			this->addint(d);
		}
		virtual void operator =(sanae::str d) final{
			this->add(d.c_str());
		}
		/*その他処理*/
		char& operator [](int t) {
			return *(st+t);
		}
		void operator +=(const char* t){
			this->add(t);
		}
		void operator +=(int i){
			this->addint(i);
		}
		/*if*/
		bool operator ==(const char text[]){
			if (strcmp(st, text) == 0) { return 1; }
			return 0;
		}
		bool operator ==(str t){
			if (strcmp(st, t.c_str()) == 0) { return 1; }
			return 0;
		}
		bool operator !=(const char text[]){
			if (strcmp(st, text) != 0) { return 1; }
			return 0;
		}
		bool operator !=(str t){
			if (strcmp(st, t.c_str()) != 0) { return 1; }
			return 0;
		}
		/*変換関数*/
		operator const char* () {
			return st;
		}
		operator char* (){
			return st;
		}
		operator int(){return atoi(st);}
		/*char*型で返す*/
		const char* c_str(){
			return st;
		}
		/*文字列追加*/
		char* addchr(char d){
			char buf[4];
			snprintf(buf, 4, "%c", d);
			add(buf);
			return st;
		}
		char* add(const char* text){
			char* copyst = (char*)malloc(sizeof(char*)*(strlen(st)+1));
			if (copyst == NULL) { printf("\nMessage:メモリの確保に失敗しました。\n"); exit(0); }
			copystring(&copyst,(const char**)&st);
			sfree(st);
			st = (char*)malloc(sizeof(char*)*(strlen(copyst)+strlen(text)+1));
			copystring(&st,(const char**)&copyst,false);
			if(st==NULL){ printf("\nMessage:メモリの確保に失敗しました。\n"); exit(0); }
			strcat_s(st, strlen(copyst) + strlen(text) + 2,text);
			sfree(copyst);
			return st;
		}
		char* addint(const int i){
			char buf[4];
			snprintf(buf, 4, "%d", i);
			add(buf);
			return st;
		}
		int find(const char* to){
			if (strstr(st, to)==0)return -1;
			if (st == NULL) return -1;
			return strlen(st)-strlen(strstr(st,to));
		}
		int replace(const char* from,const char* to){
			const int position = this->find(from);
			if (position == -1) { return -1; }
			const int len = strlen(from);
			replace_c(position,len,(char*)to);
			return 0;
		}
		virtual void clear() {
			sfree(st);
		}
		//指定したバイト数確保&すべてのデータを消去します。(calloc)
		virtual void secure(unsigned int byte, bool clean = true) {
			if (clean) {
				sfree(st);
			}
			st = (char*)calloc(byte,sizeof(char*));
		}
		/*入力取得
		mode:0 代入
		mode:1 追記
		*/
		void input(size_t size = 1024, unsigned int mode = 0) {
			char* t = (char*)malloc(size * sizeof(char*));
			if (t == NULL) { printf("\nMessage:メモリの確保に失敗しました。\n");exit(0);}
			scanf_s("%s", t, size);
			if (mode == 0) {
				copystring(&st, (const char**)&t, true, true);
			}
			else if (mode == 1) {
				for (unsigned int i = 0; i < strlen(t); i++) {
					this->addchr(*(t + i));
				}
			}
			sfree(t);
		}
	};
}