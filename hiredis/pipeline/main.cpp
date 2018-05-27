#include <iostream>
#include <hiredis/hiredis.h>

int main()
{
    struct timeval timeout = {2, 0};
    redisContext* redis_context = reinterpret_cast<redisContext*>(redisConnectWithTimeout("101.132.110.96", 6379, timeout));
    if(redis_context == nullptr){
        std::cout<< "no connection established." <<std::endl;
        return 1;
    }
    else if(redis_context->err){
        std::cout<< "connection encounts errors: " << redis_context->errstr <<std::endl;
        return 1;
    }

    {
        redisAppendCommand(redis_context, "SET temp 1 EX 5");
        redisAppendCommand(redis_context, "GET temp");

        redisReply* redis_reply = nullptr;
        for(int i=0; i<2; i++){
            redisGetReply(redis_context, reinterpret_cast<void**>(&redis_reply));
            std::cout<< "reply 1: " << redis_reply->str <<std::endl;
            freeReplyObject(redis_reply);
        }
    }

    {
        redisAppendCommand(redis_context, "SET temp2 1 EX 5");
        redisAppendCommand(redis_context, "GET temp2");
        redisAppendCommand(redis_context, "GETSET temp2 2");

        redisReply* redis_reply;
        for(int i=0; i<3; i++){
            redisGetReply(redis_context, reinterpret_cast<void**>(&redis_reply));
            std::cout<< "redis 2: " << redis_reply->str <<std::endl;
            freeReplyObject(redis_reply);
        }
    }

    redisFree(redis_context);
    return 0;
}
