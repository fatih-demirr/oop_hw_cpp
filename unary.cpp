#include "nullary.h"
#include "unary.h"
#include "binary.h"
#include <math.h>

namespace sym 
{
	bool NegOp::is_neg() const {return true; }

	__expr_t* NegOp::eval(const var_map_t& vars) const {
	    __expr_t* a = operand -> eval(vars);
	    if(a -> is_nullary()){
	        if(dynamic_cast<const __nullary_op_t*>(a) -> is_con()){
	            double b = dynamic_cast<const Const*>(a) -> get_value();
	            Const* c = new Const((-1) * b);
	            delete a;
	            return c;
	        }
	    }
	    __expr_t* e = new NegOp(a);
	    return e;
	}

	__expr_t* NegOp::diff(const std::string& v) const {
	    __expr_t* a = operand -> diff(v);
	    __expr_t* b = new NegOp(a);
	    return b;
	}

	std::ostream& NegOp::operator<< (std::ostream &out) const {
	    out<< "-";
	    if(!operand-> is_nullary()){
	        out << "(";
	        out << *operand;
    	    out << ")";
	    }
	    else{
	        out << *operand;
	    }
	    return out;
	}

	bool NegOp::operator==(const __expr_t& other_) const {
	    const __expr_t* a = &other_;
	    if(a -> is_unary()){
	        if(dynamic_cast<const __unary_op_t*>(a) -> is_neg()){
	            return dynamic_cast<const NegOp*>(a) -> operand == this -> operand;
	        }
	    }
	}
}

namespace sym 
{
	bool ExpOp::is_exp() const {return true; }

	__expr_t* ExpOp::eval(const var_map_t& vars) const {
	    __expr_t* a = operand -> eval(vars);
	    if(a -> is_nullary()){
	        if(dynamic_cast<const __nullary_op_t*>(a) -> is_con()){
	            double b = dynamic_cast<const Const*>(a) -> get_value();
	            Const* c = new Const(std::exp(b));
	            delete a;
	            return c;
	        }
	    }
        ExpOp* b = new ExpOp(a);
	    return b;
	}

	__expr_t* ExpOp::diff(const std::string& v) const {
	    __expr_t* a = operand -> diff(v);
	    __expr_t* b = this -> eval();
	    if(a -> is_nullary()){
	        if(dynamic_cast<const __nullary_op_t*>(a) -> is_con()){
	            if(dynamic_cast<const Const*>(a) -> get_value() == 0){
	                Const* c = new Const(0);
	                delete b;
	                delete a;
	                return c;
	            }
	            if(dynamic_cast<const Const*>(a) -> get_value() == 1){
	                delete a;
	                return b;
	            }
	            if(dynamic_cast<const Const*>(a) -> get_value() == -1){
	                NegOp* e = new NegOp(b);
	                delete a;
	                return e;
	            }
	        }
	    }
	    MulOp* d = new MulOp(a, b);
	    return d;
	}

	std::ostream& ExpOp::operator<< (std::ostream &out) const {
	    if(this -> operand -> is_nullary()){
	        out << "e^";
	        out << *operand;
	        return out;
	    }
	    else{
	        out << "e^(";
	        out << *operand;
	        out << ")";
	        return out;
	    }
	}

	bool ExpOp::operator==(const __expr_t& other_) const {
	    const __expr_t* a = &other_;
	    if(a -> is_unary()){
	        if(dynamic_cast<const __unary_op_t*>(a) -> is_exp()){
	            return dynamic_cast<const ExpOp*>(a) -> operand == this -> operand;
	        }
	    }
	}
}
