#include "expr.h"

namespace sym 
{
	Expr::Expr(const Const& c) {
	    __expr_t* a = c.eval();
	    expr_ = a;
	}
	Expr::Expr(const Var& v) {
	    __expr_t* a = v.eval();
	    expr_ = a;
	}
	Expr::Expr(const __expr_t* e) {
	    expr_ = e;
	}
	Expr::Expr(const __expr_t& e) {
	    if(e.is_nullary()){
	        const __expr_t* a = e.eval();
	        expr_ = a;
	    }
	    else{
	        expr_ = &e;
	    }
	}
	Expr::Expr(const Expr& e) {
	    if(e.is_nullary()){
	        const __expr_t* a = e.eval();
	        expr_ = a;
	    }
	    else{
	        expr_ = &e;
	    }
	}
		
	Expr::~Expr() {delete expr_;}

	__expr_t* Expr::eval(const var_map_t& var_map) const {
	    __expr_t* a = expr_ -> eval(var_map);
	    return a;
	}
	__expr_t* Expr::diff(const std::string& v) const {
	    __expr_t* a = expr_ -> diff(v);
	    return a;
	}
	std::ostream& Expr::operator<< (std::ostream &out) const {
	    out << *expr_;
	    return out;
	}
	bool Expr::operator==(const Expr& other) const {
	    return *expr_ == *(other.expr_);
	}
	bool Expr::operator==(const __expr_t& other) const {
	    return *expr_ == other;
	}
}                                                                  	
