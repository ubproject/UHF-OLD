#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define SanaeMath
namespace sanae {
	/*
	*Copyright 2021 SanaeProject.ALL Rights Reserved.
	* Author Usagi
	*/
	/*���w�֌W�̊֐��Q�ł��B*/
	namespace math {
		/*������Ԃ�*/
		unsigned int digit(int t) {
			unsigned int digit = 0;
			for (int i = 1;; i = i * 10) {
				if ((t / i) != 0 || (t / i) > 0) { digit += 1; }
				else break;
			}
			return digit-1;
		}
		/* �j���[�g���@�𗘗p���ĕ������̌v�Z���s�� */
		double root(long double t) {
			/*���p:https://schlaf.ltd/programming/c/c-square-root/ */
			if (t == 0) {
				return 0;
			}
			else if (t == 1) { return 1; }
			double y = 0, x = 1;
			while (1) {
				x = x - (x * x - t) / (2 * x);
				y = x * x - t;
				if ((y <= 0.00000001) && (y >= -0.00000001)) {
					break;
				}
			}
			return x;
		}
		/*�����_�͉������邩��Ԃ��܂��B*/
		int little_digit(double t) {
			if (t == (int)t)return 0;
			for (long i = 10, i2 = 1;; i = i * 10, i2++) {
				if ((t * i) > 0 && (t * i) - (int)(t * i) == 0) {
					return i2;
				}
			}
		}
		/*3�����̒藝�ŋ��߂�*/
		template<class T>
		double triangle(T a, T b, bool calculation_root = true) {
			double answer = 0;
			if (calculation_root) {
				answer = sanae::math::root(((long double)a * (long double)a) + ((long double)b * (long double)b));
			}
			else {
				answer = ((long double)a * (long double)a) + ((long double)b * (long double)b);
			}
			return answer;
		}
		//���ϒl��Ԃ�
		template<typename T>
		double array_average(int count, T* t) {
			T data = 0;
			for (int i = 0; i < count; i++) {
				data += *(t + i);
			}
			return data / count;
		}
		//�W���΍���Ԃ�
		template<typename T>
		double array_deviation(int count, T* datas, bool to_distributed = false) {
			T average_value = array_average(count, datas);
			for (int i = 0; i < count; i++) {
				*(datas + i) = *(datas + i) - average_value;
				double s = *(datas + i);
				*(datas + i) = s * s;
			}
			double v = 0;
			if (!to_distributed) {
				v = root(array_average(count, datas));
			}
			else {
				v = array_average(count, datas);
			}
			return v;
		}
		/*���������肵�܂��B*/
		bool is_even(int i) {
			if (i % 2 == 0)return true;
			return false;
		}
		/*�f�������Ԃ��܂��B*/
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
			for (int i1 = 3; i1 < i2; i1 += 2) {
				if (i % i1 == 0) {
					return false;
				}
			}
			return true;
		}
		/*N������2�̃f�[�^�̃��[�N���b�h������Ԃ��܂��B*/
		template<typename T>
		double euclidean(T* data1, T* data2, int count) {
			sanae::util::arraylist<T> datas = { 0,0 };
			for (unsigned int i = 0; i < count; i++) {
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
#ifdef SanaeUtil
		/*���֌W����Ԃ��܂��B*/
		template<typename T>
		double correlation(T* d1, T* d2, int count) {
			double data1 = sanae::math::array_average(count, d1);
			double data2 = sanae::math::array_average(count, d2);
			double* a1 = (double*)malloc(sizeof(double) * count);
			double* a2 = (double*)malloc(sizeof(double) * count);
			if (a1 == NULL || a2 == NULL) { printf("\n�������̊m�ۂɎ��s���܂����B\n"); exit(0); }
			//�΍��ς��o��
			sanae::util::arraylist<double> a3;
			//�΍����o��d1,d2
			for (int i = 0; i < count; i++) { a1[i] = (d1[i] - data1); }
			for (int i = 0; i < count; i++){a2[i] = (d2[i] - data2);}
			//�΍��̐ς��o��
			for (int i = 0; i < count; i++) { a3.add(a1[i] * a2[i]); }
			double _d = 0;
			for (int i = 0; i < a3.len(); i++) { _d += a3[i]; }
			free(a1); free(a2);
			_d = _d / a3.len();
			a3.clear();
			data1 = sanae::math::array_deviation(count, d1);
			data2 = sanae::math::array_deviation(count, d2);
			return _d / (data1 * data2);
		}
		/*�n���ꂽ�z��̍ŏ��l��Ԃ��܂�*/
		template<typename T>
		T min(int count, T* data) {
			sanae::util::arraylist<T> data_cpy = { 0,0 };
			T min = 0;
			for (int i = 0; i < count; i++) {
				data_cpy.add(*(data + i));
				if (i == 0) { min = *(data + i); }
				if (i > 0 && min > *(data + i)) {
					min = *(data + i);
				}
			}
			data_cpy.clear();
			return min;
		}
		/*�n���ꂽarraylist�̍ŏ��l��Ԃ��܂��B*/
		template<typename T>
		T min(int count, sanae::util::arraylist<T> data) {
			sanae::util::arraylist<T> data_cpy = { 0,0 };
			T min = 0;
			for (unsigned int i = 0; i < count; i++) {
				data_cpy.add(data[i]);
				if (i == 0) { min = data[i]; }
				if (i > 0 && min > data[i]) {min = data[i];}
			}
			data_cpy.clear();
			return min;
		}
		/*N������2�̃f�[�^�̃��[�N���b�h������Ԃ��܂��B*/
		template<typename T>
		double euclidean(sanae::util::arraylist<T> data1, sanae::util::arraylist<T> data2) {
			sanae::util::arraylist<T> datas = { 0,0 };
			if (data1.len() == data2.len()) {
				for (int i = 0; i < data1.len(); i++) {datas.add(data1[i] - data2[i]);}
				double d = 0;
				for (int i = 0; i < datas.len(); i++) {d += datas[i] * datas[i];}
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
		/*�|���Z��Ԃ��܂��B
		�������̒l�����邱�ƂŎw�肵���l����|���Z�������ł��܂��B
		*/
		sanae::util::pair<int, int> division_number_parts(int root, int startpoint = 2) {
			if (startpoint <= 1) {
				startpoint = 2;
			}
			if (is_primenumber(root)) {
				sanae::util::pair<int, int> an = { root,0 };
				return an;
			}
			sanae::util::pair<int, int> answer = { 0,0 };
			if (root == 4) { answer = { 2,2 }; return answer; }
			for (int i = startpoint; i <= root; i++) {
				if (is_primenumber(i)) {
					if (little_digit(root / i) == 0) {
						if ((root / i) * i == root) {
							answer = { i,root / i };
							return answer;
						}
					}
				}
			}
			return answer;
		}
		/*���͂��ꂽ�l�̑f���̑g�ݍ��킹��Ԃ��܂�*/
		sanae::util::arraylist<int> division_number(int number) {
			sanae::util::arraylist<int> answer = { 0,0 };
			if (is_primenumber(number)) {
				answer.add(number);
				return answer;
			}
			sanae::util::pair<int, int> test = { 0,number };
			for (;;) {
				test = division_number_parts(test.second());
				answer.add(test.first());
				if (is_primenumber(test.second())) {
					answer.add(test.second());
					break;
				}
				if (test.second() == 0) {
					break;
				}
			}
			return answer;
		}
#endif
	}
	namespace util {
		/*Arraylist�����������ɐ��񂳂��܂��B*/
		template<typename T>
		void align(sanae::util::arraylist<T>* data) {
			sanae::util::arraylist<T> d = { 0, 0 };
			size_t size = data->len();
			for (unsigned int i = 0; i < size; i++) {
				d.add((*data)[i]);
			}
			data->clear();
			*data = { 0,0 };
			for (unsigned int point = 0; point < size; point++) {
				data->add(sanae::math::min(d.len(), d));
				d.del(d.find((*data)[point]));
			}
			d.clear();
		}
	}
}