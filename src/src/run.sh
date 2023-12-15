$bin = "bin/${@/.cpp/}"
g++ -Wall -Wextra -o "$bin" "$@"
time ./$bin < in.in > out.out & sleep 1
[[ -n $(echo $(jobs) | grep -i Running) ]] && (echo "TLE"; killall "$bin"; rm "$bin"; exit 1)
rm "$bin"