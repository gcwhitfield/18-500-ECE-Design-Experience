# CMake generated Testfile for 
# Source directory: /Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/jsoncpp/src/jsontestrunner
# Build directory: /Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/libs/jsoncpp/src/jsontestrunner
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(jsoncpp_readerwriter "/Library/Frameworks/Python.framework/Versions/3.8/bin/python3.8" "-B" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/jsoncpp/src/jsontestrunner/../../test/runjsontests.py" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/bin/jsontestrunner_exe" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/jsoncpp/src/jsontestrunner/../../test/data")
set_tests_properties(jsoncpp_readerwriter PROPERTIES  WORKING_DIRECTORY "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/jsoncpp/src/jsontestrunner/../../test/data" _BACKTRACE_TRIPLES "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/jsoncpp/src/jsontestrunner/CMakeLists.txt;43;add_test;/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/jsoncpp/src/jsontestrunner/CMakeLists.txt;0;")
add_test(jsoncpp_readerwriter_json_checker "/Library/Frameworks/Python.framework/Versions/3.8/bin/python3.8" "-B" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/jsoncpp/src/jsontestrunner/../../test/runjsontests.py" "--with-json-checker" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/build/bin/jsontestrunner_exe" "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/jsoncpp/src/jsontestrunner/../../test/data")
set_tests_properties(jsoncpp_readerwriter_json_checker PROPERTIES  WORKING_DIRECTORY "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/jsoncpp/src/jsontestrunner/../../test/data" _BACKTRACE_TRIPLES "/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/jsoncpp/src/jsontestrunner/CMakeLists.txt;47;add_test;/Users/george/Desktop/教育/CMU/Senior Year/ECE Capstone 18-500/18-500-ECE-Design-Experience/libs/jsoncpp/src/jsontestrunner/CMakeLists.txt;0;")
