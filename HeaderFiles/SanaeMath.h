#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define SanaeMath
namespace sanae {
	/*
	*Copyright 2021 SanaeProject.ALL Rights Reserved.
	*/
	/*数学関係の関数群です。*/
	namespace math {
		/*桁数を返す*/
		unsigned int digit(int t) {
			unsigned int digit = 0;
			for (int i = 1;; i = i * 10) {
				if ((t / i) != 0 || (t / i) > 0) { digit += 1; }
				else break;
			}
			return digit;
		}
		/* ニュートン法を利用して平方根の計算を行う */
		double root(long double t) {
			/*引用:https://schlaf.ltd/programming/c/c-square-root/ */
			if (t == 0) {return 0;
			}else if (t == 1) {return 1;}
			double y=0,x=1;
			while (1) {
				x = x - (x * x - t) / (2 * x);
				y = x * x - t;
				if ((y <= 0.00000001) && (y >= -0.00000001)) {
				break;
				}
			}
			return x;
		}
		/*小数点は何桁あるかを返します。*/
		int little_digit(double t) {
			if (t==(int)t)return 0;
			for (long i = 10,i2=1;;i=i*10,i2++) {
				if ((t*i)>0&&(t*i)-(int)(t*i)==0) {
					return i2;
				}
			}
		}
		/*3平方の定理で求める*/
		template<class T>
		double triangle(T a,T b,bool calculation_root=true) {
			double answer = 0;
			if (calculation_root) {
					answer = sanae::math::root(((long double)a*(long double)a)+((long double)b*(long double)b));
			}else{
				answer = ((long double)a * (long double)a) + ((long double)b * (long double)b);
			}
			return answer;
		}
		//平均値を返す
		template<typename T>
		double array_average(int count, T* t) {
			T data = 0;
			for (int i = 0; i < count; i++) {
				data += *(t + i);
			}
			return data / count;
		}
		//標準偏差を返す
		template<typename T>
		double array_deviation(int count, T* datas,bool to_distributed=false) {
			T average_value = array_average(count,datas);
			for (int i = 0; i < count; i++) {
				*(datas + i) = *(datas+ i) - average_value;
				double s = *(datas + i);
				*(datas + i) = s * s;
			}
			double v = 0;
			if (!to_distributed) {
				v= root(array_average(count, datas));
			}
			else {
				v = array_average(count, datas);
			}
			return v;
		}
		/*偶数か判定します。*/
		bool is_even(int i) {
			if (i%2==0)return true;
			return false;
		}
		/*素数判定を返します。*/
		bool is_primenumber(int i) {
			if (i <= 1) {
				return false;
			}
			else if (i == 2) {
				return true;
			}
			if (i % 2 == 0) {
				return false;
			}
			int i2 = (int)sanae::math::root(i) + 1;
			for (int i1=3;i1<i2;i1+=2){
				if (i%i1==0) {
					return false;
				}
			}
			return true;
		}
		/*N次元の2個のデータのユークリッド距離を返します。*/
		template<typename T>
		double euclidean(T data1[], T data2[]) {
			sanae::util::arraylist<T> datas = { 0,0 };
			if (sizeof(data1) == sizeof(data2)) {
				for (unsigned int i = 0; i < (sizeof(data1)/sizeof(int)); i++) {
					datas.add(data1[i] - data2[i]);
				}
				double d = 0;
				for (unsigned int i = 0; i < datas.len(); i++) {
					d += datas[i] * datas[i];
				}
				datas.clear();
				d = sanae::math::root(d);
				return d;
			}
			else {
				return 0.0;
			}
		}
#ifdef SanaeUtil
		/*渡された配列の最小値を返します*/
		template<typename T>
		T min(size_t size, T* data) {
			size = size / sizeof(T);
			sanae::util::arraylist<T> data_cpy = { 0,0 };
			T min = 0;
			for (int i = 0; i < size; i++) {
				data_cpy.add(*(data + i));
				if (i == 0) { min = *(data + i); }
				if (i > 0 && min > *(data + i)) {
					min = *(data + i);
				}
			}
			data_cpy.clear();
			return min;
		}
		/*渡されたarraylistの最小値を返します。*/
		template<typename T>
		T min(size_t len, sanae::util::arraylist<T> data) {
			sanae::util::arraylist<T> data_cpy = { 0,0 };
			T min = 0;
			for (unsigned int i = 0; i < len; i++) {
				data_cpy.add(data[i]);
				if (i == 0) { min = data[i]; }
				if (i > 0 && min > data[i]) {
					min = data[i];
				}
			}
			data_cpy.clear();
			return min;
		}
		/*N次元の2個のデータのユークリッド距離を返します。*/
		template<typename T>
		double euclidean(sanae::util::arraylist<T> data1,sanae::util::arraylist<T> data2) {
			sanae::util::arraylist<T> datas = {0,0};
			if (data1.len()==data2.len()) {
				for (int i = 0; i < data1.len();i++) {
					datas.add(data1[i]-data2[i]);
				}
				double d=0;
				for (int i = 0; i < datas.len();i++) {
					d += datas[i] * datas[i];
				}
				datas.clear();
				data1.clear();
				data2.clear();
				d = sanae::math::root(d);
				return d;
			}
			else {
				return 0.0;
			}
		}
		/*掛け算を返します。
		第二引数の値を入れることで指定した値から掛け算を検索できます。
		*/
		sanae::util::pair<int, int> division_number_parts(int root, int startpoint = 2) {
			if (startpoint<=1) {
				startpoint = 2;
			}
			if (is_primenumber(root)) {
				sanae::util::pair<int, int> an = {root,0};
				return an;
			}
			sanae::util::pair<int, int> answer = {0,0};
			if (root == 4) { answer = { 2,2 }; return answer; }
			for (int i = startpoint; i <= root; i++) {
				if (is_primenumber(i)) {
					if (little_digit(root/i) == 0) {
						if ((root/i)*i==root) {
							answer = { i,root / i };
							return answer;
						}
					}
				}
			}
			return answer;
		}
		/*入力された値の素数の組み合わせを返します*/
		sanae::util::arraylist<int> division_number(int number) {
			sanae::util::arraylist<int> answer = {0,0};
			if (is_primenumber(number)) {
				answer.add(number);
				return answer;
			}
			sanae::util::pair<int, int> test = {0,number};
			for (;;) {
				test=division_number_parts(test.second());
				answer.add(test.first());
				if (is_primenumber(test.second())) {
					answer.add(test.second());
					break;
				}
				if (test.second()==0) {
					break;
				}
			}
			return answer;
		}
#endif
#ifdef SanaeStr
		/*平均値を返す
		average("int or double",入れる個数,値...);
		例:
		average("int",3(3個入れる),1,2,3);
		*/
		double average(sanae::str type, int count, ...) {
			va_list var1;
			va_start(var1, count);
			double data = 0;
			for (int i = 0; i < count; i++) {
				if (type == "int") {
					data += va_arg(var1, int);
				}
				else if (type == "double") {
					data += va_arg(var1, double);
				}
				else return -1;
			}
			data = data / count;
			va_end(var1);
			return data;
		}
		/*標準偏差を返す
		* sanae::deviation("型",値の個数,値...);
		test code:
		sanae::deviation("int",4,1,2,3,4);
		//1.118034
		sanae::deviation("double",4,0.1,0.2,0.3,0.4);
		//0.111803
		*/
		double deviation(sanae::str type, int count, ...) {
			va_list var1;
			va_start(var1, count);
			double* datas = (double*)malloc(sizeof(double) * count);
			if (datas == NULL) {
				return -1;
			}
			for (int i = 0; i < count; i++) {
				if (type == "double") {
					*(datas + i) = va_arg(var1, double);
				}
				else if (type == "int") {
					*(datas + i) = va_arg(var1, int);
				}
				else {
					return -1;
				}
			}
			va_end(var1);
			double average_value = array_average(count, datas);
			for (int i = 0; i < count; i++) {
				*(datas + i) = *(datas + i) - average_value;
				*(datas + i) = *(datas + i) * *(datas + i);
			}
			double v = root(array_average(count, datas));
			free(datas);
			return v;
		}
#endif
	}
	namespace util {
		/*Arraylistを小さい順に整列させます。*/
		template<typename T>
		void align(sanae::util::arraylist<T> *data) {
			sanae::util::arraylist<T> d = { 0, 0 };
			size_t size = data->len();
			for (unsigned int i = 0; i < size; i++) {
				d.add((*data)[i]);
			}
			data->clear();
			*data ={0,0};
			for (unsigned int point = 0; point < size; point++) {
				(*data).add(sanae::math::min(d.len(), d));
				d.del(d.find((*data)[point]));
			}
			d.clear();
		}
	}
}