#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

int main(){

std::fstream fs;
fs.open("/proc/cpuinfo",std::fstream::in);

std::string line;

//Informacion del CPU
while(getline(fs,line)){

if(line.find("model name") != std::string::npos){


std::string model = line.substr (line.find(":")+1);

std::cout<<model<<std::endl;
fs.close();

}

}

//informacion de la memoria instalada
fs.open ("/proc/meminfo",std::fstream::in);

while(getline(fs,line)){

if(line.find("MemTotal") != std::string::npos){

std::string mem = line.substr (line.find(":")+1);

std::cout<<mem<<std::endl;
fs.close();

}

}

//informacion del kernel
fs.open("/proc/version",std::fstream::in);
getline(fs,line);

std::cout<< line<< std::endl;

fs.close();


//informacion ultima vez prendida

fs.open("/proc/uptime",std::fstream::in);
getline(fs,line);
std::string x1 , x2;

long l;
std::stringstream ss(line);
ss >> x1 >> x2;
std::cout<<x1<<std::endl<<x2<<std::endl;



}
