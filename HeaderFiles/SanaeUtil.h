#pragma once
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <typeinfo>
/*
*Copyright 2021 SanaeProject.ALL Rights Reserved.
*/
#define SanaeUtil
namespace sanae {
	namespace util {
		/*
		�ϒ��z��ł��B
		����:
		����������ۂ͑������ɓ���������͂��Ă��������B
		��:
		sanae::util::arraylist<int> test;//ok
		����:test[0]�Ɠo�^�Ȃ��Ńf�[�^�������o����-1���Ԃ���܂��B

		sanae::util::arraylist<int> test={3,1,2,3};//ok
		sanae::util::arraylist<int> test={2,1,2,3};//1,2�̂ݓǂݎ����(�댯)
		sanae::util::arraylist<int> test={4,1,2,3};//�댯�Ȃ̂Ő�΂ɂ�߂Ă��������B

		sanae::util::arraylist<int> test={������,�l...};
		*/
		template <typename T>class arraylist {
		private:
			T* data = NULL;
			int datalen = 0;
		public:
			/*�v�f��Ԃ��܂��B
			�Ȃ��ꍇ��NULL��Ԃ��܂��B
			sanae::str�^�̏ꍇ��""��Ԃ��܂��B
			*/
			T operator [](int i) {
				if (i>=datalen) {
					if (strcmp(typeid(T).name(),"class sanae::str")==0) {
						return "";
					}
					return NULL;
				}
				return data[i];
			}
			/*
			�w�肵���z��ԍ��̒l����͂��ꂽ�ԍ��ɕύX���܂��B
			arraylist<int> test={3,1,2,3};
			test.chenge(1,9);//test[1]�̒l��9�ɂ���
			����:
			test[0]=1;
			test[1]=9;
			test[2]=3;
			*/
			void chenge(int number,T to) {
				if (number<datalen) {
					data[number] = to;
				}
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
					T* d1 = (T*)malloc(sizeof(T)*datalen);
					for (int i = 0,i2=0; i2 < datalen;i++) {
						if (i==number) {
							continue;
						}
						*(d1 + i2) = *(data + i);
						i2 += 1;
					}
					free(data);
					data = (T*)malloc(sizeof(T)*datalen);
					for (int i = 0; i < datalen;i++) {
						*(data + i) = *(d1 + i);
					}
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
					free(data);
				}
				if (count==0) {
					data = NULL;
				}
				else {
					data = (T*)malloc(sizeof(T) * count);
					if (data == NULL) { printf("�������m�ۂɎ��s���܂���"); exit(0); }
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
				T* d_c=(T*)malloc(sizeof(T)* datalen);
				for (int i = 0; i < datalen;i++) {
					*(d_c + i) = *(data+i);
				}
				free(data);
				datalen += 1;
				data = (T*)malloc(sizeof(T)*datalen);
				if(data==NULL){ printf("�������m�ۂɎ��s���܂���"); exit(0); }
				for (int i = 0; i < datalen-1;i++) {
					*(data + i) = *(d_c+i);
				}
				*(data + (datalen - 1)) = d;
				free(d_c);
			}
			/*�l�����ׂč폜���܂�*/
			void clear() {
				free(data);
				datalen = 0;
			}
			int find(T t) {
				for (unsigned int i = 0; i < (this->len());i++) {
					if (t==this->data[i]) {
						return i;
					}
				}
				return -1;
			}
			size_t len() {
				return this->datalen;
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
		/*�n���ꂽ�z��̒��ɉ��w�肵���l�����邩�Ԃ��܂�*/
		template<class T> int count(sanae::util::arraylist<T> array,T to) {
			int len = array.len();
			int c = 0;
			for (int i = 0; i < len; i++) {
				if (array[i] == to) {
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
			sanae::util::arraylist<K> keys;
			sanae::util::arraylist<D> datas;
			/*�ꎞ�ۑ��p�ϐ�*/
			K key_cp;
			D data_cp;
		public:
			map(K key, D data) :key_cp(key),data_cp(data){
				keys.add(key_cp);
				datas.add(data_cp);
			}
			//�v�f����Ԃ��܂�
			size_t len() { return keys.len(); }
			//�f�[�^��ǉ����܂�
			void add(K key,D data) {
				keys.add(key);
				datas.add(data);
			}
			//�f�[�^��������Ȃ��ꍇNULL,�܂���""��Ԃ��܂��B
			D get_data(K key) {
				int number=keys.find(key);
				if(number==-1){
					return NULL;
				}
				return datas[number];
			}
			//key�̃f�[�^���������܂��B
			void del_data(K key) {
				int number = keys.find(key);
				keys.del(number);
				datas.del(number);
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