CONTAINER = map
NS = ft

COMMAND = one

all :
	c++ -g3 -fsanitize=address test.cpp
	./a.out
test :
	cd ./containers_test && ./do.sh $(CONTAINER)
bounds :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/bounds.cpp $(NS)
comp :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/comp.cpp $(NS)
copy_construct :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/copy_construct.cpp $(NS)
empty :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/empty.cpp $(NS)
erase :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/erase.cpp $(NS)
erase2 :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/erase2.cpp $(NS)
find_count :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/find_count.cpp $(NS)
insert :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/insert.cpp $(NS)
insert2 :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/insert2.cpp $(NS)
ite_arrow :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/ite_arrow.cpp $(NS)
ite_n0 :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/ite_n0.cpp $(NS)
ite_n1 :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/ite_n1.cpp $(NS)
ite_type :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/ite_type.cpp $(NS)
more :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/more.cpp $(NS)
op_sqbr :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/op_sqbr.cpp $(NS)
relational_ope :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/relational_ope.cpp $(NS)
rev_ite_construct :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/rev_ite_construct.cpp $(NS)
rite :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/rite.cpp $(NS)
rite_arrow :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/rite_arrow.cpp $(NS)
swap :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/swap.cpp $(NS)
tricky_construct :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/tricky_construct.cpp $(NS)
tricky_erase :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/tricky_erase.cpp $(NS)