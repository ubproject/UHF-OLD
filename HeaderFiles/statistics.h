#pragma once
#ifdef H_SANAE
namespace sanae{
	template<typename T> inline T sigma(unsigned int i, unsigned int N,T* data) {
		T d = 0;
		for (i-=1; i < N; i++) { d += data[i]; }
		return d;
	}
	template<typename T> inline T sigma(unsigned int i, unsigned int N,sanae::util::arraylist<T> *data) {
		T d = 0;
		for (i -= 1; i < N; i++) { d += data[i]; }
		return d;
	}
	namespace statistics {
		//’P‰ñ‹A’¼ü‚ð‹‚ß‚Ü‚·B
		template<typename X,typename Y>class Regressionline {
		private:
			double a=0, b=0;
			X x = 0;
			Y y=0;
			sanae::util::arraylist<X> XX;
			sanae::util::arraylist<double> XY;
		public:
			~Regressionline() {
				this->finish();
			}
			void put(X d1, Y d2) {
				x += d1;
				y += d2;
				XX.add(squared(d1));
				XY.add(d1 * d2);
			}
			void learn() {
				double xx=0, xy=0;
				int N = XX.len();
				for (unsigned int i = 0; i < XX.len();i++) {
					xx += XX[i];
				}
				for (unsigned int i = 0; i < XX.len(); i++) {
					xy += XY[i];
				}
				a = (xx * y - xy * x )/(N * xx - squared(x));
				b = (N * xy - x * y) /(N * xx - squared(x));
			}
			Y get(X x) {
				return a + b * x;
			}
			void finish() {
				XX.clear();
				XY.clear();
				a = b = x = y = 0;
			}
			void formula() {
				printf("%lf+%lf*X\n",a,b);
			}
		};
	}
}
#endif