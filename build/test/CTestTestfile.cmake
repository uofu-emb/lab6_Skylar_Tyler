# CMake generated Testfile for 
# Source directory: /Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab6/test
# Build directory: /Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab6/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(simulate_mytest "RENODE-NOTFOUND" "--disable-xwt" "--port" "-2" "--pid-file" "renode.pid" "--console" "-e" "\$ELF=@/Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab6/build/test/mytest.elf; \$WORKING=@/Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab6; include @/Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab6/test/simulate.resc; start")
set_tests_properties(simulate_mytest PROPERTIES  _BACKTRACE_TRIPLES "/Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab6/test/CMakeLists.txt;48;add_test;/Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab6/test/CMakeLists.txt;0;")
