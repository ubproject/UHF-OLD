#include <stdio.h>
#include "Sanae.h"
int main()
{
	/*Sanae::str型*/
		sanae::str test;
		//代入
		test = "Sanae";
		//追加(文字列)
		test.add("Projec");
		//追加(char)
		test.addchr('t');
		//追加(int)
		test.addint(2021);
		//出力
		printf(test);//SanaeProject2021
		printf("%s\n",test.c_str());//SanaeProject2021
		//特定の文字列の位置を返します。
		test.find("P");//5
		//第一引数の文字列を第二引数の文字列にすり替えます。
		test.replace("Sanae","PPPtal");//PPPtalProject2021
		//文字列をすべて消去します。
		test.clear();
	/*Sanae::Util*/
		/*arraylist*/
			sanae::util::arraylist<int> test2;
			//12を追加します
			test2.add(12);
			//配列番号0の値を0に変更。
			test2.chenge(0,0);
			//値が0の場所を返します。
			test2.find(0);//0
			//要素数を返します。
			test2.len();//1
			//12こ確保します。
			test2.secured(12);
			int test2_0[12];
			//配列の値をtest2_0の配列にコピー
			test2.to_array(test2_0,sizeof(test2_0));
			//test2[0]を消去。
			test2.del(0);
		/*pair*/
			sanae::util::pair<sanae::str, int> test3 = {"99",99};
			test3.first();//"99"
			test3.second();//99
			test3.set("22",22);
		/*map*/
			sanae::util::map<sanae::str, int> test4 = {"0",0};
			//追加します。
			test4.add("1",1);
			//データを取得
			test4.get_data("1");//1
			//"0"を消去します。
			test4.del_data("0");
			//要素数を取得します。
			test4.len();
		/*clock*/
			sanae::util::clock time;
			//スタート
			time.start();
			//ストップ
			time.stop();
			//経過秒数を取得します。
			time.getdata();
	/*Sanae::Math*/
		int data1 = 2021;
		//桁数を返します
		sanae::math::digit(data1);//3
		//ルートを返します。
		sanae::math::root(data1); //44.955534
		//10の何乗で整数になるかを返します。
		sanae::math::little_digit(0.001);//3


		int array1[6] = { 1,2,3,4,5,6 };
		//平均値を返します。
		sanae::math::array_average(6,array1);  //3.5
		//標準偏差を返します。
		sanae::math::array_deviation(6,array1);//1.732051
		//配列の最小値を返します。
		sanae::math::min(6,array1);            //0


		int array2[6] = { 6,5,4,3,2,1 };
		//相関係数を返す
		sanae::math::correlation(array1,array2,6);//-0.545275
		//二次元2データのユークリッド距離を返します
		sanae::math::euclidean(array1, array2, 6);//34.176015


		sanae::util::arraylist<int> test1;
		//素数の組み合わせを返します。
		test1 = sanae::math::division_number(data1);//43,47
		//偶数か判定します。
		sanae::math::is_even(data1);       //false
		//素数か否か返します。
		sanae::math::is_primenumber(data1);//false
		//ピタゴラスの定理を使用し高さと横の長さを入力することで斜辺の長さを返します。
		sanae::math::triangle(3,6);      //6.708204
}