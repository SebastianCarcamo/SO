#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <unistd.h>

int main(){
	std::fstream fs;
	double avaD, totD;
	std::string line;
	std::string tot, ava;
	while(true){

		fs.open("/proc/meminfo",std::fstream::in);

		while(getline(fs,line)){

			if(line.find("MemTotal") != std::string::npos){
				std::stringstream ss(line);
				ss>>tot>>tot;
				//std::cout<<tot<<std::endl;
				totD = std::stod(tot);
				//std::cout<<totD<<std::endl;
				}

			if(line.find("MemAvailable") != std::string::npos){

				std::stringstream sss(line);
				sss>>ava>>ava;
				//std::cout<<ava<<std::endl;
				avaD = std::stod(ava);
				//std::cout<<avaD<<std::endl;
				}
double perc = avaD * 100 / totD;

//	std::cout<<perc<<"%\t";

}

//fs.close();

fs.open("/proc/stat/",std::fstream::in);


while(getline(fs,line)){

if(line.find("cpu") != std::string::npos){

std::stringstream ss2(line);
std::string cpu;
double user,nice,system,idle,iowait,irq,softirq,total;
ss2>>cpu>>user>>nice>>system>>idle>>iowait>>irq>>softirq;
total = user+nice+system+idle+iowait+irq+softirq;


std::cout<<"hola"<<user;
}
//std::cout<<"User ->"<<user/total*100;
//std::cout<<"System ->"<<system/total*100;
//std::cout<<"Idle ->"<<idle/total*100;

}
while(getline(fs.line)){

	if(line.find("ctxt") == std::string::npos) continue;
	stringstream ss3(line);
	std::string ctxt;
	

}

usleep(1000);
}
return 0;
}
