CONTAINER = vector
NS = ft

COMMAND = cmp_one

test :
	cd ./containers_test && ./do.sh $(CONTAINER)
at :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/at.cpp $(NS)
assign :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/assign.cpp $(NS)
at_const :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/at_const.cpp $(NS)
bidirect_it :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/bidirect_it.cpp $(NS)
copy_construct :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/copy_construct.cpp $(NS)
erase :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/erase.cpp $(NS)
insert :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/insert.cpp $(NS)
insert2 :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/insert2.cpp $(NS)
ite :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/ite.cpp $(NS)
ite_arrow :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/ite_arrow.cpp $(NS)
ite_eq_ope :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/ite_eq_ope.cpp $(NS)
ite_n0 :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/ite_n0.cpp $(NS)
ite_n00 :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/ite_n00.cpp $(NS)
ite_n1 :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/ite_n1.cpp $(NS)
push_pop :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/push_pop.cpp $(NS)
relational_ope :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/relational_ope.cpp $(NS)
rev_ite_construct :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/rev_ite_construct.cpp $(NS)
rite :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/rite.cpp $(NS)
rite2 :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/rite2.cpp $(NS)
rite_arrow :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/rite_arrow.cpp $(NS)
rite_eq_ope :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/rite_eq_ope.cpp $(NS)
size :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/size.cpp $(NS)
swap :
	cd ./containers_test && ./$(COMMAND) srcs/$(CONTAINER)/swap.cpp $(NS)
