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
		可変長配列です。
		注意:
		初期化する際は第一引数に入れる個数を入力してください。
		例:
		sanae::util::arraylist<int> test;//ok
		注意:test[0]と登録なしでデータを引き出すと-1が返されます。

		sanae::util::arraylist<int> test={3,1,2,3};//ok
		sanae::util::arraylist<int> test={2,1,2,3};//1,2のみ読み取られる(危険)
		sanae::util::arraylist<int> test={4,1,2,3};//危険なので絶対にやめてください。

		sanae::util::arraylist<int> test={入れる個数,値...};
		*/
		template <typename T>class arraylist {
		private:
			T* data = NULL;
			int datalen = 0;
		public:
			/*要素を返します。
			ない場合はNULLを返します。
			sanae::str型の場合は""を返します。
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
			指定した配列番号の値を入力された番号に変更します。
			arraylist<int> test={3,1,2,3};
			test.chenge(1,9);//test[1]の値を9にする
			結果:
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
			指定した配列番号を消去し一段下げます。
			arraylist<int> t={3,1,2,3};
			t.del(1);//t[1]を消去する
			結果:
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
			/*{入れる個数,値...}で入力してください
			{3(3個入れる),1,2,3}
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
					if (data == NULL) { printf("メモリ確保に失敗しました"); exit(0); }
					va_list var1;
					va_start(var1, count);
					for (int i = 0; i < count; i++) {
						*(data + i) = va_arg(var1, T);
					}
					va_end(var1);
					datalen = count;
				}
			}
			/*値を追加します*/
			void add(T d) {
				T* d_c=(T*)malloc(sizeof(T)* datalen);
				for (int i = 0; i < datalen;i++) {
					*(d_c + i) = *(data+i);
				}
				free(data);
				datalen += 1;
				data = (T*)malloc(sizeof(T)*datalen);
				if(data==NULL){ printf("メモリ確保に失敗しました"); exit(0); }
				for (int i = 0; i < datalen-1;i++) {
					*(data + i) = *(d_c+i);
				}
				*(data + (datalen - 1)) = d;
				free(d_c);
			}
			/*値をすべて削除します*/
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
		/*渡された配列の中に何個指定した値があるか返します*/
		template<class T>int count(T* array, int len, T to) {
			int c = 0;
			for (int i = 0; i < len; i++) {
				if (*(array + i) == to) {
					c += 1;
				}
			}
			return c;
		}
		/*渡された配列の中に何個指定した値があるか返します*/
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
		/*2種類の値を格納できます。*/
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
			//計測開始
			void start() {
				data = 0;
				t = time(NULL);
				localtime_s(&local, &t);
				second = local.tm_sec;
				min = local.tm_min;
				hour = local.tm_hour;
			}
			//int秒で返します
			int getdata() {
				return data;
			}
			//ストップして経過秒数を返します。
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
		入力されたキーとデータを格納します。
		get_data(キー);でデータを取得します。
		*/
		template<typename K, typename D>class map {
		private:
			sanae::util::arraylist<K> keys;
			sanae::util::arraylist<D> datas;
			/*一時保存用変数*/
			K key_cp;
			D data_cp;
		public:
			map(K key, D data) :key_cp(key),data_cp(data){
				keys.add(key_cp);
				datas.add(data_cp);
			}
			//要素数を返します
			size_t len() { return keys.len(); }
			//データを追加します
			void add(K key,D data) {
				keys.add(key);
				datas.add(data);
			}
			//データが見つからない場合NULL,または""を返します。
			D get_data(K key) {
				int number=keys.find(key);
				if(number==-1){
					return NULL;
				}
				return datas[number];
			}
			//keyのデータを消去します。
			void del_data(K key) {
				int number = keys.find(key);
				keys.del(number);
				datas.del(number);
			}
			//データをクリアします。
			void clear() {
				keys.clear();
				datas.clear();
			}
		};
	}
	/*random*/
	namespace random {
		bool seedset = false;
		/*乱数のシード値を設定する*/
		void setseed(unsigned long seed = (unsigned)time(0UL)) {
			srand(seed);
			seedset = true;
		}
		/*乱数シード値設定を初期化*/
		void seedreset() { seedset = false; };
		/*
		乱数生成:random(最低値,最高値,任意シード値);
		最低値～最高値までの値が出されます。
		任意シード値を使用すると次のシード値を入れても書き換えられないため、
		シード値を設定した場合はseedreset()関数をご使用ください。
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