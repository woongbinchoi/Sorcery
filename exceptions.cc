#include "exceptions.h"
Exception::Exception():
	reason{""}{}
Exception::Exception(std::string reason):
	reason{reason}{}
	
std::string Exception::why(){
	return reason;
}

InvalidTarget::InvalidTarget():
	Exception{""}{}

InvalidTarget::InvalidTarget(std::string reason):
	Exception{reason}{}

NoEffect::NoEffect():
	Exception{""}{}

NoEffect::NoEffect(std::string reason):
	Exception{reason}{}

InvalidMove::InvalidMove():
	Exception{""}{}

InvalidMove::InvalidMove(std::string reason):
	Exception{reason}{}
	