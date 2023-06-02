#include "type.h"
#include "nullary.h"

namespace sym 
{
	double Const::get_value() const {return value_;}
	Const::operator double() const {return value_; }

	bool Const::is_con() const {return true;}

	__expr_t* Const::eval(const var_map_t& var_map) const {
	    Const* a = new Const(value_);
	    return a;
}

	__expr_t* Const::diff(const std::string& v) const {
	    Const* a = new Const(0);
	    return a;
	}

	std::ostream& Const::operator<< (std::ostream &out) const {
	    out << value_;
	    return out;
	}

	bool Const::operator==(const __expr_t& other) const {
	    const __expr_t* a = &other;
	    if(a -> is_nullary()){
	        if(dynamic_cast<const __nullary_op_t*>(a) -> is_con()){
	            return dynamic_cast<const Const*>(a) -> value_ == this -> value_;
	        }
	    }
	}
}

namespace sym 
{
	std::string Var::get_variable() const {return var_; }
	Var::operator std::string () const {return var_;}
	
	bool Var::is_var() const {return true;}

	__expr_t* Var::eval(const var_map_t& vars) const {
	    if(vars.count(var_) != 1){
	        Var* a = new Var(var_);
	        return a;
	    }
	    else{
	        Const* a = new Const(vars.at(var_));
	        return a;
	    }
	}

	__expr_t* Var::diff(const std::string& v) const {
	    if(var_ == v){
	        Const* a = new Const(1);
	        return a;
	    }
	    else{
	        Const* a = new Const(0);
	        return a;
	    }
	    
	}
	
	std::ostream& Var::operator<< (std::ostream &out) const {
	    out << var_;
	    return out;
	}

	bool Var::operator==(const __expr_t& other) const {
	    const __expr_t* a = &other;
	    if(a -> is_nullary()){
	        if(dynamic_cast<const __nullary_op_t*>(a) -> is_var()){
	            return dynamic_cast<const Var*>(a) -> var_ == this -> var_;
	        }
	    }
	}
}
