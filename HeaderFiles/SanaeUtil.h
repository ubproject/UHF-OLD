#pragma once
#ifndef INCLUDE_GUARD_SANAEUTIL_H
#define INCLUDE_GUARD_SANAEUTIL_H
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <vector>
#include <stdexcept>
#include <exception>

namespace sanae {
	/*-----------------------------------------------
	* Project:SanaeProject-UsefulHeadersProject
	* Dev:SanaeProject
	* Function:
	This header have many utility programs. 
	*Copyright 2021 SanaeProject.ALL Rights Reserved.
	-----------------------------------------------*/
	namespace util {
		//�␔�𗘗p�����o�C�i���ŕ\���A�v�Z���܂��B(int)
		class binary {
		private:
			bool minus_binary = false;
			std::vector<bool> data;
			sanae::str data_binary = "";
			//complement1(Inversion)
			void complement_1() {
				for (unsigned int i = 0; i < data.size(); i++)data[i] = data[i] ? false : true;
			}
			//complement2(plus1)
			void complement_2() {
				bool advance = true;
				for (int i = data.size() - 1; i >= 0;i--) {
					if (data[i]&&advance) {
						data[i] = false;
						advance = true;
					}
					else if(advance) {
						data[i] = true;
						advance = false;
						break;
					}
				}
			}
			//Convert decimal to binary
			void to_binary(int d) {
				minus_binary = false;
				if (d < 0) {
					minus_binary = true;
					d *= -1;
				}
				else {
					minus_binary = false;
				}
				while (1) {
					data.push_back(d%2);
					d= d / 2;
					if (d==1||d==0) {
						data.push_back(d);
						break;
					}
				}
				for (unsigned int i = data.size(); i < 3;i++) {
					data.push_back(0);
				}
				data.push_back(0);
				std::reverse(data.begin(),data.end());
				if (minus_binary) {
					complement_1();
					complement_2();
				}
			}
			//Convert binary to decimal
			int to_decimal() {
				bool minus = false;
				if (data[0]) {
					complement_1();
					complement_2();
					minus = true;
				}
				int data_decimal = 0;
				for (int i = data.size() - 1,count=0; i >= 0;i--,count++) {
					int plus_data = 0;
					if (data[i]) {
						if (count==0) {
							plus_data = 1;
						}
						else {
							plus_data = 1;
							for (int i = 0; i < count;i++) {
								plus_data *= 2;
							}
						}
						data_decimal += plus_data;
					}
				}
				if (minus) {
					data_decimal *= -1;
				}
				return data_decimal;
			}
		public:
			//Pass binary value.
			const char* binary_num() {
				for (int i:data) {
					data_binary.addint(i);
				}
				return data_binary.c_str();
			}
			//Operator
			bool operator [](unsigned int count) {
				if ((data.size()-1)<count) {
					throw std::runtime_error("�͈͊O�̒l�ɃA�N�Z�X���悤�Ƃ��܂����B");
				}
				return data[count];
			}
			void operator =(const binary& t) {
				data.erase(data.begin(), data.end());
				for (int i : t.data) {
					data.push_back(i);
				}
				if (t.minus_binary) {
					complement_1();
					complement_2();
				}
			}
			int operator +(int d) {
				int s = to_decimal() + d;
				return s;
			}
			int operator +(binary& d) {
				int s = to_decimal() + d.decimal();
				return s;
			}
			int operator -(int d) {
				int s = to_decimal() - d;
				return s;
			}
			int operator -(binary& d) {
				int s = to_decimal() - d.decimal();
				return s;
			}
			//Constructor
			binary(int d) {
				to_binary(d);
			}
			//Copyconstructor
			binary(const binary & t) {
				data.erase(data.begin(), data.end());
				for (int i : t.data) {
					data.push_back(i);
				}
				if (t.minus_binary) {
					complement_1();
					complement_2();
				}
			}
			//Destructor
			~binary() {
				data.~vector();
				minus_binary = false;
			}
			//Pass decimal value.
			int decimal() {
				return to_decimal();
			}

		};
		//sanae::util::arraylist<int> test={������,�l...};
		template<typename T> class [[deprecated("���̌^��Sanae::str�^��z��^�Ŏg�p����ƃo�O���������Ă��܂Ă��܂��B\n����������E���ǂł���܂Ŏg�p���Ȃ��ł��������B\n�g�p����ꍇ��NOT_ERROR_SANAE���`���Ă��������B")]] arraylist {
		private:
			T* data = NULL;
			int datalen = 0;
			//calloc�Ŋm�ۂ��܂��B ���� true ���s:false
			int _calloc(T** to, size_t count, bool dofree = true) {
				if (count == 0)return false;
				if (dofree)sfree(*to);
				*to = (T*)calloc(count, sizeof(T*));
				return *to == NULL ? false : true;
			}
			//free������|�C���^��NULL�ɂ��܂�
			template<typename T>
			void sfree(T d) { free(d); d = NULL; }
			//error��Ԃ��܂�
			[[noreturn]] void mem_err() {
				throw std::runtime_error("�������m�ۂɎ��s���܂����B");
			}
		public:
			/*�v�f��Ԃ��܂��B
			�Ȃ��ꍇ��NULL��Ԃ��܂��B
			*/
			T& operator [](int t) {
				if(datalen<=t){
					throw std::out_of_range("�͈͊O�̒l�ɃA�N�Z�X���悤�Ƃ��܂����B");
				}
				return *(data + t);
			}
			//������ �z�� ������ �v�f��
			int to_array(T* arr,size_t count) {
				if ((this->len())>=count) {
					for (int i = 0; i < (this->len());i++) {
						*(arr+i) = *(data + i);
					}
					return 1;
				}
				return -1;
			}
			/*
			�w�肵���z��ԍ�����������i�����܂��B
			arraylist<int> t={3,1,2,3};
			t.del(1);//t[1]����������
			����:
			t[0]=1
			t[1]=3
			*/
			void del(int number) {	
				if (number<datalen) {
					datalen -= 1;
					T* d1 = NULL;
					if (!_calloc(&d1, datalen, false))mem_err();
					for (int i = 0,i2=0; i2 < datalen;i++) {
						if (i==number) {
							continue;
						}
						*(d1 + i2) = *(data + i);
						i2 += 1;
					}
					sfree(data);
					data = NULL;
					if (!_calloc(&data, datalen, false))mem_err();
					for (int i = 0; i < datalen;i++) {
						*(data + i) = *(d1 + i);
					}
				}
			}
			~arraylist() {
				this->clear();
			}
			/*�R�s�[�R���X�g���N�^*/
			arraylist(const arraylist& d) {
				this->clear();
				if (!_calloc(&data, d.datalen, false))mem_err();
				for (int i = 0; i < d.datalen; i++) {
					this->data[i] = d.data[i]; 
				}
			}
			arraylist() {
				data = NULL;
				datalen = 0;
			}
			/*{������,�l...}�œ��͂��Ă�������
			{3(3�����),1,2,3}
			*/
			arraylist(int count,T...) {
				if (datalen!=0) {
					sfree(data);
				}
				if (count==0) {
					sfree(data);
				}
				else {
					if (!_calloc(&data, count, false))mem_err();
					va_list var1;
					va_start(var1, count);
					for (int i = 0; i < count; i++) {
						*(data + i) = va_arg(var1, T);
					}
					va_end(var1);
					datalen = count;
				}
			}
			/*�l��ǉ����܂�*/
			void add(T d) {
				if (datalen == 0) {
					datalen += 1;
					data = NULL;
					if (!_calloc(&data, datalen, false))mem_err();
					data[datalen - 1] = d;
				}else {
					T* d_c = NULL;
					if (!_calloc(&d_c, datalen, false))mem_err();
					for (int i = 0; i < datalen; i++) {
						*(d_c + i) = *(data + i);
					}
					sfree(data);
					datalen += 1;
					data = NULL;
					if (!_calloc(&data, datalen, false))mem_err();
					for (int i = 0; i < datalen - 1; i++) {
						*(data + i) = *(d_c + i);
					}
					*(data + (datalen - 1)) = d;
					sfree(d_c);
				}
			}
			/*�l�����ׂč폜���܂�*/
			void clear() {
				sfree(data);
				datalen = 0;
			}
			/*�������������Ĕ��������ꏊ�̔z��ԍ���Ԃ��܂��B*/
			int find(T t) {
				for (unsigned int i = 0; i < (this->len());i++) {
					if (t==this->data[i]) {
						return i;
					}
				}
				return -1;
			}
			/*�v�f����Ԃ��܂��B*/
			size_t len() {
				return this->datalen;
			}
			/*�z���������m�ۂ�0�܂��͑������Ŗ��߂܂��B*/
			void secured(int l,T d=NULL) {
				for (int i = 0; i < l;i++) {
					this->add(d);
				}
			}
		};
		/*�n���ꂽ�z��̒��ɉ��w�肵���l�����邩�Ԃ��܂�*/
		template<class T>int count(T* array, int len, T to) {
			int c = 0;
			for (int i = 0; i < len; i++) {
				if (*(array + i) == to) {
					c += 1;
				}
			}
			return c;
		}
		/*2��ނ̒l���i�[�ł��܂��B*/
		template<class T1, class T2>class pair{
		private:
			T1 t1;
			T2 t2;
		public:
			bool operator ==(sanae::util::pair<T1, T2> t) {
				sanae::util::pair<T1, T2>* te = &t;
				if (te->first() == this->first() && te->second() == this->second())return true;
				return false;
			}
			void operator =(sanae::util::pair<T1, T2> t) {
				sanae::util::pair<T1, T2>* p = &t;
				this->t1 = p->first();
				this->t2 = p->second();
			}
			pair(T1 d1, T2 d2) :t1(d1), t2(d2) {};
			pair() { t1 = NULL; t2 = NULL; };
			void set(T1 d1, T2 d2) { t1 = d1; t2 = d2; }
			T1 first() { return t1; }
			T2 second() { return t2; }
		};
		/*time*/
		class clock {
		private:
			time_t t=0;
			struct tm local = {};
			int second = 0;
			int min = 0;
			int hour = 0;
			int data = 0;
		public:
			//�v���J�n
			void start() {
				data = 0;
				t = time(NULL);
				localtime_s(&local, &t);
				second = local.tm_sec;
				min = local.tm_min;
				hour = local.tm_hour;
			}
			//int�b�ŕԂ��܂�
			int getdata() {
				return data;
			}
			//�X�g�b�v���Čo�ߕb����Ԃ��܂��B
			int stop() {
				t = time(NULL);
				localtime_s(&local, &t);
				int end_second = local.tm_sec;
				int end_min = local.tm_min;
				int end_hour = local.tm_hour;
				data= (end_second - second) + ((end_min - min) * 60) + (((end_hour - hour) * 60) * 60);
				return data;
			}
		};
		/*
		���͂��ꂽ�L�[�ƃf�[�^���i�[���܂��B
		get_data(�L�[);�Ńf�[�^���擾���܂��B
		*/
		template<typename K, typename D>class map {
		private:
			std::vector<K> keys;
			std::vector<D> datas;
			/*�ꎞ�ۑ��p�ϐ�*/
			K key_cp;
			D data_cp;
		public:
			map(K key, D data) :key_cp(key),data_cp(data){
				keys.clear();
				datas.clear();
				keys.push_back(key_cp);
				datas.push_back(data_cp);
			}
			map() {}
			~map() {
				this->clear();
			}
			//�v�f����Ԃ��܂�
			size_t len() { return keys.len(); }
			//���������ꍇtrue ������Ȃ������ꍇfalse
			bool find(D data) {
				auto found = std::find(datas.cbegin(),datas.cend(),data);
				if (found!=datas.cend()) {
					return true;
				}
				return false;
			}
			/*�f�[�^��ǉ����܂��B
			�Ԃ�l:����:���������z��ԍ�
			���s:-1
			*/
			int add(K key,D data) {
				auto found = std::find(keys.cbegin(), keys.cend(), key);
				if (found == keys.cend()) {
					keys.push_back(key);
					datas.push_back(data);
					return keys.size() - 1;
				}else {
					return -1;
				}
			}
			//�f�[�^��������Ȃ��ꍇNULL��Ԃ��܂��B
			D get_data(K key) {
				auto found = std::find(keys.cbegin(), keys.cend(), key);
				if (found == keys.cend()) {
					return NULL;
				}
				int number = 0;
				for (int i = 0; i < keys.size();i++) {
					if (key==keys[i]) {
						number = i;
						break;
					}
				}
				return datas[number];
			}
			//key�̃f�[�^���������܂��B
			void del_data(K key) {
				auto found = std::find(keys.cbegin(), keys.cend(), key);
				if (found != keys.cend()) {
					int number = 0;
					for (int i = 0; i < keys.size(); i++) {
						if (key == keys[i]) {
							number = i;
							break;
						}
					}
					keys.erase(keys.begin()+number);
					datas.erase(datas.begin()+number);
				}
			}
			//�f�[�^���N���A���܂��B
			void clear() {
				keys.clear();
				datas.clear();
			}
		};
	}
	/*random*/
	namespace random {
		bool seedset = false;
		/*�����̃V�[�h�l��ݒ肷��*/
		void setseed(unsigned long seed = (unsigned)time(0UL)) {
			srand(seed);
			seedset = true;
		}
		/*�����V�[�h�l�ݒ��������*/
		void seedreset() { seedset = false; };
		/*
		��������:random(�Œ�l,�ō��l,�C�ӃV�[�h�l);
		�Œ�l�`�ō��l�܂ł̒l���o����܂��B
		�C�ӃV�[�h�l���g�p����Ǝ��̃V�[�h�l�����Ă������������Ȃ����߁A
		�V�[�h�l��ݒ肵���ꍇ��seedreset()�֐������g�p���������B
		*/
		int random(int min, int max, unsigned long seed = 0) {
			if (seed != 0 && !seedset)setseed(seed);
			if (!seedset)setseed();
			max += 1;
			if (min > max || min == max) {
				return -1;
			}
			int ran = rand() % max;
			if (ran < min) {
				ran = ran + min;
				if (ran > max) {
					ran = ran - (ran - max);
				}
			}
			return ran;
		}
	}
}
#endif