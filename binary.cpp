#include "binary.h"
#include "nullary.h"
#include <math.h>

namespace sym 
{
	bool AddOp::is_add() const {return true; }

	__expr_t* AddOp::eval(const var_map_t& vars) const {
	    __expr_t* l = lhs_ -> eval(vars);
	    __expr_t* r = rhs_ -> eval(vars);
	    if(r -> is_nullary()){
	        if(dynamic_cast<const __nullary_op_t*>(r) -> is_con()){
	            if(dynamic_cast<const Const*>(r) -> get_value() == 0){
	                delete r;
	                return l;
	            }
	        }
	    }
	    if(l -> is_nullary()){
	        if(dynamic_cast<const __nullary_op_t*>(l) -> is_con()){
	            if(dynamic_cast<const Const*>(l) -> get_value() == 0){
	                delete l;
	                return r;
	            }
	        }
	    }
	    if(l -> is_nullary() && r -> is_nullary()){
	        if(dynamic_cast<const __nullary_op_t*>(r) -> is_con() && dynamic_cast<const __nullary_op_t*>(l) -> is_con()){
	            double a = dynamic_cast<const Const*>(r) -> get_value();
	            double b = dynamic_cast<const Const*>(l) -> get_value();
	            double c = a + b;
	            Const* d = new Const(c);
	            delete l;
	            delete r;
	            return d;
	        }
	    }
        AddOp* a = new AddOp(l, r);
        return a;
	}

	__expr_t* AddOp::diff(const std::string& v) const {
	    __expr_t* dummy1 = lhs_ -> diff(v);
	    __expr_t* dummy2 = rhs_ -> diff(v);
	    __expr_t* l = dummy1 -> eval();
	    __expr_t* r = dummy2 -> eval();
	    if(l -> is_nullary()){
	        if(dynamic_cast<__nullary_op_t*>(l) -> is_con()){
	            if(dynamic_cast<Const*>(l) -> get_value() == 0){
	                delete l;
	                delete dummy1;
	                delete dummy2;
	                return r;
	            }
	        }
	    }
	    if(r -> is_nullary()){
	        if(dynamic_cast<__nullary_op_t*>(r) -> is_con()){
	            if(dynamic_cast<Const*>(r) -> get_value() == 0){
	                delete r;
	                delete dummy1;
	                delete dummy2;
	                return l;
	            }
	        }
	    }
	    if(l -> is_nullary() && r -> is_nullary()){
	        if(dynamic_cast<const __nullary_op_t*>(r) -> is_con() && dynamic_cast<const __nullary_op_t*>(l) -> is_con()){
	            double a = dynamic_cast<const Const*>(r) -> get_value();
	            double b = dynamic_cast<const Const*>(l) -> get_value();
	            double c = a + b;
	            Const* d = new Const(c);
	            delete l;
	            delete r;
	            delete dummy1;
	            delete dummy2;
	            return d;
	        }
	    }
	    AddOp* a = new AddOp(l, r);
	    delete dummy1;
	    delete dummy2;
	    return a;
	}

	std::ostream& AddOp::operator<< (std::ostream &out) const {
	    if(!(lhs_-> is_nullary())){
	        out << "(";
	        out << *lhs_;
    	    out << ")";
	    }
	    else{
	        out << *lhs_;
	    }
	    out << " + ";
	    if(!(rhs_ -> is_nullary())){
	        out << "(";
	        out << *rhs_;
	        out << ")";
	    }
	    else{
	        out << *rhs_;
	    }
	    return out;
	}

	bool AddOp::operator==(const __expr_t& other_) const {
	    const __expr_t* a = &other_;
	    if(a -> is_binary()){
	        if(dynamic_cast<const __binary_op_t*>(a) -> is_add()){
	            bool x = dynamic_cast<const AddOp*>(a) -> lhs_ == this -> lhs_;
	            bool y = dynamic_cast<const AddOp*>(a) -> rhs_ == this -> rhs_;
	            bool z = dynamic_cast<const AddOp*>(a) -> lhs_ == this -> rhs_;
	            bool t = dynamic_cast<const AddOp*>(a) -> rhs_ == this -> lhs_;
	            if((x && y) || (z && t)){
	                return true;
	            }
	        }
	    }
	}
}

namespace sym 
{
	bool MulOp::is_mul() const {return true; }

	__expr_t* MulOp::eval(const var_map_t& vars) const {
	    __expr_t* l = lhs_ -> eval(vars);
	    __expr_t* r = rhs_ -> eval(vars);
	    if(r -> is_nullary()){
	        if(dynamic_cast<const __nullary_op_t*>(r) -> is_con()){
    	        if(dynamic_cast<const Const*>(r) -> get_value() == 0){
    	            Const* a = new Const(0);
    	            delete r;
    	            delete l;
    	            return a;
    	        }
    	    }
	    }
	    if(l -> is_nullary()){
	        if(dynamic_cast<const __nullary_op_t*>(l) -> is_con()){
    	        if(dynamic_cast<const Const*>(l) -> get_value() == 0){
    	            Const* a = new Const(0);
    	            delete r;
    	            delete l;
    	            return a;
    	        }
    	    }
	    }
	    if(r -> is_nullary()){
	        if(dynamic_cast<const __nullary_op_t*>(r) -> is_con()){
    	        if(dynamic_cast<const Const*>(r) -> get_value() == 1){
    	            delete r;
    	            return l;
    	        }
    	    }
	    }
	    if(l -> is_nullary()){
	        if(dynamic_cast<const __nullary_op_t*>(l) -> is_con()){
	            if(dynamic_cast<const Const*>(l) -> get_value() == 1){
	                delete l;
	                return r;
	            }
	        }
	    }
	    if(l -> is_nullary() && r -> is_nullary()){
	        if(dynamic_cast<const __nullary_op_t*>(r) -> is_con() && dynamic_cast<const __nullary_op_t*>(l) -> is_con()){
	            double a = dynamic_cast<const Const*>(r) -> get_value();
	            double b = dynamic_cast<const Const*>(l) -> get_value();
	            double c = a * b;
	            Const* d = new Const(c);
	            delete l;
	            delete r;
	            return d;
	        }
	    }
	    MulOp* a = new MulOp(l, r);
	    return a;
	}

	__expr_t* MulOp::diff(const std::string& v) const {
	    __expr_t* left;
	    __expr_t* right;
	    __expr_t* dummy1 = lhs_ -> diff(v);
	    __expr_t* dummy2 = rhs_ -> diff(v);
	    __expr_t* le = lhs_ -> eval();
	    __expr_t* re = rhs_ -> eval();
	    __expr_t* l = dummy1 -> eval();
	    __expr_t* r = dummy2 -> eval();
	    if(l -> is_nullary() && re -> is_nullary()){
	        if(dynamic_cast<__nullary_op_t*>(l) -> is_con() && dynamic_cast<__nullary_op_t*>(re) -> is_con()){
	            if(dynamic_cast<Const*>(l) -> get_value() == 0 || dynamic_cast<Const*>(re) -> get_value() == 0){
	                Const* a = new Const(0);
	                left = a;
	                delete l;
	                delete re;
	            }
	            else{
	                double m = dynamic_cast<Const*>(l) -> get_value();
	                double n = dynamic_cast<Const*>(re) -> get_value();
	                Const* a = new Const(m * n);
	                left = a;
	                delete l;
	                delete re;
	            }
	        }
	        else if(dynamic_cast<__nullary_op_t*>(l) -> is_con()){
	            if(dynamic_cast<Const*>(l) -> get_value() == 0){
	                Const* a = new Const(0);
	                left = a;
	                delete l;
	                delete re;
	            }
	            else if(dynamic_cast<Const*>(l) -> get_value() == 1){
	                left = re;
	                delete l;
	            }
	            else{
	                MulOp* a = new MulOp(l, re);
	                left = a;
	            }
	        }
	        else if(dynamic_cast<__nullary_op_t*>(re) -> is_con()){
	            if(dynamic_cast<Const*>(re) -> get_value() == 0){
	                Const* a = new Const(0);
	                left = a;
	                delete l;
	                delete re;
	            }
	            if(dynamic_cast<Const*>(re) -> get_value() == 1){
	                left = l;
	                delete re;
	            }
	            else{
	                MulOp* a = new MulOp(l, re);
	                left = a;
	            }
	        }
	        else{
	            MulOp* a = new MulOp(l, re);
	            left = a;
	        }
	    }
	    else{
	        if(l -> is_nullary()){
    	        if(dynamic_cast<__nullary_op_t*>(l) -> is_con()){
    	            if(dynamic_cast<Const*>(l) -> get_value() == 0){
    	                Const* a = new Const(0);
    	                left = a;
    	                delete l;
    	                delete re;
    	            }
    	            else if(dynamic_cast<Const*>(l) -> get_value() == 1){
    	                left = re;
    	                delete l;
    	            }
    	            else{
    	                MulOp* a = new MulOp(l, re);
    	                left = a;
    	            }
    	        }
    	        else{
    	            MulOp* a = new MulOp(l, re);
    	            left = a;
    	        }
    	    }
    	    else if(re -> is_nullary()){
    	        if(dynamic_cast<__nullary_op_t*>(re) -> is_con()){
    	            if(dynamic_cast<Const*>(re) -> get_value() == 0){
    	                Const* a = new Const(0);
    	                left = a;
    	                delete l;
	                    delete re;
    	            }
    	            else if(dynamic_cast<Const*>(re) -> get_value() == 1){
    	                left = l;
    	                delete l;
	                    delete re;
    	            }
    	            else{
    	                MulOp* a = new MulOp(l, re);
    	                left = a;
    	            }
    	        }
    	        else{
    	            MulOp* a = new MulOp(l, re);
    	            left = a;
    	        }
    	    }
    	    else{
    	        MulOp* a = new MulOp(l, re);
    	        left = a;
    	    }
	    }
	    if(r -> is_nullary() && le -> is_nullary()){
	        if(dynamic_cast<__nullary_op_t*>(r) -> is_con() && dynamic_cast<__nullary_op_t*>(le) -> is_con()){
	            if(dynamic_cast<Const*>(r) -> get_value() == 0 || dynamic_cast<Const*>(le) -> get_value() == 0){
	                Const* a = new Const(0);
	                right = a;
	                delete le;
	                delete r;
	            }
	            else{
	                double m = dynamic_cast<Const*>(r) -> get_value();
	                double n = dynamic_cast<Const*>(le) -> get_value();
	                Const* a = new Const(m * n);
	                right = a;
	                delete le;
	                delete r;
	            }
	        }
	        else if(dynamic_cast<__nullary_op_t*>(r) -> is_con()){
	            if(dynamic_cast<Const*>(r) -> get_value() == 0){
	                Const* a = new Const(0);
	                right = a;
	                delete le;
	                delete r;
	            }
	            else if(dynamic_cast<Const*>(r) -> get_value() == 1){
	                right = le;
	                delete r;
	            }
	            else{
	                MulOp* a = new MulOp(le, r);
	                right = a;
	            }
	        }
	        else if(dynamic_cast<__nullary_op_t*>(le) -> is_con()){
	            if(dynamic_cast<Const*>(le) -> get_value() == 0){
	                Const* a = new Const(0);
	                right = a;
	                delete le;
	                delete r;
	            }
	            if(dynamic_cast<Const*>(le) -> get_value() == 1){
	                right = r;
	                delete le;
	            }
	            else{
	                MulOp* a = new MulOp(le, r);
	                right = a;
	            }
	        }
	        else{
	            MulOp* a = new MulOp(le, r);
	            right = a;
	        }
	    }
	    else{
    	    if(r -> is_nullary()){
    	        if(dynamic_cast<__nullary_op_t*>(r) -> is_con()){
    	            if(dynamic_cast<Const*>(r) -> get_value() == 0){
    	                Const* a = new Const(0);
    	                right = a;
    	                delete le;
    	                delete r;
    	            }
    	            else if(dynamic_cast<Const*>(r) -> get_value() == 1){
    	                right = le;
	                    delete r;
    	            }
    	            else{
    	                MulOp* a = new MulOp(le, r);
    	                right = a;
    	            }
    	        }
    	        else{
    	            MulOp* a = new MulOp(le, r);
    	            right = a;
    	        }
    	    }
    	    else if(le -> is_nullary()){
    	        if(dynamic_cast<__nullary_op_t*>(le) -> is_con()){
    	            if(dynamic_cast<Const*>(le) -> get_value() == 0){
    	                Const* a = new Const(0);
    	                right = a;
    	                delete le;
    	                delete r;
    	            }
    	            else if(dynamic_cast<Const*>(le) -> get_value() == 1){
    	                right = r;
    	                delete le;
    	            }
    	            else{
    	                MulOp* a = new MulOp(le, r);
    	                right = a;
    	            }
    	        }
    	        else{
	                MulOp* a = new MulOp(le, r);
	                right = a;
	            }
    	    }
    	    else{
    	        MulOp* a = new MulOp(le, r);
    	        right = a;
    	    }
	    }
	    if(left -> is_nullary()){
	        if(dynamic_cast<__nullary_op_t*>(left) -> is_con()){
	            if(dynamic_cast<Const*>(left) -> get_value() == 0){
	            delete left;
        	    delete dummy1;
        	    delete dummy2;
    	        return right;
        	    }
	        }
	    }
	    if(right -> is_nullary()){
	        if(dynamic_cast<__nullary_op_t*>(right) -> is_con()){
	            if(dynamic_cast<Const*>(right) -> get_value() == 0){
    	            delete right;
    	            delete dummy1;
            	    delete dummy2;
        	        return left;
    	        }
	        } 
	    }
	    if(left -> is_nullary() && right -> is_nullary()){
	        if(dynamic_cast<__nullary_op_t*>(left) -> is_con() && dynamic_cast<__nullary_op_t*>(right) -> is_con()){
    	        double m = dynamic_cast<Const*>(left) -> get_value();
    	        double n = dynamic_cast<Const*>(right) -> get_value();
    	        Const* a = new Const(m+n);
    	        delete dummy1;
        	    delete dummy2;
    	        delete left;
    	        delete right;
    	        return a;
    	    }
	    }
        AddOp* a = new AddOp(left, right);
	    delete dummy1;
	    delete dummy2;
	    return a;
	}

	std::ostream& MulOp::operator<< (std::ostream &out) const {
	    if(!(lhs_-> is_nullary())){
	        out << "(";
	        out << *lhs_;
    	    out << ")";
	    }
	    else{
	        out << *lhs_;
	    }
	    out << " * ";
	    if(!(rhs_ -> is_nullary())){
	        out << "(";
	        out << *rhs_;
	        out << ")";
	    }
	    else{
	        out << *rhs_;
	    }
	    return out;
	}
	
	bool MulOp::operator==(const __expr_t& other_) const {
	    const __expr_t* a = &other_;
	    if(a -> is_binary()){
	        if(dynamic_cast<const __binary_op_t*>(a) -> is_mul()){
	            bool x = dynamic_cast<const MulOp*>(a) -> lhs_ == this -> lhs_;
	            bool y = dynamic_cast<const MulOp*>(a) -> rhs_ == this -> rhs_;
	            bool z = dynamic_cast<const MulOp*>(a) -> lhs_ == this -> rhs_;
	            bool t = dynamic_cast<const MulOp*>(a) -> rhs_ == this -> lhs_;
	            if((x && y) || (z && t)){
	                return true;
	            }
	        }
	    }
	}
}
