$bin = "bin/${@/.cpp/}"
g++ -DLOCAL_ -o "$bin" "$@"
time ./$bin < in.in > out.out & sleep 1
[[ -n $(echo $(jobs) | grep -i Running) ]] && (echo "TLE"; killall "$bin"; rm "$bin"; exit 1)
rm "$bin"