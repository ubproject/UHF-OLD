#pragma once
#ifndef INCLUDE_GUARD_SANAEUTIL_H
#define INCLUDE_GUARD_SANAEUTIL_H
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdexcept>
#include <exception>
/*
*Copyright 2021 SanaeProject.ALL Rights Reserved.
*Author Usagi
*/
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
		template <typename T>class [[deprecated("この型はSanae::str型や配列型で使用するとバグが発生してしまています。原因が特定・改良できるまで使用しないでください")]] arraylist {
		private:
			T* data = NULL;
			int datalen = 0;
			//callocで確保します。 成功 true 失敗:false
			int _calloc(T** to, size_t count, bool dofree = true) {
				if (count == 0)return false;
				if (dofree)sfree(*to);
				*to = (T*)calloc(count, sizeof(T*));
				return *to == NULL ? false : true;
			}
			//freeした後ポインタをNULLにします
			template<typename T>
			void sfree(T d) { free(d); d = NULL; }
			//errorを返します
			[[noreturn]] void mem_err() {
				throw std::runtime_error("メモリ確保に失敗しました。");
			}
		public:
			/*要素を返します。
			ない場合はNULLを返します。
			*/
			T& operator [](int t) {
				if(datalen<=t){
					throw std::out_of_range("範囲外の値にアクセスしようとしました。");
				}
				return *(data + t);
			}
			//第一引数 配列 第二引数 要素数
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
			/*コピーコンストラクタ*/
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
			/*{入れる個数,値...}で入力してください
			{3(3個入れる),1,2,3}
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
			/*値を追加します*/
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
			/*値をすべて削除します*/
			void clear() {
				sfree(data);
				datalen = 0;
			}
			/*引数を検索して発見した場所の配列番号を返します。*/
			int find(T t) {
				for (unsigned int i = 0; i < (this->len());i++) {
					if (t==this->data[i]) {
						return i;
					}
				}
				return -1;
			}
			/*要素数を返します。*/
			size_t len() {
				return this->datalen;
			}
			/*配列を第一引数個確保し0または第二引数で埋めます。*/
			void secured(int l,T d=NULL) {
				for (int i = 0; i < l;i++) {
					this->add(d);
				}
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
			std::vector<K> keys;
			std::vector<D> datas;
			/*一時保存用変数*/
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
			//要素数を返します
			size_t len() { return keys.len(); }
			//見つかった場合true 見つからなかった場合false
			bool find(D data) {
				auto found = std::find(datas.cbegin(),datas.cend(),data);
				if (found!=datas.cend()) {
					return true;
				}
				return false;
			}
			/*データを追加します。
			返り値:成功:成功した配列番号
			失敗:-1
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
			//データが見つからない場合NULLを返します。
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
			//keyのデータを消去します。
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
#endif