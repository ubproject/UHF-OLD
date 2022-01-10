#pragma once
#ifndef INCLUDE_GUARD_SANAESTR_H
#define INCLUDE_GUARD_SANAESTR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*ERROR用*/
#include <stdexcept>
#include <exception>
/*splitメンバ用*/
#include <vector>

#pragma warning(disable:4267)
#pragma warning(disable:4477)
namespace sanae {
/*
*Copyright 2021 SanaeProject.ALL Rights Reserved.
* Author Usagi
*/
	class str {
	private:
		//freeした後ポインタをNULLにします
		template<typename T>
		void sfree(T* d) { free(d); d = NULL; }
		//errorを返します
		[[noreturn]] void mem_err() {
			throw std::runtime_error("メモリ確保に失敗しました。");
		}
		//callocで確保します。 成功 true 失敗:false
		int _calloc(char** to, size_t count, bool dofree = true) {
			if (count == 0) {count += 1;}
			if (dofree)sfree(*to);
			*to = (char*)calloc(count,sizeof(char*));
			return *to == NULL?false:true;
		}
		char* st = NULL;
		/*mode:
		true=コピー先の初期化
		false=初期化なし*/
		void copystring(char** to,char** from,bool dofree=true) {
			if (dofree)sfree(*to);
			if (!_calloc(to, (strlen(*from) + 1)))mem_err();
			strcpy_s(*to, strlen(*from)+1,*from);
		}
		void copystring(char** to, const char** from, bool dofree = true) {
			if (dofree)sfree(*to);
			if (!_calloc(to, (strlen(*from) + 1)))mem_err();
			strcpy_s(*to, strlen(*from) + 1, *from);
		}
		void replace_c(int position,int len,char* to) {
			char* str1 = NULL;
			if (!_calloc(&str1, position))mem_err();
			char* str2 = NULL;
			char* str3 = NULL;
			if (!_calloc(&str3, strlen(st) + 1 - (position + len)))mem_err();
			/*str1=前方文字列 str2=挿入文字列 str3=後方文字列*/
			char* text = NULL;
			if (!_calloc(&text, position + strlen(to) + strlen(st) + 1 - (position + len) + 1))mem_err();
			/*text=str1+str2+str3*/
			//str1格納
			for (int i = 0; i < position; i++) {
				*(str1+i) = *(st + i);
			}
			*(str1+position) = 0;
			//str2格納
			copystring(&str2,&to,true);
			//str3格納
			for (unsigned int i = position + len, i2 = 0; i <= strlen(st);i++,i2++) {
				*(str3 + i2) = *(st + i);
			}
			*(str3 + (strlen(str3) + 1)) = 0;
			if (!_calloc(&st, strlen(str1) + strlen(str2) + strlen(str3) + 3))mem_err();
			copystring(&st,&str1,false);
			strcat_s(st, strlen(str1) + strlen(str2) + strlen(str3) + 3,str2);
			strcat_s(st, strlen(str1) + strlen(str2) + strlen(str3) + 3, str3); 
			if (position>0) {sfree(str1);}//0の場合エラーが起きるため1以上の場合許可
			sfree(str2);
			sfree(str3);
		}
	public:
		//指定されたサイズ確保する
		void secure(size_t count) {
			if (!_calloc(&st, count))mem_err();
		}
		/*コンストラクタ*/
		str(const char text[]) {
			copystring(&st, &text);
		}
		/*コンストラクタ*/
		str() {
			const char* text = "";
			copystring(&st, &text);
		}
		/*コピーコンストラクタ*/
		str(const str& strc) {
			char* test = strc.st;
			copystring(&st, &test);
		}
		/*デストラクタ*/
		~str() {
			this->clear();
		}
		size_t len() {
			return strlen(st);
		}
		virtual str& operator =(const char&)final{
			return *this;
		}
		virtual str& operator =(str&) {
			return *this;
		}
		virtual str& operator =(const int d)final {
			this->addint(d);
			return *this;
		}
		/*その他処理*/
		char& operator [](unsigned int t) {
			if (strlen(st)<=t) {
				throw std::out_of_range("範囲外の値にアクセスしようとしました。");
			}
			return *(st+t);
		}

		str& operator +=(const char* t){
			this->add(t);
			return *this;
		}
		str& operator +=(int i){
			this->addint(i);
			return *this;
		}

		str& operator <<(const char* t) {
			this->add(t);
			return *this;
		}
		str& operator <<(char t) {
			this->addchr(t);
			return *this;
		}
		str& operator <<(int t) {
			this->addint(t);
			return *this;
		}

		/*if*/
		bool operator ==(const char text[]){
			if (strcmp(st, text) == 0) { return true; }
			return false;
		}
		bool operator ==(str& t){
			if (strcmp(st, t.c_str()) == 0) { return true; }
			return false;
		}
		bool operator !=(const char text[]){
			if (strcmp(st, text) != 0) { return true; }
			return false;
		}
		bool operator !=(str& t){
			if (strcmp(st, t.c_str()) != 0) { return true; }
			return false;
		}
		/*変換関数*/
		operator const char* () {
			return st;
		}
		operator char* (){
			return st;
		}
		operator int(){return atoi(st);}
		/*char*型で返します。*/
		const char* c_str(){
			return st;
		}
		/*文字を追加*/
		str& addchr(char d){
			char buf[4];
			snprintf(buf, 4, "%c", d);
			add(buf);
			return *this;
		}
		//指定文字の個数を数えます。
		int count(char t) {
			int count = 0;
			for (unsigned int i = 0; i < strlen(this->st);i++) {
				if ((this->st[i]) == t)count++;
			}
			return count;
		}
		//追記します。
		str& add(const char* text){
			char* copyst = NULL;
			if (!_calloc(&copyst, strlen(st) + 1, false))mem_err();
			copystring(&copyst,&st,false);
			sfree(st);
			if (!_calloc(&st, strlen(copyst) + strlen(text) + 1, false))mem_err();
			copystring(&st,&copyst,false);
			strcat_s(st, strlen(copyst) + strlen(text) + 2,text);
			sfree(copyst);
			return *this;
		}
		//前方に追記します。
		str& add_front(const char* text) {
			char* copyst = NULL;
			if (!_calloc(&copyst, strlen(st) + 1, false))mem_err();
			copystring(&copyst, &st);
			sfree(st);
			if (!_calloc(&st, strlen(copyst) + strlen(text) + 1, false))mem_err();
			copystring(&st,&text,false);
			strcat_s(st, strlen(copyst) + strlen(text) + 2, copyst);
			sfree(copyst);
			return *this;
		}
		//int型を追加します。
		str& addint(const int i){
			char buf[4];
			snprintf(buf, 4, "%d", i);
			add(buf);
			return *this;
		}
		/*検索文字列が存在しない場合は - 1を返します。
		存在する場合は配列番号を返します。
		*/
		int find(const char* to){
			if (strstr(st, to)==0)return -1;
			if (st == NULL) return -1;
			#pragma warning(disable:6387) 
			return strlen(st)-strlen(strstr(st,to));
		}
		/*検索文字が存在しない場合は - 1を返します。
		存在する場合は配列番号を返します。
		*/
		int find(const char to) {
			for (unsigned int i = 0; i < strlen(st);i++) {
				if (st[i]==to) {
					return i;
				}
			}
			return -1;
		}
		/*検索文字が存在しない場合は - 1を返します。
		存在する場合は配列番号を返します。(後ろから探します)*/
		int rfind(const char to) {
			for(int i = strlen(this->st) - 1; i >= 0;i--) {
				if (this->st[i]==to) {
					return i;
				}
			}
			return -1;
		}
		/*切り抜いて返します。 substr(切り抜く配列番号,そこから切り抜く個数)
		第二引数で0が渡された場合切り抜く配列番号~最後まで切り抜きます。
		*/
		char* substr_c(unsigned int position,int count=0) {
			count == 0 ? count = strlen(this->st) - position:count;
			char* data = NULL;
			if (!_calloc(&data, count + position + 1), false)mem_err();
			for (unsigned int i = position,now=0; i < (count + position);i++,now++) {
				data[now] = this->st[i];
			}
			return data;
		}
		/*切り抜いて返します。
		第一引数~第二引数まで切り抜きます.
		*/
		char* substr(char start,char finish) {
			int s = this->find(start);
			int f = this->rfind(finish);
			int count = f - s;
			return this->substr_c(s+1,count-1);
		}
		/*文字と文字を入れ替えます。*/
		int replace(const char* from,const char* to){
			const int position = this->find(from);
			if (position == -1) { return -1; }
			const int len = strlen(from);
			replace_c(position,len,(char*)to);
			return 0;
		}
		/*値を消去します。*/
		virtual void clear() {
			sfree(st);
		}
		/*入力取得
		mode:0 代入
		mode:1 追記
		*/
		void input(size_t size = 1024, unsigned int mode = 0) {
			char* t = NULL;
			if (!_calloc(&t, size, false))mem_err();
			scanf_s("%s", t, size);
			if (mode == 0) {
				copystring(&st, &t, true);
			}
			else if (mode == 1) {
				for (unsigned int i = 0; i < strlen(t); i++) {
					this->addchr(*(t + i));
				}
			}
			sfree(t);
		}
		//指定した文字で分割しstd::vectorで返します。
		std::vector<str> split(const char split_text) {
			std::vector<str> data;
			int hear = this->find(split_text);
			if (hear==-1) {
				data.push_back(st);
				return data;
			}
			while (1) {
				int found = this->find(split_text);
				char* deldata = NULL;
				if (!_calloc(&deldata, found, false))mem_err();
				for (int i = 0; i < found+1;i++) {
					deldata[i] = st[i];
				}
				str adddata="";
				adddata.add((const char*)deldata);
				this->replace(adddata.c_str(),"");
				data.push_back(adddata);
				found = this->find(split_text);
				if (found == -1) {
					str g = "";
					g.add(st);
					g.replace(deldata,"");
					data.push_back(g);
					for (unsigned int i = 0; i < data.size();i++) {
						if (data[i].find(split_text)!=-1) {
							data[i][strlen(data[i].c_str())-1] = 0;
						}
					}
					return data;
				}
			}
		}
	};
}
#endif
