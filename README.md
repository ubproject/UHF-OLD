# Useful-headers
Objective is make to "useful header for C++". <br>I like C++ language! and I want to more study C++ language so made this project.<br> Please tell me how to more good programming for C++ language....

Version.3
# Sanae::str
  	/*Define*/
  	sanae::str variable="";
  
	/* Return char* type.*/
	variable.c_str();
	
  	/*This class can use printf*/
 	 printf(variable.c_str());
	
	/*Add string*/
	variable.add("Add string");
	
	/*find string*/
	variable.find("string for find");
	
	/*replace string*/
	variable.replace("string to replace","string");
	
	/*delete string*/
	variable.clear();//free memory
	
	variable.~str();//Destructor
	
	variable.split(',');//return std::vector<sanae::str>
 # Else functions(SanaeNet.h)
	#class
	
	・sanae::UDP::udp variable(portnumber,"IPv4 Address");
	
	variable.send_udp("send text");
	
	variable.bind_udp();

	variable.recv_udp((size_t)1024);//return char*
	
	variable.~udp();//Destructor
	
	・sanae::TCP::server variable(portnumber);
	
	test.accept_tcp();
	
	test.send_tcp("send text");
	
	test.recv_tcp(1024);//return char*
	
	test.~server();//destructor
	
	・sanae::TCP:: client

	d.connect_tcp("IP Address",port);

	d.recv_tcp(1024);//return char*

	d.send_tcp("send text");

	d.~client();//destructor

 # Else functions(statistics.h)
	sanae::sigma(unsigned int i, unsigned int N,T* data);

	sanae::sigma(unsigned int i, unsigned int N,sanae::util::arraylist<T> *data);
	
	#class
	sanae::statistics::Regressionline<X,Y> a;
	
	a.put((X)data1,(Y)data2);
	
	a.learn();
	
	a.get((X)data);
	
	a.finish();
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
	
	sanae::math::min();//argument:(sanae::util::arraylist::.len(),arraylist)
	//return minimum of sanae::util::arraylist.
	
	sanae::math::division_number_parts(int,int);//return multiplication,second argument is multiplication start point.
	/*return type is sanae::util::pair<int,int>.*/
	
	sanae::math::division_number(int);//return multiplication of prime number.
	/*return type is sanae::util::arraylist<int>.*/	
	
	sanae::math::array_deviation(int,T*);//argument:(quanity,array) return deviation for array.
	
	sanae::math correlation(T* d1,T* d2, int);//return Correlation coefficient.

	//alignment to Smallest first.
	sanae::util::align(sanae::util::arraylist<T>);
	
# Else functions(SanaeUtil.h)
	#classes
	/*Not recommended*/
	
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
	
	/*Not recommended*/
	
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
