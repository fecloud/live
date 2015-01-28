/*
 * log.h
 *
 *  Created on: 2015年1月27日
 *      Author: maygolf
 */

#ifndef LOG_H_
#define LOG_H_

#ifndef CPP_DEBUG
#define CPP_DEBUG 1
#endif

#ifndef C_DEBUG
#define C_DEBUG 1
#endif

#ifdef __cplusplus

#if CPP_DEBUG
#define CPPLOG(_STR_) std::cout << __FILE__ << " " <<  __LINE__ << " " << _STR_ << std::endl
#else
#define CPPLOG(_STR_)   ((void)0)
#endif

#endif /*__cplusplus */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#if C_DEBUG
#define CLOG(...)    \
	((void)printf("(%s %d) ",__FILE__, __LINE__));						 \
	((void)printf(__VA_ARGS__));						     \
	((void)printf("\n"))

#else
#define CLOG(...) ((void)0)
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LOG_H_ */
