# ちょっと便利なファイルをつくる！
今回作ったやつはできるだけポインタを使用しました！<br>
そのせいでめんどくさいことになったりしましたけど、、、<br>
一応使ってみてバグはなかったけどたぶんポインタで<br>みすってるからきおつけてください！<br>
# Sanae::str型関数
	/*char*型の値を変えす。*/
	変数.c_str();
	変数(const char*型との互換性があるためprintf(変数)が使用できます。)
	
	/*文字列を追加する*/
	変数.add("追加する文字");
	変数+="追加する文字";
	
	/*int型の値を追加する*/
	addint(値);
	変数+=値;
	
	/*文字列を検索する*/
	変数.find("検索したい文字列");
	
	/*文字列を入れ替える*/
	変数.replace("切り替える文字列","切り替えたい文字列");
	
	/*確保しているメモリを開放する*/
	変数.clear();//確保していたメモリが解放される。
# TestCode(Str型)
 	#include <stdio.h>
	#include "Sanae.h"
	int main(){
	sanae::str test = "SanaeProject";//定義<br>
	sanae::str test2 = "Sanae San";<br>

	test2.replace(" San","Project");//文字列を入れ替える
	
	test.addint(2021);//int型を挿入
	test2.addint(2021);

	if (test==test2) {//比較 TRUE
		printf("同じ\n");
	}

	test2.add("Plus");//Plusを挿入

	if (test!=test2) {//比較 TRUE
		printf("違う\n");
	}
	printf(test);
	printf(test2);
	test.clear();//メモリの開放
	test2.clear();//メモリの開放
	/*結果:
	同じ
	違う
	SanaeProject2021SanaeProject2021Plus
	*/
	return 0;
 	}
 # その他関数(SanaeMath.h)
	sanae::math::digit(int);//引数(int)の桁数を返します。
	
	sanae::math::little_digit(double);//小数点の桁巣を返します。
	
	sanae::math::root(double);//引数(double)の平方根の計算を行います。
	
	sanae::math::triangle(T,T,bool);//ピタゴラスの定理を使用し斜辺の長さを返します。
	//boolは√の計算をして返します。falseの場合√の計算をせずに帰します。
	
	sanae::math::array_average(int,T*);//int個(第一引数)配列の数を足し平均値を出します。
	
	sanae::math::is_even(int i);//偶数か判定して返します。
	
	sanae::math::is_primenumber(int i);//素数か判定して返します。	
	
	sanae::math::euclidean(T*,T*);//N次元の2個のデータのユークリッド距離を返します。
	
	sanae::math::min(size_t,T*);//引数:(sizeof(配列),配列))
	//渡された配列の最小値を返します。	
	
	sanae::math::min();//引数:(sanae::util::arraylist::.len(),arraylist)
	//渡されたsanae::util::arraylistの最小値を返します。
	
	sanae::math::division_number_parts(int,int);//掛け算を返します。第二引数のint値から掛け算の値を検索します。
	/*返り値の型はsanae::util::pair<int,int>です。*/
	
	sanae::math::division_number(int);//入力された値の掛け算の素数の組み合わせを返します。
	/*返り値の型はsanae::util::arraylist<int>です。*/	
	
	sanae::math::average(sanae::str,int, ...);//可長変引数の値をint(第一引数)個たして平均値を出します。
	
	sanae::math::array_deviation(int,T*);//偏差を出します。その他array_average()と同じ。
	
	sanae::math::deviation(sanae::str, int, ...);//偏差を出します。その他average()と同じ
	
	//arraylistを小さい順に整列させます。
	sanae::util::align(sanae::util::arraylist<T>);
	
# その他関数(SanaeUtil.h)
	#クラス
	・sanae::util::map<T1,T2> 変数={T1型のデータ(キー),T2型のデータ};
	
	変数.len();//要素数を返します。

	変数.add(T1(キー),T2(データ));//要素を追加します。
	
	変数.get_data(T1(キー));//キーに対応する要素を返します。
	
	変数.del_data(T1(キー));//キーのデータを消去します。
	
	変数.clear();//データをすべて消去します。
	
	・sanae::util::clock

	sanae::util::clock 変数;//経過した時間(秒)を計測するクラスです。	
	
	変数.start();//経過時間計測開始
	
	変数.stop();//計測終了、経過時間取得(int,秒)
	
	・sanae::util::arraylist
	
	sanae::util::arraylist<T> 変数={値の個数,値...};

	変数.chenge(int,T);//変数[int引数]=Tと同じ
	
	変数.del(int);//変数[int番目]の値を削除

	変数.add(T);//T型の値を追加します。

	変数.clear();//メモリを開放します。
	
	変数.find(T);//Tの値を検索して見つかったらその場所を、見つからない場合は-1を返します。
	
	変数.len();//配列の個数を返します。
	
	・sanae::util::pair
	
	sanae::util::pair<T1,T2> 変数名={T1,T2};//T1型とT2型の値を入れる
	
	変数名.set(T1,T2);//初期化と同じ
	
	変数名.first();//T1型の値を参照
	
	変数名.second();//T2型の値を参照
	
	#関数
	
	sanae::util::count(T*,int,T);//渡されたT型の配列の中に何個Tの値があるかを返します。intは検索する配列の個数です。

	sanae::util::count(sanae::util::arraylist<T>,T);//配列sanae::util::arraylist<T>の中にTの値がいくつあるか返します。
		
	
	sanae::random::setseed(unsigned long seed);//シード値をセットします。
	
	sanae::random::seedreset();//シード値をリセットします。
	
	sanae::random::random(int min, int max, unsigned long seed);//乱数を生成します。
