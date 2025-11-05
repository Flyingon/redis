#include "server.h"

void myCommandFunc(client *c) {
    if (c->argc!= 4) {
        // 参数个数不对，返回错误信息给客户端
        addReplyError(c, "ERR wrong number of arguments for 'myCommandFunc' command");
        return;
    }

    robj *key_obj = c->argv[1];
    robj *zset1_obj = c->argv[2];
    robj *zset2_obj = c->argv[3];

    // 获取 key 对应的 SDS 字符串表示（这里假设 robj 结构体中有合适方式获取，比如通过 ptr 字段等，需根据实际调整）
    sds key_sds = sdsnew((char *)key_obj->ptr);

    // 从 zset1 中删除指定 key 的元素
    int del_result = zsetDel(zset1_obj, key_sds);
    if (del_result) {
        // 定义用于 zsetAdd 的输入标志和输出标志变量（这里根据常见需求设置，可按需调整）
        int in_flags = 0;
        int out_flags = 0;
        // 调用 zsetAdd 将元素添加到 zset2 中，这里假设分值为 0（实际可能需按业务确定分值）
        int add_result = zsetAdd(zset2_obj, 0, key_sds, in_flags, &out_flags, NULL);
        if (add_result) {
            addReply(c, shared.ok);
        } else {
            addReplyError(c, "ERR failed to add element to zset2");
        }
    } else {
        addReplyError(c, "ERR element not found in zset1");
    }

    // 释放相关的 SDS 字符串内存
    sdsfree(key_sds);
}
