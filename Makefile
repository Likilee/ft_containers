MLI_TESTER_DIR = ./tester/mli42_tester/
MY_TESTER_DIR = ./tester/my_tester
TEST_RESULT = $(MY_TESTER_DIR)/result
CONT = vector
CXXFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address -std=c++98 #-lgtest -lgtest_main -pthread
INCLUDE = -I./include/
STD_NS = -D TEST_NS=std

#COLORS
RED=\033[0;31m
NC=\033[0m
GREEN=\033[0;32m
BLUE=\033[0;34m
small :
	@c++ $(CXXFLAGS) $(INCLUDE) main.cpp -o main
	./main
mli :
	cd $(MLI_TESTER_DIR) && ./do.sh $(CONT)

my :
	@c++ $(CXXFLAGS) $(INCLUDE) $(MY_TESTER_DIR)/$(CONT).cpp -o vector
	@./vector > $(TEST_RESULT)/ft.vector.result
	@rm vector
	@rm -rf vector.dSYM
	@c++ $(CXXFLAGS) $(INCLUDE) $(STD_NS) $(MY_TESTER_DIR)/$(CONT).cpp -o $(CONT)
	@./$(CONT) > $(TEST_RESULT)/std.$(CONT).result
	@rm $(CONT)
	@rm -rf $(CONT).dSYM
	@printf "***************************************************\n"
	@printf "**                                               **\n"
	@printf "**$(GREEN)               $(CONT) TEST START!              $(NC)**\n"
	@printf "**                                               **\n"
	@printf "***************************************************\n"
	@diff -d $(TEST_RESULT)/std.$(CONT).result $(TEST_RESULT)/ft.$(CONT).result > $(TEST_RESULT)/$(CONT).diff || exit 0
	@if [ -s "$(TEST_RESULT)/$(CONT).diff" ]; then \
		printf "\n                   🔥 $(RED)FAILED$(NC) 🔥\n";\
		printf "====================== DIFF =======================\n\n";\
		cat $(TEST_RESULT)/$(CONT).diff;\
		printf "\n======================++++++=======================\n";\
	else\
		printf "\n                   💧 $(BLUE)SUCCESS$(NC) 💧\n\n";\
	fi

diff: