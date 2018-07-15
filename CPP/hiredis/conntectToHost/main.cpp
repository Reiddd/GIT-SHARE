#include <iostream>
#include <string>
#include <hiredis/hiredis.h>

int main()
{
    struct timeval timeout = {2, 0};
    redisContext* redis_context = reinterpret_cast<redisContext*>(redisConnectWithTimeout("101.132.110.96", 6379, timeout));
 // redisContext* redis_context = reinterpret_cast<redisContext*>(redisConnect("127.0.0.1", 6379));

    if(redis_context == nullptr || redis_context->err){
        if(redis_context->err)
            std::cerr<< redis_context->errstr <<std::endl;
        else
            std::cerr<< "can't allocate redisContext" <<std::endl;
        return -1;
    }

    redisReply* redis_reply = reinterpret_cast<redisReply*>(redisCommand(redis_context, "INFO"));
    std::cout<< redis_reply->str <<std::endl;

    freeReplyObject(redis_reply);
    return 0;
}
