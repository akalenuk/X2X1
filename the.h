#include <string>
#include <vector>
#include <stdexcept>

class the // runtime_error for type errors
{
    enum class Type {String, Vector, Nothing};
    Type m_type = Type::Nothing;
    std::string m_string;
    std::vector<the> m_vector;

public:
    the() : m_type{Type::Nothing}, m_string{}, m_vector{} {}
    the(const std::string& s) : m_type{Type::String}, m_string{s}, m_vector{} {}
    the(const char* s) : the(std::string(s)) {}
    the(const std::vector<the>& v) : m_type{Type::Vector}, m_string{}, m_vector{v.begin(), v.end()} {}
    the(const std::initializer_list<the>& v) : the(static_cast<std::vector<the> >(v)) {}

    operator std::string(){
        if(m_type == Type::String){
            return m_string;
        }else{
            return this->joined_with("\n");
        }
    }

    the operator&(std::string b){
        if(m_type == Type::String){
            return the(m_string + b);
        }else if(m_type == Type::Vector){
            auto that = the(*this);
            for(auto& it : that.m_vector)
                it = it & b;
            return that;
        }
        throw std::runtime_error("& does not add to Nothing.");
    }

    the operator[](int i){
        if(m_type == Type::Vector){
            return m_vector.at(i-1);
        }
        throw std::runtime_error("This 'the' doesn't hold multiple values.");
    }

    the split_with(the coma){
        if(m_type == Type::String && coma.m_type == Type::String ){
            std::vector<the> to;
            size_t coma_pos = 0;
            size_t coma_len = coma.m_string.size();
            while(coma_pos != std::string::npos){
                size_t new_coma_pos = m_string.find(coma.m_string, coma_pos);
                if(new_coma_pos != std::string::npos){
                    to.push_back(m_string.substr(coma_pos, new_coma_pos - coma_pos));
                    coma_pos = new_coma_pos + coma_len;
                }else{
                    to.push_back(m_string.substr(coma_pos, std::string::npos));
                    coma_pos = std::string::npos;
                }
            }
            return the(to);
        }else if(m_type == Type::Vector){
            auto that = the(*this);
            for(auto& it : that.m_vector)
                it = it.split_with(coma);
            return that;
        }else{
            throw std::runtime_error("Split doesn't work on Nothing");
        }
    }

    the joined_with(the coma){
        if(m_type == Type::Vector && coma.m_type == Type::String && !m_vector.empty()){
            the to = m_vector.front();
            for(auto& it : m_vector){
		if(it.m_type == Type::String)
	                to = to & coma & it;
		else
			throw std::runtime_error("Join doesn't work with other than String vectors");
            }
            return to;
        }
        throw std::runtime_error("Join works with multiple strings on the left and single strings on the right.");
    }

    std::vector<the>::iterator begin(){
        return m_vector.begin();
    }

    std::vector<the>::iterator end(){
        return m_vector.end();
    }

    size_t size(){
        if(m_type == Type::Vector){
            return m_vector.size();
        }
        throw std::runtime_error("Size works only on multiple values.");
    }

    void append(the t){
        if(m_type == Type::Nothing){
            m_type = Type::Vector;
            this->append(t);
        }else if(m_type == Type::Vector){
            if(t.m_type == Type::Vector){
                m_vector.insert(m_vector.end(), t.m_vector.begin(), t.m_vector.end());
            }else{
                m_vector.push_back(t);
            }
        }else{
            throw std::runtime_error("Append works only on multiple values or completely new 'the'.");
        }
    }
};

