#!/bin/bash

# 定义 Redis 服务器的启动命令
REDIS_SERVER="../../src/redis-server"

# 定义 Redis 服务器的进程名，根据实际情况修改
REDIS_PROCESS_NAME="redis-server"

# 定义端口列表
PORTS=(16380 16381 16382 16383 16384)

# 循环重启 Redis 服务
for PORT in "${PORTS[@]}"; do
    # 检查 Redis 服务是否正在运行
    if ps -ef | grep "$REDIS_PROCESS_NAME" | grep -w "127.0.0.1:$PORT" | grep -v grep > /dev/null; then
        echo "Stopping Redis on 127.0.0.1:$PORT"
        # 使用 pkill 命令杀死 Redis 服务
        pkill -f "127.0.0.1:$PORT"
        # 等待一段时间确保服务关闭
        sleep 0.1
    fi

    # 启动 Redis 服务
    echo "Starting Redis on 127.0.0.1:$PORT"
    $REDIS_SERVER redis_$PORT.conf &
    if [ $? -eq 0 ]; then
        echo "Redis started successfully on 127.0.0.1:$PORT"
    else
        echo "Failed to start Redis on 127.0.0.1:$PORT"
    fi
done