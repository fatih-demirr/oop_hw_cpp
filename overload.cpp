#include "nullary.h"
#include "unary.h"
#include "binary.h"

namespace sym {
	__expr_t& operator-(const __expr_t &op) {
	    if(op.is_nullary()){
	        __expr_t* b = op.eval();
	        __expr_t* a = new NegOp(b);
	        return *a;
	    }
	    __expr_t* a = new NegOp(&op);
	    return *a;
	}
	__expr_t& exp(const __expr_t &op) {
	    if(op.is_nullary()){
	        __expr_t* b = op.eval();
	        __expr_t* a = new ExpOp(b);
	        return *a;
	    }
	    __expr_t* a = new ExpOp(&op);
	    return *a;
	}

	__expr_t& operator+(const __expr_t &lhs, const __expr_t &rhs) {
	    const __expr_t* left = &lhs;
	    const __expr_t* right = &rhs;
	    if(lhs.is_nullary()){
	        left = lhs.eval();
	    }
	    if(rhs.is_nullary()){
	        right = rhs.eval();
	    }
	    __expr_t* a = new AddOp(left, right);
	    return *a;
	}
	__expr_t& operator+(double lhs, const __expr_t &rhs) {
	    const __expr_t* right;
	    __expr_t* a = new Const(lhs);
	    if(rhs.is_nullary()){
	        right = rhs.eval();
	        __expr_t* b = new AddOp(a, right);
	        return *b;
	    }
	    __expr_t* b = new AddOp(a, &rhs);
	    return *b;
	}
	__expr_t& operator+(const __expr_t &lhs, double rhs) {
	    const __expr_t* left;
	    __expr_t* a = new Const(rhs);
	    if(lhs.is_nullary()){
	        left = lhs.eval();
	        __expr_t* b = new AddOp(left, a);
	        return *b;
	    }
	    __expr_t* b = new AddOp(&lhs, a);
	    return *b;
	}

	__expr_t& operator*(const __expr_t &lhs, const __expr_t &rhs) {
	    const __expr_t* left = &lhs;
	    const __expr_t* right = &rhs;
	    if(lhs.is_nullary()){
	        left = lhs.eval();
	    }
	    if(rhs.is_nullary()){
	        right = rhs.eval();
	    }
	    __expr_t* a = new MulOp(left, right);
	    return *a;
	}
	__expr_t& operator*(double lhs, const __expr_t &rhs) {
	    __expr_t* right;
	    __expr_t* a = new Const(lhs);
	    if(rhs.is_nullary()){
	        right = rhs.eval();
	        __expr_t* b = new MulOp(a, right);
	        return *b;
	    }
	    __expr_t* b = new MulOp(a, &rhs);
	    return *b;
	}
	__expr_t& operator*(const __expr_t &lhs, double rhs) {
	    __expr_t* left;
	    __expr_t* a = new Const(rhs);
	    if(lhs.is_nullary()){
	        left = lhs.eval();
	        __expr_t* b = new MulOp(left, a);
	        return *b;
	    }
	    __expr_t* b = new MulOp(&lhs, a);
	    return *b;
	}
}
