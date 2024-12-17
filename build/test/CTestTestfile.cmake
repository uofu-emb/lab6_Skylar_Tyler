# CMake generated Testfile for 
# Source directory: /Users/tyler/documents/fall2024/ECE5785-adv_emb/lab6d/lab6_Skylar_Tyler/test
# Build directory: /Users/tyler/documents/fall2024/ECE5785-adv_emb/lab6d/lab6_Skylar_Tyler/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(simulate_mytest "RENODE-NOTFOUND" "--disable-xwt" "--port" "-2" "--pid-file" "renode.pid" "--console" "-e" "\$ELF=@/Users/tyler/documents/fall2024/ECE5785-adv_emb/lab6d/lab6_Skylar_Tyler/build/test/mytest.elf; \$WORKING=@/Users/tyler/documents/fall2024/ECE5785-adv_emb/lab6d/lab6_Skylar_Tyler; include @/Users/tyler/documents/fall2024/ECE5785-adv_emb/lab6d/lab6_Skylar_Tyler/test/simulate.resc; start")
set_tests_properties(simulate_mytest PROPERTIES  _BACKTRACE_TRIPLES "/Users/tyler/documents/fall2024/ECE5785-adv_emb/lab6d/lab6_Skylar_Tyler/test/CMakeLists.txt;39;add_test;/Users/tyler/documents/fall2024/ECE5785-adv_emb/lab6d/lab6_Skylar_Tyler/test/CMakeLists.txt;0;")
