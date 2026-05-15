day := "day1"

valgrind *args:
    cd {{ day }} && make clean && make SANITIZE_FLAGS=
    cd {{ day }} && valgrind --tool=memcheck --leak-check=full --track-origins=yes ../target/c/{{ day }}/debug/{{ day }} {{ args }}

callgrind *args:
    cd {{ day }} && make clean && make release RELEASE_CFLAGS="-std=c23 -fdefer-ts -Wall -Wextra -Wpedantic -O3 -g -DNDEBUG"
    cd {{ day }} && valgrind --tool=callgrind --callgrind-out-file=callgrind.out ../target/c/{{ day }}/release/{{ day }} {{ args }}
    cd {{ day }} && callgrind_annotate callgrind.out

samply *args:
    # echo '-1' | sudo tee /proc/sys/kernel/perf_event_paranoid
    cd {{ day }} && make clean && make release RELEASE_CFLAGS="-std=c23 -fdefer-ts -Wall -Wextra -Wpedantic -O3 -g -DNDEBUG -fno-omit-frame-pointer"
    samply record target/c/{{ day }}/release/{{ day }} {{ args }}
