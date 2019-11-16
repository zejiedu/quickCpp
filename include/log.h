/**
 * @file log.h
 * @author Zejie Du (duzejie@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-11-15
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include<iostream>
#include <sstream> 
#include <fstream> 
#include <string>       // std::string
#include <ctime>

enum class LogRank {    
    INFO,   
    WARNING,
    CAUTION,
    ERROR
};

void LogInit(std::string log_file_err, std::string log_file_info="");

static std::string  getCurrentTimeStr(){
	time_t t = time(NULL);
	char ch[64] = {0};
	strftime(ch, sizeof(ch) - 1, "[%Y-%m-%d %H:%M:%S]", localtime(&t));     //年-月-日 时-分-秒
	return ch;
}

class Log
{
private:        
    bool out;
    bool quit;    

public:
    static std::ostream *o_err;  //out log file    
    static std::ostream *o_info;  //out log file
    std::ostream *o;  //out log file
    friend void LogInit();
    

    template<class T>
    Log & operator << (T t){        
        if (out)           
            *o <<t<<" ";         
        return *this;
    }
    Log(LogRank rank, const char* file, int line, bool isOut, bool isQuit):out(isOut), quit(isQuit){
        if (out)
        {
            o = o_info;
            if (rank == LogRank::INFO)
            {
                *o_info << std::endl << getCurrentTimeStr() << "INFO:         ";
                
            }
            else if (rank == LogRank::WARNING)
            {
                *o_info << std::endl << getCurrentTimeStr() << "WARNING:      ";
            }
            else if (rank == LogRank::CAUTION)
            {
                *o_info << std::endl << getCurrentTimeStr() << "CAUTION:      ";
            }
            else if (rank == LogRank::ERROR)
            {
                *o_err << std::endl << getCurrentTimeStr()  << "CHECK FALL:   ";
                o = o_err;
            }
            else
            {
                std::cerr << "err log rank" << std::endl;
            }
            *o << file << ", line:" << line << ", ";
        }
    } 
    ~Log(){      
        if(quit){
            *o << std::endl;
            exit(0); 
        }
                 
    }
};



#define CHECK(x)        Log(LogRank::ERROR,  __FILE__, __LINE__,  !(x), !(x))
#define INFO            Log(LogRank::INFO,   __FILE__, __LINE__,  true, false)
#define WARNING(x)      Log(LogRank::WARNING,__FILE__, __LINE__,  !(x), false)
#define CAUTION         Log(LogRank::CAUTION,__FILE__, __LINE__,  true, false)
    



std::ostream *Log::o_err = &std::cerr;
std::ostream *Log::o_info = &std::clog;

void LogInit(std::string log_file_err, std::string log_file_info){
    static std::ofstream err(log_file_err,std::ios::out);
    if (!err)
    {
        std::cerr<<"LogInit ERR, please check your log_file_err name"<<std::endl;
        exit(0); 
    }
    Log::o_err = &err;

    static std::ofstream info(log_file_info,std::ios::out);
    if (!info)
    {
        std::clog<<"LogInit WARNING, please check your log_file_info name"<<std::endl;
        Log::o_info = &err;
    }else{
        Log::o_info = &info;
    }        

}
    