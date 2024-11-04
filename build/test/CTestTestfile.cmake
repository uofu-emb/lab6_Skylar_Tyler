# CMake generated Testfile for 
# Source directory: /Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler/test
# Build directory: /Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(simulate_mytest "RENODE-NOTFOUND" "--disable-xwt" "--port" "-2" "--pid-file" "renode.pid" "--console" "-e" "\$ELF=@/Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler/build/test/mytest.elf; \$WORKING=@/Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler; include @/Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler/test/simulate.resc; start")
set_tests_properties(simulate_mytest PROPERTIES  _BACKTRACE_TRIPLES "/Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler/test/CMakeLists.txt;39;add_test;/Users/tyler/Documents/fall2024/ECE5785-adv_emb/lab5/lab_5_Muteeb_Tyler/test/CMakeLists.txt;0;")
