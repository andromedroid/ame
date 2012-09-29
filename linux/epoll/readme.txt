gcc -Wall ./client1.c -o ./cl1
gcc -Wall ./client2.c -o ./cl2
gcc -Wall ./select.c -o ./sel

./sel &

./cl1

./cl2
