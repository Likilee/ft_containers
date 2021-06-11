CONTAINER = vector

test :
	cd ./containers_test && ./do.sh $(CONTAINER)
at :
	cd ./containers_test && ./one srcs/$(CONTAINER)/at.cpp
assign :
	cd ./containers_test && ./one srcs/$(CONTAINER)/assign.cpp
at_const :
	cd ./containers_test && ./one srcs/$(CONTAINER)/at_const.cpp
bidirect_it :
	cd ./containers_test && ./one srcs/$(CONTAINER)/bidirect_it.cpp
copy_construct.cpp :
	cd ./containers_test && ./one srcs/$(CONTAINER)/copy_construct.cpp.cpp
erase :
	cd ./containers_test && ./one srcs/$(CONTAINER)/erase.cpp
insert :
	cd ./containers_test && ./one srcs/$(CONTAINER)/insert.cpp
insert2 :
	cd ./containers_test && ./one srcs/$(CONTAINER)/insert2.cpp
ite :
	cd ./containers_test && ./one srcs/$(CONTAINER)/ite.cpp
ite_arrow :
	cd ./containers_test && ./one srcs/$(CONTAINER)/ite_arrow.cpp
ite_eq_ope :
	cd ./containers_test && ./one srcs/$(CONTAINER)/ite_eq_ope.cpp
ite_n0 :
	cd ./containers_test && ./one srcs/$(CONTAINER)/ite_n0.cpp
ite_n00 :
	cd ./containers_test && ./one srcs/$(CONTAINER)/ite_n00.cpp
ite_n1 :
	cd ./containers_test && ./one srcs/$(CONTAINER)/ite_n1.cpp
push_pop :
	cd ./containers_test && ./one srcs/$(CONTAINER)/push_pop.cpp
relational_ope :
	cd ./containers_test && ./one srcs/$(CONTAINER)/relational_ope.cpp
rev_ite_construct :
	cd ./containers_test && ./one srcs/$(CONTAINER)/rev_ite_construct.cpp
rite :
	cd ./containers_test && ./one srcs/$(CONTAINER)/rite.cpp
rite2 :
	cd ./containers_test && ./one srcs/$(CONTAINER)/rite2.cpp
rite_arrow :
	cd ./containers_test && ./one srcs/vector/rite_arrow.cpp
rite_eq_ope :
	cd ./containers_test && ./one srcs/vector/rite_eq_ope.cpp
size :
	cd ./containers_test && ./one srcs/vector/size.cpp
swap :
	cd ./containers_test && ./one srcs/vector/swap.cpp
