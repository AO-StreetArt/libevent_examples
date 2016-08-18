sudo apt-get install libevent-dev
g++ -o hw_server hw_server.cpp -lpthread -levent -std=c++11
curl --request GET 'http://127.0.0.1:5555/'
g++ -o mserver multisocket_server.cpp -lpthread -levent -std=c++11
g++ -o basic_requests_server basic_requests_server.cpp  -lpthread -levent -std=c++11

