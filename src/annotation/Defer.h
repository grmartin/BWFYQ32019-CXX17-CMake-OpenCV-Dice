#ifndef DEFER_H
#define DEFER_H

namespace jpeganno {
	template <typename Fn> struct Defer {
	private:
		Fn action;
		bool run{ true };
	public:
		Defer(Fn fn) : action{ fn } {}
		~Defer() { if (run) perform(); }
		
		void perform() {
			if (run) {
				run = false;
				action();
			}
		};
	
	}; 

	template <typename F> Defer<F> defer(F fn) { return Defer<F>(fn); }
}

#endif // DEFER_H
