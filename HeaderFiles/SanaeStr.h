#pragma once
#ifndef INCLUDE_GUARD_SANAESTR_H
#define INCLUDE_GUARD_SANAESTR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*ERROR�p*/
#include <stdexcept>
#include <exception>
/*split�����o�p*/
#include <vector>

#pragma warning(disable:4267)
#pragma warning(disable:4477)

/*-----------------------------------------------
* Project:SanaeProject-UsefulHeadersProject
* Dev:SanaeProject
* Function:
this headers have "String type and mathematics
functions and else many functions and types.".
*Copyright 2021 SanaeProject.ALL Rights Reserved.
-----------------------------------------------*/
namespace sanae {
	/*-----------------------------------------------
	* Project:SanaeProject-UsefulHeadersProject
	* Dev:SanaeProject
	* Function:
	This header has String type.
	*Copyright 2021 SanaeProject.ALL Rights Reserved.
	-----------------------------------------------*/
	class str {
	private:
		//free������|�C���^��NULL�ɂ��܂�
		template<typename T>
		void sfree(T* d) { free(d); d = NULL; }
		//error��Ԃ��܂�
		[[noreturn]] void mem_err() {
			throw std::runtime_error("�������m�ۂɎ��s���܂����B");
		}
		//calloc�Ŋm�ۂ��܂��B ���� true ���s:false
		int _calloc(char** to, size_t count, bool dofree = true) {
			if (count == 0) {count += 1;}
			if (dofree)sfree(*to);
			*to = (char*)calloc(count,sizeof(char*));
			return *to == NULL?false:true;
		}
		char* st = NULL;
		/*mode:
		true=�R�s�[��̏�����
		false=�������Ȃ�*/
		void copystring(char** to,char** from,bool dofree=true) {
			if (dofree)sfree(*to);
			if (!_calloc(to, (strlen(*from) + 1),false))mem_err();
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
			/*str1=�O�������� str2=�}�������� str3=���������*/
			char* text = NULL;
			if (!_calloc(&text, position + strlen(to) + strlen(st) + 1 - (position + len) + 1))mem_err();
			/*text=str1+str2+str3*/
			//str1�i�[
			for (int i = 0; i < position; i++) {
				*(str1+i) = *(st + i);
			}
			*(str1+position) = 0;
			//str2�i�[
			copystring(&str2,&to,true);
			//str3�i�[
			for (unsigned int i = position + len, i2 = 0; i <= strlen(st);i++,i2++) {
				*(str3 + i2) = *(st + i);
			}
			*(str3 + (strlen(str3) + 1)) = 0;
			if (!_calloc(&st, strlen(str1) + strlen(str2) + strlen(str3) + 3))mem_err();
			copystring(&st,&str1,false);
			strcat_s(st, strlen(str1) + strlen(str2) + strlen(str3) + 3,str2);
			strcat_s(st, strlen(str1) + strlen(str2) + strlen(str3) + 3, str3); 
			if (position>0) {sfree(str1);}//0�̏ꍇ�G���[���N���邽��1�ȏ�̏ꍇ����
			sfree(str2);
			sfree(str3);
		}
	public:
		//�w�肳�ꂽ�T�C�Y�m�ۂ���
		void secure(size_t count) {
			if (!_calloc(&st, count))mem_err();
		}
		/*�R���X�g���N�^*/
		str(const char text[]) {
			copystring(&st, &text);
		}
		/*�R���X�g���N�^*/
		str() {
			const char* text = "";
			copystring(&st, &text);
		}
		/*�R�s�[�R���X�g���N�^*/
		str(const str& strc) {
			char* test = strc.st;
			copystring(&st, &test);
		}
		/*�f�X�g���N�^*/
		~str() {
			this->clear();
		}
		size_t len() {
			return strlen(st);
		}
		virtual str& operator =(const char text[])final {
			copystring(&st, &text);
			return *this;
		}
		str& operator =(const str& strc) {
			char* test = strc.st;
			copystring(&st, &test);
			return *this;
		}
		/*���̑�����*/
		char& operator [](int t) {
			if (strlen(st)<=t) {
				throw std::out_of_range("�͈͊O�̒l�ɃA�N�Z�X���悤�Ƃ��܂����B");
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
		/*�ϊ��֐�*/
		operator const char* () {
			return st;
		}
		operator char* (){
			return st;
		}
		operator int(){return atoi(st);}
		/*char*�^�ŕԂ��܂��B*/
		const char* c_str(){
			return st;
		}
		/*������ǉ�*/
		str& addchr(char d){
			char buf[4];
			snprintf(buf, 4, "%c", d);
			add(buf);
			return *this;
		}
		//�w�蕶���̌��𐔂��܂��B
		int count(char t) {
			int count = 0;
			for (unsigned int i = 0; i < strlen(this->st);i++) {
				if ((this->st[i]) == t)count++;
			}
			return count;
		}
		//�ǋL���܂��B
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
		//�O���ɒǋL���܂��B
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
		//int�^��ǉ����܂��B
		str& addint(int i){
			char buf[12];
			snprintf(buf, 12, "%d", i);
			add((const char*)buf);
			return *this;
		}
		/*���������񂪑��݂��Ȃ��ꍇ�� - 1��Ԃ��܂��B
		���݂���ꍇ�͔z��ԍ���Ԃ��܂��B
		*/
		int find(const char* to){
			if (strstr(st, to)==0)return -1;
			if (st == NULL) return -1;
			#pragma warning(disable:6387) 
			return strlen(st)-strlen(strstr(st,to));
		}
		/*�������������݂��Ȃ��ꍇ�� - 1��Ԃ��܂��B
		���݂���ꍇ�͔z��ԍ���Ԃ��܂��B
		*/
		int find(const char to) {
			for (unsigned int i = 0; i < strlen(st);i++) {
				if (st[i]==to) {
					return i;
				}
			}
			return -1;
		}
		/*�������������݂��Ȃ��ꍇ�� - 1��Ԃ��܂��B
		���݂���ꍇ�͔z��ԍ���Ԃ��܂��B(��납��T���܂�)*/
		int rfind(const char to) {
			for(int i = strlen(this->st) - 1; i >= 0;i--) {
				if (this->st[i]==to) {
					return i;
				}
			}
			return -1;
		}
		/*�؂蔲���ĕԂ��܂��B substr(�؂蔲���z��ԍ�,��������؂蔲����)
		��������0���n���ꂽ�ꍇ�؂蔲���z��ԍ�~�Ō�܂Ő؂蔲���܂��B
		*/
		const char* substr_c(unsigned int position,int count=0) {
			count == 0 ? count = strlen(this->st) - position:count;
			char* data = NULL;
			if (!_calloc(&data, count + position + 1), false)mem_err();
			for (unsigned int i = position,now=0; i < (count + position);i++,now++) {
				data[now] = this->st[i];
			}
			const char* d = {data};
			sfree(data);
			return d;
		}
		/*�؂蔲���ĕԂ��܂��B
		������~�������܂Ő؂蔲���܂�.
		*/
		const char* substr(char start,char finish) {
			int s = this->find(start);
			int f = this->rfind(finish);
			int count = f - s;
			return this->substr_c(s+1,count-1);
		}
		/*�����ƕ��������ւ��܂��B*/
		int replace(const char* from,const char* to){
			const int position = this->find(from);
			if (position == -1) { return -1; }
			const int len = strlen(from);
			replace_c(position,len,(char*)to);
			return 0;
		}
		/*�l���������܂��B*/
		virtual void clear() {
			sfree(st);
		}
		/*���͎擾
		mode:0 ���
		mode:1 �ǋL
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
		//�w�肵�������ŕ�����std::vector�ŕԂ��܂��B
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