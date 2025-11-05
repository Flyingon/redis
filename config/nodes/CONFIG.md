## 集群配置

集群基本配置
```
# Redis 基础配置
port 6379
cluster-enabled yes
cluster-config-file nodes.conf
cluster-node-timeout 5000
appendonly yes
logfile "redis-cluster.log"
dir ./
protected-mode no  # 禁用保护模式，允许外部访问

# 仅用于开发和测试，生产环境请添加密码
```

自动配置集群
```
redis-cli --cluster create 127.0.0.1:16379 127.0.0.1:16380 127.0.0.1:16381 127.0.0.1:16382 127.0.0.1:16383 127.0.0.1:16384 --cluster-replicas 1 --cluster-yes
```

添加 slots
```
redis-cli -p 6379 cluster addslots $(seq 0 16383)
```

备节点切换到主
```
redis-cli -h 127.0.0.1 -p 16379 CLUSTER FAILOVER
```

检查集群
```
cluster nodes
cluster info
cluster slots
```