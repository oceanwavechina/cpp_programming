
# 用 Docker 搭建zookeeper集群

搭建集群
https://www.cnblogs.com/LUA123/p/11428113.html

## 1. standalone模式

```
docker pull zookeeper

docker run --name my_zookeeper -d zookeeper:latest

查看日志
docker logs -f my_zookeeper


docker run -it --rm --link my_zookeeper:zookeeper zookeeper zkCli.sh -server zookeeper
    这个命令的含义是:
    启动一个 zookeeper 镜像, 并运行这个镜像内的 zkCli.sh 命令, 命令参数是 "-server zookeeper"
    将我们先前启动的名为 my_zookeeper 的容器连接(link) 到我们新建的这个容器上, 并将其主机名命名为 zookeeper
    当我们执行了这个命令后, 就可以像正常使用 ZK 命令行客户端一样操作 ZK 服务了.

```

## 用docker-compose 搭建集群

```
    cd MY_PATH/zookeeper_box/zookeeper
    docker network create --driver bridge --subnet=172.170.0.0/16 --gateway=172.170.0.1 zoonet

    docker-compose -f docker-compose.yml up -d

    另一个终端
        docker-compose ps

        进入一个容器
        docker exec -it b5f48775e4b0 bash
```