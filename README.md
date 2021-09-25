# Usually-headers
Objective is make to "Usually header for C++". I like C++ language! and I want to more study C++ language so made this project. Please tell me how to more good programming for C++ language....

# Sanae::str
  /*Define*/
  sanae::str variable="";
  
	/* Return char* type.*/
	variable.c_str();
	
  	/*This class can use printf*/
 	 printf(variable);
	
	/*Add string*/
	variable.add("Add string");
	variable+="Add string";
	
	/*Add int type value.*/
	addint(value);
  	variable+=value;
	
	/*find string*/
	variable.find("string for find");
	
	/*replace string*/
	variable.replace("string to replace","string");
	
	/*delete string*/
	variable.clear();//free memory.
# TestCode(Str型)
 	#include <stdio.h>
	#include "Sanae.h"
	int main(){
	sanae::str test = "SanaeProject";//define
	sanae::str test2 = "Sanae San";//define

	test2.replace(" San","Project");//replace " San" to "Project"
	
	test.addint(2021);//insert int type
	test2.addint(2021);

	if (test==test2) {//compare TRUE
		printf("same\n");
	}

	test2.add("Plus");//insert "Plus"

	if (test!=test2) {//compare TRUE
		printf("not same\n");
	}
	printf(test);
	printf(test2);
	test.clear();//delete string
	test2.clear();//delete string
	/*result:
	same
	not same
	SanaeProject2021SanaeProject2021Plus
	*/
	return 0;
 	}
 # Else functions(SanaeMath.h)
	sanae::math::digit(int);//return argument digit.
	
	sanae::math::little_digit(double);//return decimal point digit for argument.
	
	sanae::math::root(double);//return calculation of square root for argument(double type).
	
	sanae::math::triangle(T,T,bool);//calculation use the Pythagorean theorem then return length of hypotenuse.
	//if third argument is true calculate of square root.
	
	sanae::math::array_average(int,T*);//first argument is number of array,second argument is array.
	
	sanae::math::is_even(int i);//judgement of Even.
	
	sanae::math::is_primenumber(int i);//judgement of primenumber.
	
	sanae::math::euclidean(T*,T*);//return euclidean distance of n dimension two datas.
	
	sanae::math::min(size_t,T*);//argument:(sizeof(array),array))
	//return minimum of array.	
	
	sanae::math::min();//引数:(sanae::util::arraylist::.len(),arraylist)
	//return minimum of sanae::util::arraylist.
	
	sanae::math::division_number_parts(int,int);//return multiplication,second argument is multiplication start point.
	/*return type is sanae::util::pair<int,int>.*/
	
	sanae::math::division_number(int);//return multiplication of prime number.
	/*return type is sanae::util::arraylist<int>.*/	
	
	sanae::math::average(sanae::str,int, ...);//argument:("int or double",quantity,values...) return average.
	
	sanae::math::array_deviation(int,T*);//argument:(quanity,array) return deviation for array.
	
	sanae::math::deviation(sanae::str, int, ...);//argument:("int or double",quanity,values...) return deviation.
	
	//alignment to Smallest first.
	sanae::util::align(sanae::util::arraylist<T>);
	
# Else functions(SanaeUtil.h)
	#classes
	・sanae::util::map<T1,T2> variable={T1typedata(key),T2typedata};
	
	variable.len();//return quanity.

	variable.add(T1(key),T2(data));//add data.
	
	variable.get_data(T1(key));//return data corresponding to the key.
	
	variable.del_data(T1(key));//delete the key and data.
	
	valiable.clear();//delete all datas.
	
	・sanae::util::clock

	sanae::util::clock variable;//A class that measures elapsed time (seconds).
	
	variable.start();//start
	
	variable.stop();//End and return result.
	
	・sanae::util::arraylist
	
	sanae::util::arraylist<T> variable={quanity,values...};

	variable.chenge(int,T);//variable[int] replace to T
	
	variable.del(int);//delete to variable[int]

	variable.add(T);//add the T type value.

	variable.clear();//delete all data.
	
	variable.find(T);//find the argument.
	
	variable.len();//return quanity.
	
	・sanae::util::pair
	
	sanae::util::pair<T1,T2> variable={T1,T2};//insert T1 and T2.
	
	variable.set(T1,T2);//Initialize
	
	variable.first();//reference the T1.
	
	variable.second();//reference the T2.
	
	#function
	
	sanae::util::count(T*,int,T);//find out how many arguments there are in the array.

	sanae::util::count(sanae::util::arraylist<T>,T);//find out how many arguments there are in the sanae::util::array<T>.
		
	
	sanae::random::setseed(unsigned long seed);//set the seed value.
	
	sanae::random::seedreset();//reset the seed value.
	
	sanae::random::random(int min, int max, unsigned long seed);//make the random number.
